//
//  ProximityPresentationFlow.swift
//  iProov Identity Sample App
//
//  Holder/presenter side of ISO/IEC 18013-5 proximity presentation. Mirrors the
//  Android example app's HomeScreenViewModel + ProximityPresentationSheet:
//   - reader-trust banner (4 ReaderAuth states),
//   - consent → selective-disclosure → send,
//   - three terminal outcomes (full / partial / nothing) + failure with retry,
//   - disconnect-before-share treated as a failure, not a success.
//
//  The SDK session/timeout/trust logic lives in commonMain and is shared, so this
//  is purely the iOS app layer.
//
//  SDK contract (everything else here — trust banner, full/partial/none classification,
//  eager matching, hero screens — is optional UI/UX):
//    1. let session = try await wallet.startProximityPresentation(qr:config:)
//    2. session.events.collect { ... }       // drive the UI from ProximityPresentationEvent
//    3. on .RequestReceived: request.match()   // which stored credentials satisfy the request
//    4. request.respond(disclosed:)            // send the user's picks (empty map = decline)
//    5. session.close()                        // cancel / teardown
//

import CoreBluetooth
import CoreImage.CIFilterBuiltins
import SwiftUI
import UIKit
import identity

// MARK: - ViewModel

@MainActor
final class ProximityPresentationViewModel: ObservableObject {

    /// How much of the reader's request the user actually disclosed. The protocol
    /// always sends DeviceResponse status 0 regardless, so this is derived app-side.
    enum Completion { case shared, partiallyShared, nothingShared }

    /// Per requested-document selection state during the disclosure step.
    struct DocSelection: Identifiable {
        let docRequest: DocRequest
        var candidates: [DisclosedDocument]
        var selectedIndex: Int?
        var selectedItems: [String: Set<String>]  // namespace -> element identifiers
        var id: String { docRequest.docType }
        var isReady: Bool {
            selectedIndex != nil && selectedItems.values.contains { !$0.isEmpty }
        }
    }

    enum State {
        case generatingEngagement
        case showingQr(String)
        case connecting
        case awaitingRequest
        case consent(RespondableProximityRequest)
        case disclosure(request: RespondableProximityRequest, matching: Bool, selections: [DocSelection])
        case sending  // response (or decline) handed to the SDK; awaiting completion
        case completed(Completion)
        case failure(headline: String, message: String)
    }

    @Published var state: State = .generatingEngagement

    private let wallet = WalletFactory.shared.instance!
    private var session: ProximityPresentationSession?
    private var collectTask: Task<Void, Never>?
    private var presentationCompleted = false
    private var lastOutcome: Completion = .shared
    // Guards against starting a second session on the same view model (e.g. if onAppear
    // re-fires after a system permission alert) — a stray second engagement would time
    // out and overwrite a completed result.
    private var started = false

    /// Whether the wallet holds anything that satisfies the current request. Resolved
    /// eagerly (a local DB read) as soon as the request arrives so the consent screen
    /// can disable "Select document" when there's nothing to share. `nil` = still matching.
    @Published private(set) var consentMatchAvailable: Bool? = nil
    private var matchTask: Task<[String: [DisclosedDocument]], Never>?

    var isInProgress: Bool {
        switch state {
        case .completed, .failure: return false
        default: return true
        }
    }

    // MARK: Lifecycle

    func start() {
        guard !started else { return }  // never launch a second session on this view model

        // iOS has no per-permission runtime request like Android — Bluetooth is one
        // CBManager authorization (auto-prompted on first use). We pre-flight only the
        // already-denied case so it surfaces clearly instead of as a 30s engagement
        // timeout. (Bluetooth-off still falls through to the timeout — the OS prompts.)
        switch CBManager.authorization {
        case .denied, .restricted:
            state = .failure(
                headline: "Bluetooth permission needed",
                message: "Allow Bluetooth access for this app in Settings to share credentials."
            )
            return  // leave `started` false so the user can retry after enabling access
        default:
            break
        }

        started = true
        presentationCompleted = false
        state = .generatingEngagement

        Task {
            do {
                let session = try await wallet.startProximityPresentation(
                    qr: PresentationMethod.QrPresentation.shared,
                    config: ProximityConfig())
                self.session = session
                collect(session)
            } catch {
                state = .failure(headline: "Something went wrong", message: error.localizedDescription)
            }
        }
    }

