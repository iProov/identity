//
//  CredentialsView.swift
//  iProov Identity Sample App
//
//  Updated to support OID4VCI credentials alongside legacy credentials.
//

import Foundation
import SwiftUI
import identity

// MARK: - OID4VCI Stored Credentials

struct StoredCredentialsSection: View {
    let summary: CredentialSummary
    let registeredUuids: Set<String>
    let onDelete: (CredentialMetadata) -> Void

    private var readyItems: [StoredCredentialItem] {
        summary.credentials.map { StoredCredentialItem(metadata: $0.key, credential: $0.value) }
            .sorted { $0.metadata.addedAt > $1.metadata.addedAt }
    }

    private var failureItems: [CredentialFailureItem] {
        summary.failures.map { CredentialFailureItem(metadata: $0.key, failure: $0.value) }
            .sorted { $0.metadata.addedAt > $1.metadata.addedAt }
    }

    var body: some View {
        Group {
            if readyItems.isEmpty && failureItems.isEmpty {
                Section("Credentials") {
                    Text("No have been added yet.")
                        .foregroundStyle(.secondary)
                }
            } else {
                if !readyItems.isEmpty {
                    Section("Credentials") {
                        ForEach(readyItems) { item in
                            StoredCredentialRow(
                                item: item,
                                isRegisteredForDCApi: registeredUuids.contains(item.metadata.uuid),
                                onDelete: onDelete
                            )
                            // Invisible link keeps the row tappable while the row draws its own
                            // chevron, so the options menu and the chevron share one column.
                            .background(
                                NavigationLink { StoredCredentialDetailView(item: item) } label: { EmptyView() }
                                    .opacity(0)
                            )
                        }
                    }
                }

                if !failureItems.isEmpty {
                    Section("Credential Errors") {
                        ForEach(failureItems) { failure in
                            NavigationLink {
                                CredentialFailureDetailView(failure: failure, onDelete: onDelete)
                            } label: {
                                CredentialFailureRow(failure: failure, onDelete: onDelete)
                            }
                        }
                    }
                }
            }
        }
    }
}

struct DigitalCredentialsSection: View {
    let status: DCApiStatus
    let onSync: () -> Void
    let showSettingsLink: Bool

    /// `default` rather than an exhaustive switch: DCApiStatus is a Kotlin enum exported as a class,
    /// so Swift cannot prove the cases are complete.
    private var statusDescription: String {
        switch status {
            case .authorized:           "Active"
            case .notDetermined:        "Not yet requested"
            case .notAuthorized:        "Turned off in Settings"
            case .notSupported:         "Not supported for these document types"
            case .unsupportedOsVersion: "Requires iOS 26"
            case .notConfigured:        "Not enabled: the storage engine has no keychain access group"
            default:                    status.name
        }
    }

    var body: some View {
        Section {
            HStack {
                Text("Status: ") + Text(statusDescription)
                                .font(.footnote)
                                .foregroundStyle(.secondary)
            }
            Button("Sync registrations", action: onSync)

            if showSettingsLink {
                            Button("Open Settings") {
                                if let url = URL(string: UIApplication.openSettingsURLString) {
                                    UIApplication.shared.open(url)
                                }
                            }
                        }
        } header: {
            Text("Digital Credentials API")
        } footer: {
            Text("Registers mDoc credentials with iOS so websites can request them. "
                 + "Requires iOS 26 and a doctype listed in the app's entitlement.")
        }
    }
}

private struct StoredCredentialItem: Identifiable {
    let metadata: CredentialMetadata
    let credential: any Credential

    var id: String { metadata.uuid }
}

private struct CredentialFailureItem: Identifiable {
    let metadata: CredentialMetadata
    let failure: any CredentialRetrievalFailure

    var id: String { metadata.uuid }

}

private struct StoredCredentialRow: View {
    let item: StoredCredentialItem
    let isRegisteredForDCApi: Bool
    let onDelete: (CredentialMetadata) -> Void

    @StateObject private var verification = CredentialVerificationModel()

