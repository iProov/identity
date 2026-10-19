//
//  DocumentProviderExtension.swift
//  IdentityDocumentProviderExtension
//
//  Created by Owen Woodward on 21/08/2026.
//

import ExtensionKit
import IdentityDocumentServices
import IdentityDocumentServicesUI
import LocalAuthentication
import Security
import SwiftUI
import identity

@main
struct DocumentProviderExtension: IdentityDocumentProvider {

    var body: some IdentityDocumentRequestScene {
        ISO18013MobileDocumentRequestScene { context in
            IdentityDocumentRequestView(context: context)
        }
    }

    /// Required by `IdentityDocumentProvider`, and left empty.
    ///
    /// Reasoning: The containing app owns registrations: via the SDK - `registerAllCredentialsForDCApi()`
    /// This reconciles on every credential load, adding what is missing and removing what is stale.
    func performRegistrationUpdates() async {}
}

// MARK: - View

struct IdentityDocumentRequestView: View {
    let context: ISO18013MobileDocumentRequestContext

    @State private var isAuthorizing = false
    @State private var authorizationError: String?
    @State private var disclosure: [DocSelection]?
    @State private var readerAuth: ReaderAuth?
    @State private var picks: CheckedContinuation<[DocRequest: DisclosedDocument], Never>?


    var body: some View {
        NavigationStack {
            Group {
                if let disclosure {
                    disclosureSheet(disclosure)
                } else {
                    consentSheet
                }
            }
            .navigationTitle(disclosure == nil ? "Share document" : "Choose what to share")
            .navigationBarTitleDisplayMode(.inline)
        }
        .onDisappear { declineDisclosure() }
    }

    /// Notifies who  is asking and what they want, before anything is unlocked (via biometrics/passcode etc)
    @ViewBuilder
    private var consentSheet: some View {
        List {
            requesterSection

            ForEach(Array(groups.enumerated()), id: \.element.id) { index, group in
                presentmentSection(group, index: index)
            }

            if let authorizationError {
                Section {
                    Text(authorizationError)
                        .font(.footnote)
                        .foregroundStyle(.red)
                }
            }
            actionsSection
        }
    }

    // MARK: Requester

    /// Who is asking. The origin comes from the browser via the OS.
    ///
    /// The name below is only what the request's certificate claims — this screen renders before
    /// the SDK has the request, so mdoc reader authentication has not run yet. The verified
    /// result appears on the disclosure step as [ReaderAuth].
    @ViewBuilder
    private var requesterSection: some View {
        Section {
            LabeledContent("Website") {
                Text(context.requestingWebsiteOrigin?.host ?? "unknown")
                    .font(.footnote.monospaced())
            }
            LabeledContent("Certificate name") {
                Text(certificateName ?? "None supplied")
                    .foregroundStyle(certificateName == nil ? .secondary : .primary)
            }
        } header: {
            Text("Requested by")
        } footer: {
            Text(certificateName == nil
                 ? "This request supplied no reader certificate."
                 : "Not yet checked against your trusted readers.")
        }
    }

    /// Apple's `requestAuthentications` authenticates the website request, which is a different
    /// thing from the ISO 18013-5 `readerAuth` inside the CBOR DeviceRequest.
    private var certificateName: String? {
        guard let leaf = context.request.requestAuthentications
            .first?.authenticationCertificateChain.first
        else { return nil }
        return SecCertificateCopySubjectSummary(leaf) as String?
    }

    // MARK: Requested data

    @ViewBuilder
    private func presentmentSection(_ group: PresentmentGroup, index: Int) -> some View {
        ForEach(Array(group.alternatives.enumerated()), id: \.element.id) { altIndex, alternative in
            ForEach(alternative.documents) { document in
                Section {
                    ForEach(Array(document.namespaces.enumerated()), id: \.offset) { _, ns in
                        ForEach(Array(ns.elements.enumerated()), id: \.offset) { _, element in
                            HStack(alignment: .firstTextBaseline) {
                                Text(ExtensionHelpers.displayName(for: element.name))
                                Spacer()
                                if element.isRetaining {
                                    Text("stored")
                                        .font(.caption2.weight(.semibold))
                                        .foregroundStyle(.orange)
                                }
                            }
                        }
                    }
                } header: {
                    HStack {
                        Text(ExtensionHelpers.documentDisplayName(document.documentType))
                        if !group.isMandatory {
                            Text("optional").font(.caption2).foregroundStyle(.secondary)
                        }

                        if group.alternatives.count > 1 {
                            Text("option \(altIndex + 1) of \(group.alternatives.count)")
                                .font(.caption2).foregroundStyle(.secondary)
                        }
                    }
                } footer: {
                    if document.retainsAnything {
                        Text("Items marked “stored” will be kept by the requester after this "
                             + "check, rather than used once and discarded.")
                    }
                }
            }
        }
    }

    // MARK: Actions