    private func collect(_ session: ProximityPresentationSession) {
        collectTask = Task {
            // The flow's callbacks arrive off the main thread, so hop to the MainActor
            // before touching @Published state. (Terminal ordering is made safe by the
            // `presentationCompleted` guard in handle(), not by event arrival order.)
            session.events.collect(
                onEach: { [weak self] event in
                    guard let event else { return }
                    Task { @MainActor in self?.handle(event) }
                },
                onError: { [weak self] error in
                    Task { @MainActor in
                        guard let self else { return }
                        // The flow itself threw (rare — the SDK normally emits a Failure
                        // event). Don't overwrite an already-shown terminal state.
                        if !self.presentationCompleted, !self.isTerminal {
                            self.state = .failure(
                                headline: "Something went wrong",
                                message: error.localizedDescription)
                        }
                    }
                })
        }
    }

    private var isTerminal: Bool {
        switch state {
        case .completed, .failure: return true
        default: return false
        }
    }

    private func handle(_ event: ProximityPresentationEvent) {
        switch event {
        case is ProximityPresentationEvent.EngagementGenerating:
            // Don't clobber the QR if this arrives after QrEngagementReady.
            if case .showingQr = state {} else { state = .generatingEngagement }

        case let e as ProximityPresentationEvent.EngagementQrReady:
            state = .showingQr(e.payload.mdocUri)

        case is ProximityPresentationEvent.Connecting:
            // Keep the QR on screen while advertising; only move on once connected.
            if case .showingQr = state {} else { state = .connecting }

        case is ProximityPresentationEvent.Connected,
            is ProximityPresentationEvent.CreatingSession,
            is ProximityPresentationEvent.SessionCreated:
            state = .awaitingRequest

        case let e as ProximityPresentationEvent.RequestReceived:
            beginConsent(e.request)

        case is ProximityPresentationEvent.PresentationSent:
            presentationCompleted = true
            state = .completed(lastOutcome)

        case is ProximityPresentationEvent.Disconnected:
            // A disconnect after a successful share is the expected teardown. Before
            // sharing it means the session ended without completing — a failure, not
            // a success (e.g. the reader timed out and terminated).
            if !presentationCompleted {
                state = .failure(
                    headline: "Session ended",
                    message: "The session ended before your credentials were shared.")
            }

        case let e as ProximityPresentationEvent.Failure:
            if !presentationCompleted {
                state = .failure(headline: "Something went wrong", message: e.error)
            }

        default:
            break
        }
    }

    // MARK: User actions

    /// Show the consent screen and eagerly resolve which stored credentials satisfy the
    /// request, so the UI can reflect availability before the user commits.
    private func beginConsent(_ request: RespondableProximityRequest) {
        consentMatchAvailable = nil
        state = .consent(request)
        // Match once, eagerly. onConsent() awaits this same task, so match() never re-runs.
        matchTask?.cancel()
        let task = Task { await self.runMatch(request) }
        matchTask = task
        Task { @MainActor in
            let byType = await task.value
            guard case .consent = state else { return }
            consentMatchAvailable = request.docRequests.contains { !(byType[$0.docType] ?? []).isEmpty }
        }
    }

    /// Run the SDK match(). A throw must not crash the flow — fall back to empty.
    private func runMatch(_ request: RespondableProximityRequest) async -> [String: [DisclosedDocument]] {
        do {
            let matched = try await request.match()
            var byType: [String: [DisclosedDocument]] = [:]
            for (key, value) in matched { byType[key.docType] = value }
            return byType
        } catch {
            return [:]
        }
    }