    private var display: DisplayProperties? { item.metadata.bestDisplay }

    private var format: String {
        item.credential.format.value
    }

    private var issuerName: String {
        item.metadata.issuer.name
    }

    var body: some View {
        HStack(alignment: .top, spacing: 12) {
            VStack(alignment: .leading, spacing: 8) {
                VStack(alignment: .leading, spacing: 2) {
                    Text(display?.name ?? "Credential")
                        .font(.headline)
                    Text(issuerName)
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }

                VStack(alignment: .leading, spacing: 5) {
                    Text("Format: \(format)")
                        .font(.footnote)
                        .foregroundStyle(.secondary)

                    if let addedDate = formattedDate(milliseconds: item.metadata.addedAt) {
                        Text("Added: \(addedDate)")
                            .font(.footnote)
                            .foregroundStyle(.secondary)
                    }

                    HStack(spacing: 12) {
                        // Verified on appear, as the Android card is; the detail screen shows each check.
                        CompactVerificationBadge(phase: verification.phase)

                        // Only mdocs can be registered, so a "Not registered" label on an SD-JWT would
                        // read as a problem rather than a fact about the format.
                        if item.credential is MDocCredential {
                            Label(
                                isRegisteredForDCApi ? "Registered with DC-API" : "Not registered with DC-API",
                                systemImage: isRegisteredForDCApi ? "checkmark.seal.fill" : "seal"
                            )
                            .labelStyle(TightLabelStyle())
                            .font(.caption)
                            .foregroundStyle(isRegisteredForDCApi ? .green : .secondary)
                        }
                    }
                    .padding(.top, 6)
                }
            }

            Spacer(minLength: 0)

            // Menu pinned to the top; chevron centred in the row like the system indicator.
            ZStack(alignment: .top) {
                Image(systemName: "chevron.right")
                    .font(.footnote.weight(.semibold))
                    .foregroundStyle(.tertiary)
                    .frame(maxHeight: .infinity)
                Menu {
                    Button(role: .destructive) {
                        onDelete(item.metadata)
                    } label: {
                        Label("Delete", systemImage: "trash")
                    }
                } label: {
                    Image(systemName: "ellipsis.circle")
                        .imageScale(.large)
                }
            }
            .frame(maxHeight: .infinity)
        }
        .padding(.vertical, 6)
        .task(id: item.id) { await verification.verify(item.credential) }
    }
}

//Helper function for Icon/Text alignment
private struct TightLabelStyle: LabelStyle {
    var spacing: CGFloat = 3

    func makeBody(configuration: Configuration) -> some View {
        HStack(spacing: spacing) {
            configuration.icon
            configuration.title
        }
    }
}

private struct CredentialFailureRow: View {
    let failure: CredentialFailureItem
    let onDelete: (CredentialMetadata) -> Void

    private var display: DisplayProperties? { failure.metadata.bestDisplay }
    private var issuerName: String { failure.metadata.issuer.name }
    private var format: String { failure.metadata.format }
    private var addedDate: String? { formattedDate(milliseconds: failure.metadata.addedAt) }

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            HStack(alignment: .firstTextBaseline) {
                VStack(alignment: .leading, spacing: 2) {
                    Text(display?.name ?? "Credential Error")
                        .font(.headline)
                        .lineLimit(1)
                    Text(issuerName)
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                        .lineLimit(1)
                }
                Spacer()
                Menu {
                    Button(role: .destructive) {
                        onDelete(failure.metadata)
                    } label: {
                        Label("Delete", systemImage: "trash")
                    }
                } label: {
                    Image(systemName: "ellipsis.circle")
                        .imageScale(.large)
                        .padding(.leading, 4)
                }
            }

            VStack(alignment: .leading, spacing: 4) {
                Text(failure.failure.error)
                    .font(.subheadline)
                Text(failure.failure.description_)
                    .font(.footnote)
                    .foregroundStyle(.secondary)

                Text("Format: \(format)")
                    .font(.footnote)
                    .foregroundStyle(.secondary)

                if let addedDate {
                    Text("Added: \(addedDate)")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                }
            }
        }
        .padding(.vertical, 6)
    }
}

