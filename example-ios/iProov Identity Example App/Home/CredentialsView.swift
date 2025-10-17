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
                            NavigationLink {
                                StoredCredentialDetailView(item: item)
                            } label: {
                                StoredCredentialRow(item: item, onDelete: onDelete)
                            }
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
    let onDelete: (CredentialMetadata) -> Void

    private var display: DisplayProperties? { item.metadata.bestDisplay }

    private var format: String {
        item.credential.format.value
    }

    private var issuerName: String {
        item.metadata.issuer.name
    }

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            HStack(alignment: .firstTextBaseline) {
                VStack(alignment: .leading, spacing: 2) {
                    Text(display?.name ?? "Credential")
                        .font(.headline)
                    Text(issuerName)
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }
                Spacer()
                Menu {
                    Button(role: .destructive) {
                        onDelete(item.metadata)
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
                Text("Format: \(format)")
                    .font(.footnote)
                    .foregroundStyle(.secondary)

                if let addedDate = formattedDate(milliseconds: item.metadata.addedAt) {
                    Text("Added: \(addedDate)")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                }

                if let mdoc = item.credential as? MDocCredential {
                    Text("Doc Type: \(mdoc.docType)")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                }
            }
        }
        .padding(.vertical, 6)
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

    private var display: DisplayProperties? { item.metadata.bestDisplay }

    var body: some View {
        List {
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