    /// One DocSelection per requested document, with all requested items selected by
    /// default and matched candidates filled in (empty `matchedBy` → no candidates yet).
    private func selections(
        for request: RespondableProximityRequest,
        matchedBy byType: [String: [DisclosedDocument]]
    ) -> [DocSelection] {
        request.docRequests.map { dr in
            var items: [String: Set<String>] = [:]
            for (ns, reqItems) in dr.requestedItems {
                items[ns] = Set(reqItems.map { $0.elementIdentifier })
            }
            let candidates = byType[dr.docType] ?? []
            return DocSelection(
                docRequest: dr,
                candidates: candidates,
                selectedIndex: candidates.count == 1 ? 0 : nil,
                selectedItems: items
            )
        }
    }

    /// Consent given on the review step → move to disclosure, reusing the single match
    /// task from beginConsent() (the await is instant once it has resolved).
    func onConsent() {
        guard case .consent(let request) = state, let task = matchTask else { return }
        state = .disclosure(
            request: request, matching: true,
            selections: selections(for: request, matchedBy: [:]))
        Task { @MainActor in
            let byType = await task.value
            guard case .disclosure(let r, _, _) = state, r === request else { return }
            state = .disclosure(
                request: request, matching: false,
                selections: selections(for: request, matchedBy: byType))
        }
    }

    /// Mutate the disclosure selections in place (no-op outside the disclosure step).
    private func updateSelections(_ transform: (inout [DocSelection]) -> Void) {
        guard case .disclosure(let request, let matching, let selections) = state else { return }
        var updated = selections
        transform(&updated)
        state = .disclosure(request: request, matching: matching, selections: updated)
    }

    func selectCandidate(docType: String, index: Int) {
        updateSelections { sels in
            guard let i = sels.firstIndex(where: { $0.docRequest.docType == docType }),
                index < sels[i].candidates.count
            else { return }
            sels[i].selectedIndex = index
        }
    }

    func toggleItem(docType: String, namespace: String, item: String) {
        updateSelections { sels in
            guard let i = sels.firstIndex(where: { $0.docRequest.docType == docType }) else { return }
            var set = sels[i].selectedItems[namespace] ?? []
            if set.contains(item) { set.remove(item) } else { set.insert(item) }
            sels[i].selectedItems[namespace] = set
        }
    }

    /// Final confirm — package the user's picks and hand them back to the SDK.
    func submitDisclosure() {
        guard case .disclosure(let request, _, let selections) = state else { return }

        let picks = selections.reduce(into: [DocRequest: DisclosedDocument]()) { picks, sel in
            guard let idx = sel.selectedIndex, idx < sel.candidates.count else { return }
            let disclosed = sel.selectedItems.filter { !$0.value.isEmpty }
            picks[sel.docRequest] = DisclosedDocument(
                credential: sel.candidates[idx].credential,
                metadata: sel.candidates[idx].metadata,
                disclosedItems: disclosed)
        }

        lastOutcome = classify(selections)
        // Move to the sending state immediately: gives feedback while the (possibly slow)
        // BLE send runs, and removes the buttons so respond() can't be invoked twice on
        // the same transport. The terminal state arrives via PresentationSent / Failure.
        state = .sending
        Task { _ = try? await request.respond(disclosed: picks) }
    }

    /// Decline → send an empty disclosure so the SDK closes cleanly.
    func decline() {
        guard case .consent(let request) = state else { return }
        lastOutcome = .nothingShared
        state = .sending
        Task { _ = try? await request.respond(disclosed: [:]) }
    }

    func backToReview() {
        // consentMatchAvailable was computed for this request in beginConsent() and
        // doesn't change, so just restore the consent step.
        if case .disclosure(let request, _, _) = state { state = .consent(request) }
    }

    func retry() {
        collectTask?.cancel()
        let old = session
        session = nil
        Task { try? await old?.close() }
        started = false  // allow a fresh session
        start()
    }

    func cancel() {
        collectTask?.cancel()
        let old = session
        session = nil
        Task { try? await old?.close() }
    }

    // MARK: Helpers