private struct StoredCredentialDetailView: View {
    let item: StoredCredentialItem

    @StateObject private var verification = CredentialVerificationModel()

    private var display: DisplayProperties? { item.metadata.bestDisplay }

    var body: some View {
        List {
            VerificationSection(model: verification, credential: item.credential)

            Section("Overview") {
                DetailRow(label: "Name", value: display?.name)
                DetailRow(label: "Issuer", value: item.metadata.issuer.name)
                DetailRow(label: "Format", value: item.credential.format.value)
                DetailRow(label: "UUID", value: item.metadata.uuid)
                if let added = formattedDate(milliseconds: item.metadata.addedAt) {
                    DetailRow(label: "Added", value: added)
                }
            }

            if let mdoc = item.credential as? MDocCredential {
                Section("mdoc") {
                    DetailRow(label: "Doc Type", value: mdoc.docType)
                    NavigationLink("View Raw Claims") {
                        MDocClaimsView(nameSpaces: mdoc.nameSpaces)
                    }
                }
            } else if let sdjwt = item.credential as? SdJwtVcCredential {
                Section("SDJWT-VC") {
                    DetailRow(label: "Doc Type", value: sdjwt.vct)
                    NavigationLink("View Raw Claims") {
                        SDJwtClaimsView(nameSpaces: sdjwt.body)
                    }
                }
            }

            Section("Raw Credential") {
                ScrollView {
                    Text(item.credential.raw)
                        .font(.footnote)
                        .textSelection(.enabled)
                        .frame(maxWidth: .infinity, alignment: .leading)
                        .padding(.vertical, 4)
                }
            }
        }
        .navigationTitle(display?.name ?? "Credential")
        .task { await verification.verify(item.credential) }
    }
}

private struct CredentialFailureDetailView: View {
    let failure: CredentialFailureItem
    let onDelete: (CredentialMetadata) -> Void

    private var display: DisplayProperties? { failure.metadata.bestDisplay }
    private var offerDescription: String { String(describing: failure.metadata.offer) }
    private var addedDate: String? { formattedDate(milliseconds: failure.metadata.addedAt) }

    private var serializationFailure: CredentialRetrievalFailureSerializationFailed? {
        failure.failure as? CredentialRetrievalFailureSerializationFailed
    }

    private var unsupportedFormat: CredentialRetrievalFailureUnsupportedFormat? {
        failure.failure as? CredentialRetrievalFailureUnsupportedFormat
    }

    private var causeMessage: String? {
        guard let cause = serializationFailure?.cause else { return nil }
        if let message = cause.message {
            return message
        }
        return String(describing: cause)
    }

    var body: some View {
        List {
            Section("Overview") {
                DetailRow(label: "Name", value: display?.name ?? "Credential Error")
                DetailRow(label: "Issuer", value: failure.metadata.issuer.name)
                DetailRow(label: "Format", value: failure.metadata.format)
                DetailRow(label: "UUID", value: failure.metadata.uuid)
                if let addedDate {
                    DetailRow(label: "Added", value: addedDate)
                }
            }

            Section("Error Details") {
                DetailRow(label: "Error", value: failure.failure.error)
                DetailRow(label: "Description", value: failure.failure.description_)

                if let unsupportedFormat {
                    DetailRow(label: "Unsupported Format", value: unsupportedFormat.format)
                }

                if let causeMessage {
                    DetailRow(label: "Cause", value: causeMessage)
                }
            }

            Section("Raw Data") {
                ScrollView {
                    Text(offerDescription)
                        .font(.footnote)
                        .textSelection(.enabled)
                        .frame(maxWidth: .infinity, alignment: .leading)
                        .padding(.vertical, 4)
                }
            }

            Section("Actions") {
                Button(role: .destructive) {
                    onDelete(failure.metadata)
                } label: {
                    Text("Delete Credential")
                }
            }
        }
        .navigationTitle(display?.name ?? "Credential Error")
    }
}

