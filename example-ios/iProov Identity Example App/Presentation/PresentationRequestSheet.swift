import SwiftUI
import identity

struct PresentationRequestSheet: View {
    @Environment(\.dismiss) private var dismiss
    @StateObject private var viewModel: PresentationRequestViewModel
    @State private var isShowingBlockers = false

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

                    if viewModel.isLoading && viewModel.availableQueries.isEmpty {
                        ProgressView()
                            .frame(maxWidth: .infinity, alignment: .center)
                    }

                    ForEach(viewModel.availableQueries) { query in
                        QueryCard(
                            query: query,
                            matches: viewModel.matches(for: query),
                            viewModel: viewModel
                        )
                    }

                    if viewModel.availableQueries.isEmpty && !viewModel.isLoading {
                        Text("No credentials in this wallet satisfy the verifier’s request.")
                            .foregroundStyle(.secondary)
                    }

                    ShareBar(
                        canShare: viewModel.canShare,
                        isLoading: viewModel.isLoading,
                        share: { Task { await viewModel.share() } },
                        explain: { isShowingBlockers = true }
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
                dismissButton: .default(Text("OK"), action: viewModel.clearAlert)
            )
        }
        .sheet(isPresented: $isShowingBlockers) {
            NavigationStack {
                List {
                    if viewModel.shareBlockers.isEmpty {
                        Text("Sharing is available once the request has loaded.")
                    } else {
                        ForEach(viewModel.shareBlockers, id: \.self) { reason in
                            Text(reason)
                                .padding(.vertical, 4)
                        }
                    }
                }
                .navigationTitle("Why sharing is disabled")
                .toolbar {
                    ToolbarItem(placement: .confirmationAction) {
                        Button("Done") { isShowingBlockers = false }
                    }
                }
            }
        }
        .onChange(of: viewModel.successOutcome) { outcome in
            guard let outcome else { return }
            onSuccess(outcome)
            viewModel.clearSuccess()
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
            Text(query.id.isEmpty ? "Requested information" : query.id)
                .font(.headline)

            if matches.isEmpty {
                Text("No credentials match this requirement.")
                    .foregroundStyle(.secondary)
            } else {
                ForEach(matches) { match in
                    CredentialOptionRow(
                        match: match,
                        isSelected: viewModel.selectedCredentials[query] == match,
                        select: { viewModel.select(match, for: query) }
                    )
                }
            }

            if let selected = viewModel.selectedCredentials[query] {
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

            ForEach(viewModel.selectableClaims(for: query, match: match), id: \.self) { claim in
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
                            Text(viewModel.claimDisplayName(claim))
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

private struct ShareBar: View {
    let canShare: Bool
    let isLoading: Bool
    let share: () -> Void
    let explain: () -> Void

    var body: some View {
        HStack(spacing: 12) {
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

            if !canShare {
                Button(action: explain) {
                    Image(systemName: "info.circle")
                }
                .buttonStyle(.bordered)
            }
        }
    }
}