    func readerDisplayName(_ readerAuth: ReaderAuth) -> String {
        switch readerAuth {
        case let t as ReaderAuthTrusted: return t.commonName
        case let u as ReaderAuthUntrusted: return u.commonName ?? "An unidentified reader"
        default: return "An unidentified reader"
        }
    }

    func isRisky(_ readerAuth: ReaderAuth) -> Bool {
        readerAuth is ReaderAuthUntrusted || readerAuth is ReaderAuthSignatureInvalid
    }

    /// Did the user share everything requested, only some of it, or nothing? Derived from
    /// the selections (the protocol always sends status 0 regardless of how much went out).
    private func classify(_ selections: [DocSelection]) -> Completion {
        var anyShared = false
        var allComplete = true
        for sel in selections {
            let requested = Set(sel.docRequest.requestedItems.values.flatMap { $0.map { $0.elementIdentifier } })
            let shared: Set<String> =
                sel.selectedIndex == nil
                ? []
                : Set(sel.selectedItems.values.flatMap { $0 })
            if !shared.isEmpty { anyShared = true }
            if !shared.isSuperset(of: requested) { allComplete = false }
        }
        if !anyShared { return .nothingShared }
        return allComplete ? .shared : .partiallyShared
    }
}

// MARK: - Entry-point button

struct PresentProximityButton: View {
    @State private var showSheet = false

    var body: some View {
        Button {
            showSheet = true
        } label: {
            Image(systemName: "dot.radiowaves.left.and.right")
                .font(.title.weight(.semibold))
                .padding()
                .background(Color.accentColor)
                .foregroundColor(.white)
                .clipShape(Circle())
                .shadow(radius: 4)
        }
        .accessibilityLabel("Present credentials")
        .sheet(isPresented: $showSheet) {
            ProximityPresentationSheet(onDismiss: { showSheet = false })
        }
    }
}

// MARK: - Sheet

struct ProximityPresentationSheet: View {
    @StateObject private var viewModel = ProximityPresentationViewModel()
    let onDismiss: () -> Void

    var body: some View {
        NavigationStack {
            Group {
                switch viewModel.state {
                case .generatingEngagement:
                    progress(icon: "qrcode", tint: .blue, title: "Preparing…", subtitle: nil)
                case .connecting:
                    progress(
                        icon: "antenna.radiowaves.left.and.right", tint: .blue,
                        title: "Waiting for reader", subtitle: "Advertising over Bluetooth…")
                case .awaitingRequest:
                    progress(
                        icon: "hourglass", tint: .orange,
                        title: "Connected", subtitle: "Waiting for the reader's request…")
                case .showingQr(let uri):
                    QrStep(mdocUri: uri)
                case .consent(let request):
                    ConsentStep(viewModel: viewModel, request: request)
                case .disclosure(let request, let matching, let selections):
                    DisclosureStep(
                        viewModel: viewModel, request: request,
                        matching: matching, selections: selections)
                case .sending:
                    progress(
                        icon: "paperplane", tint: .blue,
                        title: "Sending…", subtitle: "Sharing your response with the reader.")
                case .completed(let completion):
                    completedHero(completion)
                case .failure(let headline, let message):
                    TerminalHero(
                        icon: "exclamationmark.triangle.fill",
                        tint: .red,
                        headline: headline,
                        detail: message
                    ) {
                        Button("Try again") { viewModel.retry() }
                            .buttonStyle(.borderedProminent)
                            .controlSize(.large)
                        Button("Close") { onDismiss() }
                            .buttonStyle(.bordered)
                            .controlSize(.large)
                    }
                }
            }
            .navigationTitle("Proximity Sharing")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .cancellationAction) {
                    if viewModel.isInProgress {
                        Button("Cancel") {
                            viewModel.cancel()
                            onDismiss()
                        }
                    }
                }
            }
        }
        .interactiveDismissDisabled(viewModel.isInProgress)
        .onAppear { viewModel.start() }
    }

    private func progress(icon: String, tint: Color, title: String, subtitle: String?) -> some View {
        // Matches the proximity-reading screens: hierarchical status icon → title →
        // subtitle → spinner.
        VStack(spacing: 24) {
            Spacer()
            Image(systemName: icon)
                .font(.system(size: 48))
                .symbolRenderingMode(.hierarchical)
                .foregroundStyle(tint)
            Text(title).font(.title3.weight(.semibold))
            if let subtitle {
                Text(subtitle)
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .multilineTextAlignment(.center)
                    .padding(.horizontal, 32)
            }
            ProgressView().controlSize(.large)
            Spacer()
        }
    }

    @ViewBuilder
    private func completedHero(_ completion: ProximityPresentationViewModel.Completion) -> some View {
        let (icon, tint, headline, detail): (String, Color, String, String) = {
            switch completion {
            case .shared:
                return (
                    "checkmark.circle.fill", .green, "Credentials shared",
                    "Your details were shared securely with the reader."
                )
            case .partiallyShared:
                return (
                    "info.circle.fill", .blue, "Some details shared",
                    "Only the items you selected were shared — the rest were withheld."
                )
            case .nothingShared:
                return (
                    "xmark.circle.fill", .secondary, "Request declined",
                    "No information was shared with the reader."
                )
            }
        }()
        TerminalHero(icon: icon, tint: tint, headline: headline, detail: detail) {
            Button("Done") { onDismiss() }
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
        }
    }
}

