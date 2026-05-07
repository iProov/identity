import SwiftUI
import identity

struct PresentationRequestSheet: View {
    @Environment(\.dismiss) private var dismiss
    @StateObject private var viewModel: PresentationRequestViewModel

    let onDismiss: () -> Void
    let onSuccess: (PresentationOutcomeSuccess) -> Void

    init(
        request: RespondablePresentationRequest,
        onDismiss: @escaping () -> Void,
        onSuccess: @escaping (PresentationOutcomeSuccess) -> Void
    ) {
        _viewModel = StateObject(wrappedValue: PresentationRequestViewModel(request: request))
        self.onDismiss = onDismiss
        self.onSuccess = onSuccess
    }

    var body: some View {
        NavigationStack {
            ScrollView {
                VStack(alignment: .leading, spacing: 16) {
                    HeaderView(verifier: viewModel.request.verifier)

                    if viewModel.isLoading && viewModel.matchableQueries.isEmpty {
                        ProgressView()
                            .frame(maxWidth: .infinity, alignment: .center)
                    }

                    ForEach(viewModel.matchableQueries) { query in
                        QueryCard(
                            query: query,
                            matches: viewModel.matchingCredentials(for: query),
                            viewModel: viewModel
                        )
                    }

                    if viewModel.matchableQueries.isEmpty && !viewModel.isLoading {
                        Text(
                            viewModel.canShare
                                ? "No optional credentials in this wallet matched the verifier's request. You can continue without sharing them."
                                : "No credentials in this wallet satisfy the verifier's request."
                        )
                            .foregroundStyle(.secondary)
                    }

                    if !viewModel.shareBlockers.isEmpty {
                        ShareBlockersCard(reasons: viewModel.shareBlockers)
                    }

                    ShareBar(
                        canShare: viewModel.canShare,
                        isLoading: viewModel.isLoading,
                        share: { Task { await viewModel.share() } }
                    )
                }
                .padding()
            }
            .navigationTitle("Share credentials")
            .toolbar {
                ToolbarItem(placement: .cancellationAction) {
                    Button("Cancel", action: cancel)
                }
            }
        }
        .presentationDetents([.large])
        .alert(item: $viewModel.alert) { alert in
            Alert(
                title: Text(alert.title),
                message: Text(alert.message),
                dismissButton: .default(Text("OK"))
            )
        }
        .onChange(of: viewModel.successOutcome) { outcome in
            guard let outcome else { return }
            onSuccess(outcome)
            viewModel.successOutcome = nil
            dismiss()
            onDismiss()
        }
    }

    private func cancel() {
        dismiss()
        onDismiss()
    }
}

// MARK: - Subviews

private struct HeaderView: View {
    let verifier: Verifier

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("Incoming presentation request")
                .font(.title3)
                .bold()
            Text("\(verifier.clientId) wants to verify specific information from your wallet.")
                .foregroundStyle(.secondary)
        }
        .frame(maxWidth: .infinity, alignment: .leading)
    }
}

private struct QueryCard: View {
    let query: CredentialQuery
    let matches: [CredentialQueryMatchResult]
    @ObservedObject var viewModel: PresentationRequestViewModel

    var body: some View {
        VStack(alignment: .leading, spacing: 12) {
            HStack {
                Text(viewModel.queryTitle(query))
                    .font(.headline)
                if !viewModel.isQueryRequired(query) {
                    OptionalBadge()
                }
                Spacer()
            }

            if matches.isEmpty {
                Text("No credentials match this requirement.")
                    .foregroundStyle(.secondary)
            } else {
                ForEach(matches) { match in
                    CredentialOptionRow(
                        match: match,
                        isSelected: viewModel.selections[query]?.match == match,
                        select: { viewModel.select(match, for: query) }
                    )
                }
            }

            if let selected = viewModel.selections[query]?.match {
                ClaimSelectionList(
                    query: query,
                    match: selected,
                    viewModel: viewModel
                )
            }
        }
        .padding()
        .frame(maxWidth: .infinity, alignment: .leading)
        .background(Color(uiColor: .secondarySystemBackground))
        .clipShape(RoundedRectangle(cornerRadius: 16))
    }
}