private struct DetailRow: View {
    let label: String
    let value: String?

    var body: some View {
        HStack {
            Text(label)
                .font(.subheadline)
                .foregroundStyle(.secondary)
            Spacer()
            Text(value ?? "—")
                .font(.subheadline)
                .multilineTextAlignment(.trailing)
        }
    }
}

private struct MDocClaimsView: View {
    let nameSpaces: [String: [String: Any]]
    

    var body: some View {

        List {
            ForEach(nameSpaces.keys.sorted(), id: \.self) { namespace in
                Section(namespace) {
                    let attrs = nameSpaces[namespace] ?? [:]
                    ForEach(attrs.keys.sorted(), id: \.self) { key in
                        VStack(alignment: .leading, spacing: 4) {
                            Text(key)
                                .font(.headline)
                            
                            let text = attrs[key].map { String(describing: $0) } ?? "null"
                            Text(text)
                                .font(.footnote)
                                .foregroundStyle(.secondary)
                                .textSelection(.enabled)

                        }
                        .padding(.vertical, 4)
                    }
                }
            }
        }
        .navigationTitle("Claims")
    }
}

private struct SDJwtClaimsView: View {
    let nameSpaces: [String: Any]
    

    var body: some View {

        List {
            ForEach(nameSpaces.keys.sorted(), id: \.self) { key in
                VStack(alignment: .leading, spacing: 4) {
                    Text(key)
                        .font(.headline)
                    
                    let text = nameSpaces[key].map { String(describing: $0) } ?? "null"
                    Text(text)
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                        .textSelection(.enabled)
                    
                }
                .padding(.vertical, 4)
            }
        }
        .navigationTitle("Claims")
    }
}


// MARK: - Legacy Credentials

struct LegacyCredentialsSection: View {
    let credentials: [LegacyCredential]
    let deleteCredential: (LegacyCredential) -> Void
    let verifyCredential: (LegacyCredential) -> Void

    private var items: [LegacyCredentialItem] {
        credentials.map { LegacyCredentialItem(credential: $0) }
    }

    var body: some View {
        Group {
            if items.isEmpty {
                Section("Legacy Credentials") {
                    Text("No legacy credentials.")
                        .foregroundStyle(.secondary)
                }
            } else {
                Section("Legacy Credentials") {
                    ForEach(items) { item in
                        NavigationLink {
                            LegacyCredentialDetailView(
                                item: item,
                                onVerify: verifyCredential,
                                onDelete: deleteCredential
                            )
                        } label: {
                            LegacyCredentialRow(
                                item: item,
                                onVerify: verifyCredential,
                                onDelete: deleteCredential
                            )
                        }
                    }
                }
            }
        }
    }
}

private struct LegacyCredentialItem: Identifiable {
    let credential: LegacyCredential

    var id: String { credential.id }
    var source: String { credential.source }
    var claims: [Claim] { credential.claims }


    var title: String {
        sourceLabel.uppercased(with: .autoupdatingCurrent)
    }

    var subtitle: String {
        source
    }

    private var sourceLabel: String {
        source.split(separator: ":").first.map { String($0).capitalized } ?? "Legacy Credential"
    }

    var isWalletCredential: Bool {
        source.contains("wallet:")
    }

    var hasDtc: Bool {
        claims.contains { $0.name == "com.svipe:dtc" }
    }

    var hasFaceVerified: Bool {
        claims.contains { $0.name == "com.svipe:face_verified" }
    }

    var faceVerificationAvailable: Bool {
        hasDtc && !hasFaceVerified
    }
}

private struct LegacyCredentialRow: View {
    let item: LegacyCredentialItem
    let onVerify: (LegacyCredential) -> Void
    let onDelete: (LegacyCredential) -> Void