// MARK: - Terminal hero (success / partial / nothing / failure)

private struct TerminalHero<Actions: View>: View {
    let icon: String
    let tint: Color
    let headline: String
    let detail: String
    @ViewBuilder let actions: () -> Actions

    var body: some View {
        // Static, flat treatment to match the proximity-reading completed/error screens.
        VStack(spacing: 16) {
            Spacer()
            Image(systemName: icon)
                .font(.system(size: 48))
                .symbolRenderingMode(.hierarchical)
                .foregroundStyle(tint)
            Text(headline)
                .font(.title2.weight(.bold))
                .multilineTextAlignment(.center)
                .accessibilityAddTraits(.isHeader)
            Text(detail)
                .font(.subheadline)
                .foregroundStyle(.secondary)
                .multilineTextAlignment(.center)
                .padding(.horizontal, 32)
            Spacer()
            VStack(spacing: 8) { actions() }
                .frame(maxWidth: .infinity)
                .padding(.horizontal)
                .padding(.bottom)
        }
    }
}

// MARK: - Reader trust banner

private struct ReaderTrustBanner: View {
    let readerAuth: ReaderAuth

    private var visual: (icon: String, tint: Color, title: String, detail: String) {
        switch readerAuth {
        case let t as ReaderAuthTrusted:
            return ("checkmark.shield.fill", .green, "Verified reader", t.commonName)
        case let u as ReaderAuthUntrusted:
            return (
                "exclamationmark.shield.fill", .orange, "Unverified reader",
                u.commonName.map { "Claims to be \"\($0)\", but its identity could not be verified." }
                    ?? "This reader's identity could not be verified."
            )
        case is ReaderAuthSignatureInvalid:
            return (
                "xmark.shield.fill", .red, "Reader identity invalid",
                "The reader's authentication signature failed. Sharing is not recommended."
            )
        default:  // Absent
            return (
                "questionmark.circle.fill", .blue, "Anonymous request",
                "This reader hasn't identified itself. Only share if you trust it."
            )
        }
    }

    var body: some View {
        let v = visual
        HStack(alignment: .top, spacing: 12) {
            Image(systemName: v.icon)
                .font(.title3)
                .foregroundStyle(v.tint)
            VStack(alignment: .leading, spacing: 2) {
                Text(v.title).font(.subheadline.weight(.semibold))
                Text(v.detail).font(.footnote).foregroundStyle(.secondary)
            }
            Spacer(minLength: 0)
        }
        .padding(12)
        .frame(maxWidth: .infinity, alignment: .leading)
        .background(v.tint.opacity(0.12))
        .clipShape(RoundedRectangle(cornerRadius: 12))
        .accessibilityElement(children: .combine)
    }
}