    @ViewBuilder
    private var actionsSection: some View {
        Section {
            Button {
                Task { await approve() }
            } label: {
                HStack {
                    Text("Approve and share")
                    if isAuthorizing { Spacer(); ProgressView() }
                }
            }
            .disabled(isAuthorizing)

            Button("Don't share", role: .cancel) { context.cancel() }
                .disabled(isAuthorizing)
        }
    }

    private func approve() async {
        isAuthorizing = true
        defer { isAuthorizing = false }

        let authContext = LAContext()
        authContext.localizedFallbackTitle = ""

        do {
            guard try await authContext.evaluatePolicy(
                .deviceOwnerAuthentication,
                localizedReason: "Confirm it's you before sharing your document"
            ) else { return }

            try await context.sendResponse { rawRequest in
                try await buildResponse(requestData: rawRequest.requestData)
            }
        } catch let error as LAError where error.code == .userCancel {
            return
        } catch {
            authorizationError = error.localizedDescription
            NSLog("Response failed inside `approve`: \(error)")
        }
    }


    /// Called by `sendResponse` once the system has authenticated the user.
    @MainActor
    private func buildResponse(requestData: Data) async throws -> ISO18013MobileDocumentResponse {
        let request = try await parseRequest(requestData)
        let candidates = try await findCandidates(for: request)
        let chosen = await askUserWhatToShare(request, candidates: candidates)
        return ISO18013MobileDocumentResponse(
            responseData: try await request.respond(disclosed: chosen))
    }

    private func parseRequest(_ requestData: Data) async throws -> RespondableDigitalCredentialsRequest {
        guard let origin = context.requestingWebsiteOrigin else {
            throw ResponseError.missingOrigin
        }
        guard let requestJson = String(data: requestData, encoding: .utf8) else {
            throw ResponseError.malformedRequest
        }
        return try await ExtensionWallet.shared.get().digitalCredentialsRequest(
            requestJson: requestJson, origin: origin)
    }

    /// Which stored credentials can satisfy each requested document, keyed by docType
    private func findCandidates(
        for request: RespondableDigitalCredentialsRequest
    ) async throws -> [String: [DisclosedDocument]] {
        var byDocType: [String: [DisclosedDocument]] = [:]
        for (docRequest, matches) in try await request.match() {
            byDocType[docRequest.docType] = matches
        }
        guard byDocType.values.contains(where: { !$0.isEmpty }) else {
            throw ResponseError.noMatchingCredential
        }
        return byDocType
    }

    /// Shows the disclosure sheet, then suspends until `share()` or `declineDisclosure()` resumes it with the user's answer.
    private func askUserWhatToShare(
        _ request: RespondableDigitalCredentialsRequest,
        candidates: [String: [DisclosedDocument]]
    ) async -> [DocRequest: DisclosedDocument] {
        // Only the sheet's buttons resume otherwise: a cancelled request would hold the handler until teardown.
        await withTaskCancellationHandler {
            await withCheckedContinuation { continuation in
                picks = continuation
                readerAuth = request.readerAuth
                disclosure = request.docRequests.map {
                    DocSelection($0, candidates: candidates[$0.docType] ?? [])
                }
            }
        } onCancel: {
            Task { @MainActor in declineDisclosure() }
        }
    }

    // MARK: Answering the sheet

    private func share() { resume(with: chosenDocuments()) }

    /// Sends an empty disclosure. The SDK turns that into documentErrors code 0
    private func declineDisclosure() { resume(with: [:]) }

    /// One entry per document the user actually chose. Assigning a nil `pickedCredential`
    /// leaves the key out, so unpicked documents are simply absent.
    private func chosenDocuments() -> [DocRequest: DisclosedDocument] {
        guard let disclosure else { return [:] }
        return disclosure.reduce(into: [:]) { chosen, selection in
            chosen[selection.docRequest] = selection.pickedCredential
        }
    }

    /// Resumes the suspended `sendResponse` handler exactly once.
    private func resume(with chosen: [DocRequest: DisclosedDocument]) {
        let continuation = picks
        picks = nil
        disclosure = nil
        readerAuth = nil
        continuation?.resume(returning: chosen)
    }

    // MARK: Disclosure sheet

    @ViewBuilder
    private func readerTrustSection(_ auth: ReaderAuth) -> some View {
        let (icon, tint, title, detail): (String, Color, String, String) = {
            switch auth {
            case let trusted as ReaderAuthTrusted:
                return ("checkmark.seal.fill", .green, trusted.commonName,
                        "Verified against your trusted readers.")
            case let untrusted as ReaderAuthUntrusted:
                return ("exclamationmark.triangle.fill", .orange,
                        untrusted.commonName ?? "Unidentified reader",
                        "Signature is valid but this reader is not on your trust list.")
            case is ReaderAuthSignatureInvalid:
                return ("xmark.seal.fill", .red, "Invalid signature",
                        "This request's reader signature failed verification.")
            default:
                return ("questionmark.circle.fill", .secondary, "Unsigned request",
                        "This request carried no reader authentication.")
            }
        }()

        Section {
            HStack(alignment: .firstTextBaseline, spacing: 10) {
                Image(systemName: icon).foregroundStyle(tint)
                VStack(alignment: .leading, spacing: 2) {
                    Text(title).font(.subheadline.weight(.semibold))
                    Text(detail).font(.caption).foregroundStyle(.secondary)
                }
            }
        } header: {
            Text("Reader")
        }
    }

