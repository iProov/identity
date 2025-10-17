import SwiftUI
import identity

struct CredentialOfferSheet: View {
    let state: CredentialOfferSheetState
    let onToggleSelection: (UUID) -> Void
    let onConfirm: () -> Void
    let onDismiss: () -> Void

    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            Capsule()
                .frame(width: 40, height: 4)
                .foregroundStyle(.secondary)
                .frame(maxWidth: .infinity)
                .padding(.top, 8)

            if let issuerDisplay = state.issuerDisplay {
                VStack(alignment: .leading, spacing: 4) {
                    Text(issuerDisplay.name)
                        .font(.title3.weight(.semibold))
                    
                    Text(issuerDisplay.description)
                            .font(.subheadline)
                            .foregroundStyle(.secondary)

                }
            }

            switch state.status {
            case .completed(let summary):
                IssuanceSummaryView(summary: summary)
                Button("Done", action: onDismiss)
                    .buttonStyle(.borderedProminent)

            case .failed(let message):
                IssueMessageView(title: "Failed to add credentials", message: message)
                Button("Close", action: onDismiss)
                    .buttonStyle(.borderedProminent)

            case .transactionCodeRequired(let description):
                IssueMessageView(title: "Transaction code required", message: description)
                Button("Close", action: onDismiss)
                    .buttonStyle(.borderedProminent)

            default:
                selectionContent
            }

            Spacer(minLength: 0)
        }
        .padding(.horizontal, 20)
        .padding(.bottom, 24)
    }

    private var selectionContent: some View {
        VStack(alignment: .leading, spacing: 16) {
            Text("Select the credentials you would like to add")
                .font(.headline)

            ScrollView {
                VStack(spacing: 12) {
                    ForEach(state.items) { item in
                        CredentialOfferRow(item: item, isDisabled: state.status == .submitting) {
                            onToggleSelection(item.id)
                        }
                    }
                }
                .padding(.vertical, 4)
            }
            .disabled(state.status == .submitting)

            HStack {
                Button("Cancel", action: onDismiss)
                    .buttonStyle(.bordered)

                Spacer()

                Button(action: onConfirm) {
                    HStack {
                        Text("Add Selected")
                    }
                }
                .buttonStyle(.borderedProminent)
                .disabled(!state.canConfirm)
            }

            if state.status == .submitting {
                HStack(spacing: 8) {
                    ProgressView()
                    Text("Issuing credentials…")
                        .font(.footnote)
                        .foregroundStyle(.secondary)
                }
            }
        }
    }
}

private struct CredentialOfferRow: View {
    let item: CredentialOfferSheetState.Item
    let isDisabled: Bool
    let toggle: () -> Void

    var body: some View {
        let background = item.display?.backgroundSwiftColor ?? Color(uiColor: .secondarySystemBackground)
        let textColor = item.display?.textSwiftColor ?? Color.primary

        Button(action: toggle) {
            HStack(alignment: .top, spacing: 12) {
                VStack(alignment: .leading, spacing: 4) {
                    Text(item.display?.name ?? "Credential")
                        .font(.headline)
                        .foregroundStyle(textColor)

                    if let description = item.display?.description {
                        Text(description)
                            .font(.subheadline)
                            .foregroundStyle(textColor.opacity(0.8))
                    }

                    Text(item.descriptor.format)
                        .font(.footnote)
                        .foregroundStyle(textColor.opacity(0.7))
                }

                Spacer()

                Image(systemName: item.isSelected ? "checkmark.circle.fill" : "circle")
                    .imageScale(.large)
                    .foregroundStyle(item.isSelected ? Color.accentColor : .secondary)
            }
            .padding()
            .frame(maxWidth: .infinity, alignment: .leading)
            .background(background.opacity(item.isSelected ? 1.0 : 0.5))
            .cornerRadius(14)
        }
        .buttonStyle(.plain)
        .disabled(isDisabled)
    }
}

private struct IssuanceSummaryView: View {
    let summary: IssuanceSummary

    private var added: [CredentialMetadata] {
        summary.credentialsAdded as? [CredentialMetadata] ?? []
    }

    private var errors: [(CredentialMetadata, OID4VCICredentialError)] {
        if let dict = summary.errors as? [CredentialMetadata: OID4VCICredentialError] {
            return dict.map { ($0.key, $0.value) }
        }

        var collected: [(CredentialMetadata, OID4VCICredentialError)] = []
        if let nsDict = summary.errors as? NSDictionary {
            for key in nsDict.allKeys {
                guard let metadata = key as? CredentialMetadata,
                      let error = nsDict[key] as? OID4VCICredentialError else { continue }
                collected.append((metadata, error))
            }
        }
        return collected
    }

    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            Text("Issuance complete")
                .font(.headline)

            if !added.isEmpty {
                VStack(alignment: .leading, spacing: 8) {
                    Text("Added")
                        .font(.subheadline.weight(.semibold))
                    ForEach(added, id: \.uuid) { metadata in
                        VStack(alignment: .leading, spacing: 2) {
                            Text(metadata.bestDisplay?.name ?? "Credential")
                                .font(.body)
                            Text(metadata.issuer.name)
                                .font(.footnote)
                                .foregroundStyle(.secondary)
                        }
                        .frame(maxWidth: .infinity, alignment: .leading)
                    }
                }
            }

            if !errors.isEmpty {
                VStack(alignment: .leading, spacing: 8) {
                    Text("Errors")
                        .font(.subheadline.weight(.semibold))
                    ForEach(errors, id: \.0.uuid) { metadata, error in
                        VStack(alignment: .leading, spacing: 4) {
                            Text(metadata.bestDisplay?.name ?? "Credential")
                                .font(.body)
                            Text(error.error)
                                .font(.footnote)
                                .foregroundStyle(.red)
                            Text(error.description_)
                                .font(.footnote)
                                .foregroundStyle(.secondary)
                        }
                        .frame(maxWidth: .infinity, alignment: .leading)
                    }
                }
            }

            if added.isEmpty && errors.isEmpty {
                Text("No credentials were issued.")
                    .foregroundStyle(.secondary)
            }
        }
    }
}

private struct IssueMessageView: View {
    let title: String
    let message: String

    var body: some View {
        VStack(alignment: .leading, spacing: 12) {
            Text(title)
                .font(.headline)
            Text(message)
                .font(.subheadline)
                .foregroundStyle(.secondary)
        }
        .frame(maxWidth: .infinity, alignment: .leading)
    }
}