// MARK: - Consent step

private struct ConsentStep: View {
    @ObservedObject var viewModel: ProximityPresentationViewModel
    let request: RespondableProximityRequest
    @State private var showContinueConfirm = false

    private var selectLabel: String {
        request.docRequests.count > 1 ? "Select documents" : "Select document"
    }

    var body: some View {
        ScrollView {
            VStack(alignment: .leading, spacing: 16) {
                VStack(alignment: .leading, spacing: 6) {
                    Text("\(viewModel.readerDisplayName(request.readerAuth)) is requesting the following credentials")
                        .font(.title3.weight(.bold))
                    Text("You choose exactly what to share when you select a document.")
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }

                ReaderTrustBanner(readerAuth: request.readerAuth)

                ForEach(request.docRequests, id: \.docType) { doc in
                    DocRequestCard(doc: doc)
                }
            }
            .padding()
        }
        .safeAreaInset(edge: .bottom) {
            VStack(spacing: 8) {
                // `nil` while matching → treat as "may have a match" so we don't flash a
                // disabled state; only `false` means the wallet holds nothing requested.
                let hasMatch = viewModel.consentMatchAvailable != false

                if viewModel.consentMatchAvailable == false {
                    Label("You don't have any of the requested documents.", systemImage: "exclamationmark.circle")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                        .multilineTextAlignment(.center)
                        .frame(maxWidth: .infinity)
                }

                if viewModel.isRisky(request.readerAuth) {
                    // Untrusted reader: keep Decline emphasised as the primary action.
                    Button("Decline") { viewModel.decline() }
                        .buttonStyle(.borderedProminent)
                        .controlSize(.large)
                        .frame(maxWidth: .infinity)
                    if hasMatch {
                        Button("Continue anyway") { showContinueConfirm = true }
                            .controlSize(.large)
                            .tint(.red)
                    }
                } else if hasMatch {
                    // Decline (negative, outlined red) + Select (primary), equal width.
                    HStack(spacing: 12) {
                        Button("Decline") { viewModel.decline() }
                            .buttonStyle(.bordered)
                            .tint(.red)
                            .controlSize(.large)
                            .frame(maxWidth: .infinity)
                        Button(selectLabel) { viewModel.onConsent() }
                            .buttonStyle(.borderedProminent)
                            .controlSize(.large)
                            .frame(maxWidth: .infinity)
                    }
                } else {
                    // Nothing to share → Decline becomes the primary action.
                    Button("Decline") { viewModel.decline() }
                        .buttonStyle(.borderedProminent)
                        .controlSize(.large)
                        .frame(maxWidth: .infinity)
                }
            }
            .frame(maxWidth: .infinity)
            .padding()
            .background(.bar)
        }
        .alert("Continue with an unverified reader?", isPresented: $showContinueConfirm) {
            Button("Continue anyway", role: .destructive) { viewModel.onConsent() }
            Button("Cancel", role: .cancel) {}
        } message: {
            Text("This reader's identity could not be verified. You'll still choose what to share next — only continue if you know and trust who you are sharing with.")
        }
    }
}

private struct DocRequestCard: View {
    let doc: DocRequest

    var body: some View {
        VStack(alignment: .leading, spacing: 0) {
            HStack(spacing: 12) {
                Image(systemName: iconForDocType(doc.docType))
                    .font(.title3)
                    .foregroundStyle(.white)
                    .frame(width: 36, height: 36)
                    .background(Color.accentColor.gradient)
                    .clipShape(RoundedRectangle(cornerRadius: 8))
                VStack(alignment: .leading, spacing: 2) {
                    Text(displayNameForDocType(doc.docType)).font(.headline)
                    Text(doc.docType).font(.caption).foregroundStyle(.secondary)
                }
                Spacer()
            }
            .padding()
            Divider()
            ForEach(Array(doc.requestedItems.keys.sorted()), id: \.self) { ns in
                let items = doc.requestedItems[ns] ?? []
                ForEach(Array(items.enumerated()), id: \.offset) { _, item in
                    HStack {
                        Text(formatClaimName(item.elementIdentifier)).font(.subheadline)
                        Spacer()
                        if item.intentToRetain { RetainPill() }
                    }
                    .padding(.horizontal)
                    .padding(.vertical, 10)
                    Divider().padding(.leading)
                }
            }
        }
        .background(Color(.secondarySystemGroupedBackground))
        .clipShape(RoundedRectangle(cornerRadius: 12))
    }
}