    private var primaryClaimSummary: [Claim] {
        Array(item.claims.prefix(2))
    }

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            HStack(alignment: .firstTextBaseline) {
                VStack(alignment: .leading, spacing: 2) {
                    Text(item.title)
                        .font(.headline)
                        .lineLimit(1)
                    Text(item.subtitle)
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                        .lineLimit(1)
                }
                Spacer()
                if item.faceVerificationAvailable || !item.isWalletCredential {
                    Menu {
                        if item.faceVerificationAvailable {
                            Button("Verify Face") {
                                onVerify(item.credential)
                            }
                        }

                        if !item.isWalletCredential {
                            Button(role: .destructive) {
                                onDelete(item.credential)
                            } label: {
                                Label("Delete", systemImage: "trash")
                            }
                        }
                    } label: {
                        Image(systemName: "ellipsis.circle")
                            .imageScale(.large)
                            .padding(.leading, 4)
                    }
                }
            }

            VStack(alignment: .leading, spacing: 4) {
                if item.faceVerificationAvailable {
                    Text("Face verification available")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                } else if item.hasFaceVerified {
                    Text("Face verified")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                }

                if !item.claims.isEmpty {
                    Text("Claims: \(item.claims.count)")
                        .font(.footnote)
                        .foregroundStyle(.secondary)

                    ForEach(primaryClaimSummary) { claim in
                        Text(summary(for: claim))
                            .font(.footnote)
                            .foregroundStyle(.secondary)
                            .lineLimit(1)
                    }
                }
            }
        }
        .padding(.vertical, 6)
    }

    private func summary(for claim: Claim) -> String {
        let name = claim.displayName ?? claim.name
        if let value = claim.jwt.value {
            let text = String(describing: value)
            if !text.isEmpty {
                var sanitized = text.replacingOccurrences(of: "\n", with: " ")
                sanitized = sanitized.trimmingCharacters(in: .whitespacesAndNewlines)
                if sanitized.count > 60 {
                    let prefix = sanitized.prefix(57)
                    sanitized = "\(prefix)..."
                }
                return "\(name): \(sanitized)"
            }
        }
        return name
    }
}

private struct LegacyCredentialDetailView: View {
    let item: LegacyCredentialItem
    let onVerify: (LegacyCredential) -> Void
    let onDelete: (LegacyCredential) -> Void

    var body: some View {
        List {
            Section("Overview") {
                DetailRow(label: "Source", value: item.subtitle)
                DetailRow(label: "Claims", value: "\(item.claims.count)")

                if item.faceVerificationAvailable {
                    DetailRow(label: "Verification", value: "Face verification available")
                } else if item.hasFaceVerified {
                    DetailRow(label: "Verification", value: "Face verified")
                }
            }

            if !item.claims.isEmpty {
                Section("Claims") {
                    ForEach(item.claims) { claim in
                        NavigationLink {
                            JwtView(displayName: claim.displayName ?? claim.name, jwt: claim.jwt)
                        } label: {
                            VStack(alignment: .leading, spacing: 4) {
                                Text(claim.displayName ?? claim.name)
                                    .font(.headline)
                                Text("Tap to view JWT")
                                    .font(.footnote)
                                    .foregroundStyle(.secondary)
                            }
                        }
                    }
                }
            }

            if item.faceVerificationAvailable || !item.isWalletCredential {
                Section("Actions") {
                    if item.faceVerificationAvailable {
                        Button("Verify Face") {
                            onVerify(item.credential)
                        }
                    }

                    if !item.isWalletCredential {
                        Button(role: .destructive) {
                            onDelete(item.credential)
                        } label: {
                            Text("Delete Credential")
                        }
                    }
                }
            }
        }
        .navigationTitle(item.title)
    }
}
private func formattedDate(milliseconds: Int64) -> String? {
    guard milliseconds > 0 else { return nil }
    let date = Date(timeIntervalSince1970: TimeInterval(milliseconds) / 1000.0)
    let formatter = DateFormatter()
    formatter.dateStyle = .medium
    formatter.timeStyle = .short
    return formatter.string(from: date)
}

// Identity module bridging helpers

extension LegacyCredential: Identifiable {
    public var id: String { source }
}

extension Claim: Identifiable {}

// MARK: - Verification status (mirrors the Android example app's badges and verification details)