private struct CredentialOptionRow: View {
    let match: CredentialQueryMatchResult
    let isSelected: Bool
    let select: () -> Void

    var body: some View {
        Button(action: select) {
            HStack(alignment: .top, spacing: 12) {
                Image(systemName: isSelected ? "largecircle.fill.circle" : "circle")
                    .foregroundStyle(isSelected ? Color.accentColor : .secondary)
                VStack(alignment: .leading, spacing: 2) {
                    Text(match.metadata.bestDisplay?.name ?? "Credential")
                        .fontWeight(.semibold)
                    Text(match.metadata.issuer.bestDisplay?.name ?? "Unknown issuer")
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }
                Spacer()
            }
            .padding(.vertical, 8)
        }
        .buttonStyle(.plain)
    }
}

private struct ClaimSelectionList: View {
    let query: CredentialQuery
    let match: CredentialQueryMatchResult
    @ObservedObject var viewModel: PresentationRequestViewModel

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("Choose which fields to disclose")
                .font(.subheadline)
                .foregroundStyle(.secondary)

            ForEach(viewModel.claims(for: query, match: match), id: \.self) { claim in
                let isRequired = viewModel.isClaimRequired(claim, for: query)
                let isSelected = viewModel.selectedClaims(for: query).contains(claim) || isRequired

                HStack(alignment: .top, spacing: 12) {
                    Toggle("", isOn: Binding(
                        get: { isSelected },
                        set: { _ in viewModel.toggle(claim, in: query) }
                    ))
                    .labelsHidden()
                    .disabled(isRequired)

                    VStack(alignment: .leading, spacing: 2) {
                        HStack {
                            Text(viewModel.claimName(claim))
                                .fontWeight(.semibold)
                            if isRequired {
                                RequiredBadge()
                            }
                        }
                        Text(viewModel.value(for: claim, in: match))
                            .font(.caption)
                            .foregroundStyle(.secondary)
                            .lineLimit(2)
                    }
                    Spacer()
                }
                Divider()
            }
        }
        .padding()
        .background(Color(uiColor: .systemBackground))
        .clipShape(RoundedRectangle(cornerRadius: 12))
    }
}

private struct RequiredBadge: View {
    var body: some View {
        Text("Required")
            .font(.caption2.bold())
            .padding(.horizontal, 8)
            .padding(.vertical, 2)
            .background(Color.accentColor.opacity(0.15))
            .clipShape(Capsule())
    }
}

private struct OptionalBadge: View {
    var body: some View {
        Text("Optional")
            .font(.caption2.bold())
            .padding(.horizontal, 8)
            .padding(.vertical, 2)
            .background(Color.secondary.opacity(0.15))
            .clipShape(Capsule())
    }
}

private struct ShareBlockersCard: View {
    let reasons: [String]

    var body: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("Sharing isn't available yet")
                .font(.subheadline.weight(.semibold))

            ForEach(reasons, id: \.self) { reason in
                Text(reason)
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
            }
        }
        .padding()
        .frame(maxWidth: .infinity, alignment: .leading)
        .background(Color(uiColor: .secondarySystemBackground))
        .clipShape(RoundedRectangle(cornerRadius: 16))
    }
}

private struct ShareBar: View {
    let canShare: Bool
    let isLoading: Bool
    let share: () -> Void

    var body: some View {
        Button(action: share) {
            Group {
                if isLoading {
                    ProgressView()
                        .progressViewStyle(.circular)
                        .tint(.white)
                } else {
                    Text("Share")
                        .fontWeight(.semibold)
                }
            }
            .frame(maxWidth: .infinity)
        }
        .buttonStyle(.borderedProminent)
        .disabled(!canShare || isLoading)
    }
}