// MARK: - Disclosure step

private struct DisclosureStep: View {
    @ObservedObject var viewModel: ProximityPresentationViewModel
    let request: RespondableProximityRequest
    let matching: Bool
    let selections: [ProximityPresentationViewModel.DocSelection]

    private var readyToSend: Bool { !selections.isEmpty && selections.allSatisfy { $0.isReady } }

    var body: some View {
        if matching {
            VStack(spacing: 24) {
                Spacer()
                ProgressView().controlSize(.large)
                Text("Finding credentials…").foregroundStyle(.secondary)
                Spacer()
                Button("Back") { viewModel.backToReview() }.padding(.bottom)
            }
        } else {
            ScrollView {
                VStack(alignment: .leading, spacing: 16) {
                    ReaderTrustBanner(readerAuth: request.readerAuth)
                    ForEach(selections) { selection in
                        DocSelectionCard(viewModel: viewModel, selection: selection)
                    }
                }
                .padding()
            }
            .safeAreaInset(edge: .bottom) {
                VStack(spacing: 8) {
                    Button("Send") { viewModel.submitDisclosure() }
                        .buttonStyle(.borderedProminent)
                        .controlSize(.large)
                        .disabled(!readyToSend)
                    Button("Back") { viewModel.backToReview() }
                        .controlSize(.large)
                }
                .frame(maxWidth: .infinity)
                .padding()
                .background(.bar)
            }
        }
    }
}

private struct DocSelectionCard: View {
    @ObservedObject var viewModel: ProximityPresentationViewModel
    let selection: ProximityPresentationViewModel.DocSelection

    var body: some View {
        VStack(alignment: .leading, spacing: 0) {
            HStack(spacing: 12) {
                Image(systemName: iconForDocType(selection.docRequest.docType))
                    .font(.title3)
                    .foregroundStyle(.white)
                    .frame(width: 36, height: 36)
                    .background(Color.accentColor.gradient)
                    .clipShape(RoundedRectangle(cornerRadius: 8))
                Text(displayNameForDocType(selection.docRequest.docType)).font(.headline)
                Spacer()
                if selection.isReady {
                    Image(systemName: "checkmark.circle.fill").foregroundStyle(.green)
                }
            }
            .padding()
            Divider()

            if selection.candidates.isEmpty {
                EmptyCandidates()
            } else {
                SectionLabel("Choose a credential")
                ForEach(Array(selection.candidates.enumerated()), id: \.offset) { index, _ in
                    Button {
                        viewModel.selectCandidate(docType: selection.docRequest.docType, index: index)
                    } label: {
                        HStack {
                            Image(
                                systemName: index == selection.selectedIndex
                                    ? "largecircle.fill.circle" : "circle"
                            )
                            .foregroundStyle(index == selection.selectedIndex ? Color.accentColor : .secondary)
                            Text(
                                selection.candidates.count > 1
                                    ? "\(displayNameForDocType(selection.docRequest.docType)) (#\(index + 1))"
                                    : displayNameForDocType(selection.docRequest.docType)
                            )
                            .foregroundStyle(.primary)
                            Spacer()
                        }
                        .padding(.horizontal).padding(.vertical, 10)
                    }
                    Divider().padding(.leading)
                }

                SectionLabel("Fields to share")
                let candidatePicked = selection.selectedIndex != nil
                ForEach(Array(selection.docRequest.requestedItems.keys.sorted()), id: \.self) { ns in
                    let items = selection.docRequest.requestedItems[ns] ?? []
                    ForEach(Array(items.enumerated()), id: \.offset) { _, item in
                        let checked = selection.selectedItems[ns]?.contains(item.elementIdentifier) ?? false
                        Button {
                            viewModel.toggleItem(
                                docType: selection.docRequest.docType,
                                namespace: ns, item: item.elementIdentifier)
                        } label: {
                            HStack {
                                Image(systemName: checked ? "checkmark.square.fill" : "square")
                                    .foregroundStyle(checked ? Color.accentColor : .secondary)
                                Text(formatClaimName(item.elementIdentifier))
                                    .foregroundStyle(candidatePicked ? .primary : .secondary)
                                Spacer()
                                if item.intentToRetain { RetainPill() }
                            }
                            .padding(.horizontal).padding(.vertical, 8)
                        }
                        .disabled(!candidatePicked)
                    }
                }
            }
        }
        .background(Color(.secondarySystemGroupedBackground))
        .clipShape(RoundedRectangle(cornerRadius: 12))
    }
}