// MARK: - Model

/// Runs `getVerificationSummary()` for one credential, held or received, and publishes the outcome.
@MainActor
final class CredentialVerificationModel: ObservableObject {
    enum Phase {
        case idle
        case verifying
        case verified(VerificationSummary)
        case failed(String)
    }

    @Published private(set) var phase: Phase = .idle

    var isVerifying: Bool {
        if case .verifying = phase { return true }
        return false
    }

    func verify(_ credential: any Credential) async {
        await run { try await credential.getVerificationSummary() }
    }

    /// An mDL the proximity reader received: the same summary as a held mDL, so the same badge.
    func verify(_ document: ReceivedMDocCredential) async {
        await run {
            let summary = try await document.getVerificationSummary()
            // No checks, or only the TrustAll warning: no status reference was checked.
            guard summary.results.allSatisfy({
                $0.check == "issuer_trust" && $0.status == .indeterminate
            }) else {
                return summary
            }
            return VerificationSummary(results: summary.results + [
                VerificationResult(
                    check: "status_list",
                    status: .indeterminate,
                    reason: "Credential has no status reference",
                    details: ["cause": "no_status"]
                )
            ])
        }
    }

    private func run(_ summary: () async throws -> VerificationSummary) async {
        if isVerifying { return }
        phase = .verifying
        do {
            phase = .verified(try await summary())
        } catch {
            phase = .failed(error.localizedDescription)
        }
    }
}

// MARK: - Styling

private struct VerificationStyle {
    let label: String
    let systemImage: String
    let color: Color
}

private let verifiedGreen = Color(red: 0.04, green: 0.53, blue: 0.33)  // Android 0xFF0A8754
private let pendingAmber = Color(red: 0.90, green: 0.63, blue: 0.0)    // Android 0xFFE6A000

/// Per-check outcome, labelled as the Android app's verification details rows are.
/// `default` because VerificationStatus is a Kotlin enum exported as a class.
private func resultStyle(_ status: VerificationStatus) -> VerificationStyle {
    switch status {
    case .valid:            return .init(label: "Valid", systemImage: "checkmark.circle.fill", color: verifiedGreen)
    case .expired:          return .init(label: "Expired", systemImage: "exclamationmark.circle.fill", color: .red)
    case .revoked:          return .init(label: "Revoked", systemImage: "exclamationmark.circle.fill", color: .red)
    case .notYetValid:      return .init(label: "Not yet valid", systemImage: "hourglass.bottomhalf.filled", color: pendingAmber)
    case .issuerUntrusted:  return .init(label: "Issuer untrusted", systemImage: "exclamationmark.triangle.fill", color: .red)
    case .signatureInvalid: return .init(label: "Signature invalid", systemImage: "exclamationmark.triangle.fill", color: .red)
    case .malformed:        return .init(label: "Malformed", systemImage: "exclamationmark.triangle.fill", color: .red)
    case .indeterminate:    return .init(label: "Indeterminate", systemImage: "shield.fill", color: .secondary)
    default:                return .init(label: status.name, systemImage: "questionmark.circle", color: .secondary)
    }
}

/// The overall verdict, labelled as the Android app's compact card badge is.
private func concludedStyle(_ status: VerificationStatus) -> VerificationStyle {
    switch status {
    case .valid:       return .init(label: "Verified", systemImage: "checkmark.seal.fill", color: verifiedGreen)
    case .expired:     return .init(label: "Expired", systemImage: "exclamationmark.circle.fill", color: .red)
    case .revoked:     return .init(label: "Revoked", systemImage: "exclamationmark.circle.fill", color: .red)
    case .notYetValid: return .init(label: "Pending", systemImage: "clock", color: pendingAmber)
    default:           return .init(label: "Issue", systemImage: "exclamationmark.triangle.fill", color: .red)
    }
}

private let failedStyle = VerificationStyle(label: "Issue", systemImage: "exclamationmark.triangle.fill", color: .red)

// MARK: - Badges