    @ViewBuilder
    private func disclosureSheet(_ selections: [DocSelection]) -> some View {
        List {
            if let readerAuth {
                readerTrustSection(readerAuth)
            }

            ForEach(selections) { selection in
                Section {
                    if selection.candidates.isEmpty {
                        Text("You don't have a document that satisfies this request.")
                            .font(.footnote)
                            .foregroundStyle(.secondary)
                    } else {
                        credentialPicker(selection)
                        elementCheckboxes(selection)
                    }
                } header: {
                    Text(ExtensionHelpers.documentDisplayName(selection.docRequest.docType))
                }
            }

            Section {
                Button("Share") { share() }
                    .disabled(!selections.contains { $0.isReady })
                Button("Don't share", role: .cancel) { declineDisclosure() }
            }
        }
    }

    @ViewBuilder
    private func credentialPicker(_ selection: DocSelection) -> some View {
        let choosing = selection.candidates.count > 1

        if choosing {
            Text("Choose a document")
                .font(.caption.weight(.semibold))
                .foregroundStyle(.secondary)
        }

        ForEach(selection.candidates.indices, id: \.self) { index in
            let picked = index == selection.selectedIndex
            Button {
                select(id: selection.id, index: index)
            } label: {
                HStack(spacing: 10) {
                    Image(systemName: choosing
                          ? (picked ? "largecircle.fill.circle" : "circle")
                          : "checkmark.circle.fill")
                        .foregroundStyle(picked ? Color.accentColor : .secondary)
                    VStack(alignment: .leading, spacing: 2) {
                        Text(selection.title(forCandidate: index))
                            .font(.subheadline.weight(.semibold))
                            .foregroundStyle(.primary)
                        Text(selection.subtitle(forCandidate: index))
                            .font(.caption)
                            .foregroundStyle(.secondary)
                    }
                    Spacer()
                }
            }
            .disabled(!choosing)
        }
    }

    /// Which of the requested elements to actually release.
    @ViewBuilder
    private func elementCheckboxes(_ selection: DocSelection) -> some View {
        ForEach(selection.itemRows) { row in
            Button {
                toggle(id: selection.id,
                       namespace: row.namespace, element: row.element)
            } label: {
                HStack(alignment: .firstTextBaseline) {
                    Image(systemName: row.checked ? "checkmark.square.fill" : "square")
                    Text(ExtensionHelpers.displayName(for: row.element)).foregroundStyle(.primary)
                    Spacer()
                    if row.intentToRetain {
                        Text("stored")
                            .font(.caption2.weight(.semibold))
                            .foregroundStyle(.orange)
                    }
                }
            }
            .disabled(selection.selectedIndex == nil)
        }
    }

    // MARK: Claim Toggles
    /// What the user wants to share and not to share in checkboxes

    private func select(id: DocSelection.ID, index: Int) {
        update(id) { selection in
            guard index < selection.candidates.count else { return }
            selection.selectedIndex = index
        }
    }

    private func toggle(id: DocSelection.ID, namespace: String, element: String) {
        update(id) { selection in
            var ticked = selection.selectedItems[namespace] ?? []
            if ticked.contains(element) { ticked.remove(element) } else { ticked.insert(element) }
            selection.selectedItems[namespace] = ticked
        }
    }

    private func update(_ id: DocSelection.ID, _ change: (inout DocSelection) -> Void) {
        guard var selections = disclosure,
              let index = selections.firstIndex(where: { $0.id == id })
        else { return }
        change(&selections[index])
        disclosure = selections
    }

    // MARK: Structure

    private var groups: [PresentmentGroup] {
        context.request.presentmentRequests.map { presentment in
            PresentmentGroup(
                isMandatory: presentment.isMandatory,
                alternatives: presentment.documentRequestSets.map { set in
                    DocumentAlternative(
                        documents: set.requests.map { request in
                            RequestedDocument(
                                documentType: request.documentType,
                                namespaces: request.namespaces
                                    .sorted { $0.key < $1.key }
                                    .map { namespace, elements in
                                        (namespace: namespace,
                                         elements: elements
                                            .sorted { $0.key < $1.key }
                                            .map { (name: $0.key, isRetaining: $0.value.isRetaining) })
                                    }
                            )
                        }
                    )
                }
            )
        }
    }


}