private struct EmptyCandidates: View {
    var body: some View {
        VStack(spacing: 8) {
            Image(systemName: "doc.questionmark")
                .font(.title2)
                .foregroundStyle(.secondary)
            Text("No matching credentials").font(.subheadline.weight(.semibold))
            Text("You don't have a document that satisfies this request.")
                .font(.footnote)
                .foregroundStyle(.secondary)
                .multilineTextAlignment(.center)
        }
        .frame(maxWidth: .infinity)
        .padding()
    }
}

// MARK: - QR step

private struct QrStep: View {
    let mdocUri: String

    var body: some View {
        VStack(spacing: 20) {
            Spacer()
            Text("Show this QR to the reader")
                .font(.title3.weight(.semibold))
            // QR must stay dark-on-light to scan, regardless of light/dark mode.
            QRCodeView(content: mdocUri)
                .frame(width: 240, height: 240)
                .padding(20)
                .background(Color.white)
                .clipShape(RoundedRectangle(cornerRadius: 20))
            Label("Hold steady near the reader to scan", systemImage: "qrcode.viewfinder")
                .font(.footnote)
                .foregroundStyle(.secondary)
            Spacer()
        }
        .padding()
    }
}

private struct QRCodeView: View {
    let content: String
    @State private var image: UIImage?

    var body: some View {
        Group {
            if let image {
                Image(uiImage: image)
                    .interpolation(.none)
                    .resizable()
                    .scaledToFit()
            } else {
                Color.clear  // reserve layout until the QR is generated
            }
        }
        .accessibilityHidden(true)
        // Generate once per content value (off the render path) and cache, instead of
        // re-encoding via CIFilter on every body re-render.
        .task(id: content) { image = Self.generate(content) }
    }

    private static func generate(_ content: String) -> UIImage {
        let context = CIContext()
        let filter = CIFilter.qrCodeGenerator()
        filter.message = Data(content.utf8)
        filter.correctionLevel = "L"  // matches the SDK's engagement QR (ISO 18013-5 §8.2.2.3)
        if let output = filter.outputImage,
            let cg = context.createCGImage(output, from: output.extent)
        {
            return UIImage(cgImage: cg)
        }
        return UIImage()
    }
}

// MARK: - Small shared bits

private struct RetainPill: View {
    var body: some View {
        Text("Will retain")
            .font(.caption2.weight(.medium))
            .padding(.horizontal, 6).padding(.vertical, 2)
            .background(Color.accentColor.opacity(0.15))
            .foregroundStyle(Color.accentColor)
            .clipShape(Capsule())
    }
}

private struct SectionLabel: View {
    let text: String
    init(_ text: String) { self.text = text }
    var body: some View {
        Text(text.uppercased())
            .font(.caption.weight(.semibold))
            .foregroundStyle(.secondary)
            .frame(maxWidth: .infinity, alignment: .leading)
            .padding(.horizontal).padding(.vertical, 8)
    }
}

// docType display name / icon / claim-name formatting live in DisplayHelpers.swift,
// shared with the proximity-reading screen.