/// Inline badge for a credential row: "Verifying…", then the summary's concluded status.
struct CompactVerificationBadge: View {
    let phase: CredentialVerificationModel.Phase

    var body: some View {
        switch phase {
        case .idle:
            EmptyView()
        case .verifying:
            HStack(spacing: 4) {
                ProgressView().controlSize(.small)
                Text("Verifying…")
            }
            .font(.caption)
            .foregroundStyle(.secondary)
        case .verified(let summary):
            InlineBadge(style: concludedStyle(summary.concluded))
        case .failed:
            InlineBadge(style: failedStyle)
        }
    }
}

/// Capsule badge for the overall status on the detail screen.
struct VerificationStatusBadge: View {
    let status: VerificationStatus

    var body: some View {
        let style = resultStyle(status)
        HStack(spacing: 4) {
            Image(systemName: style.systemImage)
            Text(style.label)
        }
        .font(.caption.weight(.semibold))
        .foregroundStyle(style.color)
        .padding(.horizontal, 10)
        .padding(.vertical, 5)
        .background(style.color.opacity(0.12), in: Capsule())
    }
}

private struct InlineBadge: View {
    let style: VerificationStyle

    var body: some View {
        HStack(spacing: 3) {
            Image(systemName: style.systemImage)
            Text(style.label)
        }
        .font(.caption.weight(.medium))
        .foregroundStyle(style.color)
    }
}

// MARK: - Detail section

/// "Verification" section for the credential detail screen: the concluded status, one row per
/// check and a button to run the checks again, like the Android app's verification details sheet.
struct VerificationSection: View {
    @ObservedObject var model: CredentialVerificationModel
    let credential: any Credential

    var body: some View {
        Section("Verification") {
            HStack {
                Text("Status")
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                Spacer()
                statusView
            }

            switch model.phase {
            case .verified(let summary):
                ForEach(Array(summary.results.enumerated()), id: \.offset) { entry in
                    VerificationResultRow(result: entry.element)
                }
            case .failed(let message):
                Text(message)
                    .font(.footnote)
                    .foregroundStyle(.red)
            default:
                EmptyView()
            }

            Button("Verify again") {
                Task { await model.verify(credential) }
            }
            .disabled(model.isVerifying)
        }
    }

    @ViewBuilder
    private var statusView: some View {
        switch model.phase {
        case .idle:
            Text("—")
                .font(.subheadline)
                .foregroundStyle(.secondary)
        case .verifying:
            HStack(spacing: 6) {
                ProgressView().controlSize(.small)
                Text("Verifying…")
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
            }
        case .verified(let summary):
            VerificationStatusBadge(status: summary.concluded)
        case .failed:
            InlineBadge(style: failedStyle)
        }
    }
}

/// One check from the summary: its name, outcome, reason and details.
struct VerificationResultRow: View {
    let result: VerificationResult

    private var details: [(key: String, value: String)] {
        result.details.sorted { $0.key < $1.key }
    }

    var body: some View {
        let style = resultStyle(result.status)
        VStack(alignment: .leading, spacing: 4) {
            HStack(spacing: 8) {
                Image(systemName: style.systemImage)
                    .foregroundStyle(style.color)
                Text(result.check)
                    .font(.subheadline.weight(.medium))
                Spacer()
                Text(style.label)
                    .font(.caption.weight(.medium))
                    .foregroundStyle(style.color)
            }
            if let reason = result.reason {
                Text(reason)
                    .font(.footnote)
                    .foregroundStyle(.secondary)
            }
            if !details.isEmpty {
                VStack(alignment: .leading, spacing: 2) {
                    ForEach(details, id: \.key) { entry in
                        HStack(alignment: .top) {
                            Text(entry.key)
                                .font(.caption)
                                .foregroundStyle(.secondary)
                            Spacer()
                            Text(entry.value)
                                .font(.caption)
                                .multilineTextAlignment(.trailing)
                                .textSelection(.enabled)
                        }
                    }
                }
                .padding(.top, 2)
            }
        }
        .padding(.vertical, 4)
    }
}
