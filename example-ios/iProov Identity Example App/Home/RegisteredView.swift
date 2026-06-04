//
//  RegisteredView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 28/01/2025.
//
import SwiftUI
import identity
import CoreNFC

private struct DocumentRoute: Hashable {
    let initialCredentialOfferUri: String?
}

struct RegisteredView: View {
    @StateObject private var viewModel = RegisteredViewModel()
    @State private var path = NavigationPath()
    let deleteWallet: () -> Void
    @Binding var pendingPresentationUri: String?
    @Binding var pendingCredentialOfferUri: String?

    private var hasCredentials: Bool {
        !viewModel.credentialSummary.credentials.isEmpty ||
        !viewModel.credentialSummary.failures.isEmpty ||
        !viewModel.legacyCredentials.isEmpty
    }

    private var credentialAddedCompletion: () -> Void {
        {
            path.removeLast()
            viewModel.loadCredentials()
        }
    }

    var body: some View {
        NavigationStack(path: $path) {
            ZStack {
                credentialsList
                    .opacity(viewModel.isLoading && !hasCredentials ? 0 : 1)

                if viewModel.isLoading && !hasCredentials {
                    ProgressView()
                        .controlSize(.large)
                }

                // Present (holder) + QR scan (reader) buttons
                VStack {
                    Spacer()
                    HStack {
                        Spacer()
                        VStack(spacing: 16) {
                            PresentProximityButton()
                            ScanQRCodeButton(
                                failure: $viewModel.alert,
                                reloadCredentials: viewModel.loadCredentials,
                                pendingDeepLinkURI: $pendingPresentationUri,
                                onCredentialOfferScanned: openCredentialOffer
                            )
                        }
                        .padding()
                    }
                }
            }
            .toolbar {
                ToolbarItem(placement: .topBarLeading) {
                    NavigationLink(destination: SettingsView()) {
                        Label("Settings", systemImage: "gear")
                    }
                }
                ToolbarItem(placement: .topBarTrailing) {
                    AddCredentialButton(path: $path)
                        .disabled(viewModel.isLoading)
                }
                ToolbarItem(placement: .topBarTrailing) {
                    DeleteWalletButton(onConfirmedDeletion: deleteWallet)
                        .disabled(viewModel.isLoading)
                }
            }
            .navigationDestination(for: CredentialType.self) { type in
                credentialCreationView(for: type)
            }
            .navigationDestination(for: DocumentRoute.self) { route in
                AddDocumentView(
                    path: $path,
                    loginRequest: nil,
                    initialCredentialOfferUri: route.initialCredentialOfferUri,
                    completion: credentialAddedCompletion
                )
            }
        }
        .onAppear {
            viewModel.loadCredentials()
            openPendingCredentialOfferIfNeeded()
        }
        .onChange(of: pendingCredentialOfferUri) { _, _ in
            openPendingCredentialOfferIfNeeded()
        }
        .refreshable {
            await viewModel.loadCredentialsAsync()
        }
        .alert(item: $viewModel.alert) { alert in
            Alert(title: Text(alert.title), message: Text(alert.message))
        }
    }

    @ViewBuilder
    private var credentialsList: some View {
        if hasCredentials {
            List {
                StoredCredentialsSection(
                    summary: viewModel.credentialSummary,
                    onDelete: viewModel.deleteCredential
                )

                LegacyCredentialsSection(
                    credentials: viewModel.legacyCredentials,
                    deleteCredential: viewModel.deleteLegacyCredential,
                    verifyCredential: viewModel.verify
                )
            }
        } else if !viewModel.isLoading {
            EmptyCredentialsView(path: $path)
        }
    }

    @ViewBuilder
    private func credentialCreationView(for type: CredentialType) -> some View {
        switch type {
        case .Document:
            AddDocumentView(path: $path, loginRequest: nil, completion: credentialAddedCompletion)
        case .Email:
            AddEmailView(path: $path, completion: credentialAddedCompletion)
        case .Phone:
            AddPhoneView(completion: credentialAddedCompletion)
        case .Reference:
            AddDocumentReferenceView(completion: credentialAddedCompletion)
        }
    }

    private func openPendingCredentialOfferIfNeeded() {
        guard let uri = pendingCredentialOfferUri else { return }
        pendingCredentialOfferUri = nil
        openCredentialOffer(uri)
    }

    private func openCredentialOffer(_ uri: String) {
        path.append(DocumentRoute(initialCredentialOfferUri: uri))
    }
}

// MARK: - Empty State

private struct EmptyCredentialsView: View {
    @Binding var path: NavigationPath

    var body: some View {
        VStack(spacing: 24) {
            Spacer()

            Image(systemName: "creditcard")
                .font(.system(size: 56))
                .foregroundStyle(.secondary)
                .symbolRenderingMode(.hierarchical)

            VStack(spacing: 8) {
                Text("No Credentials")
                    .font(.title2.weight(.semibold))

                Text("Add your first credential to get started.")
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
            }

            Button {
                path.append(CredentialType.Document)
            } label: {
                Label("Add Document", systemImage: "plus")
            }
            .buttonStyle(.borderedProminent)

            Spacer()
        }
        .frame(maxWidth: .infinity)
    }
}

// MARK: - Toolbar Buttons

extension RespondableLoginRequest: Identifiable {}

struct DeleteWalletButton: View {
    @State private var isShowingConfirmation = false
    let onConfirmedDeletion: () -> Void

    var body: some View {
        Button {
            isShowingConfirmation = true
        } label: {
            Label("Delete Wallet", systemImage: "trash")
        }
        .confirmationDialog(
            "Delete Wallet",
            isPresented: $isShowingConfirmation,
            titleVisibility: .visible
        ) {
            Button("Delete", role: .destructive) {
                onConfirmedDeletion()
            }
        } message: {
            Text("This will permanently delete your wallet and all credentials. This action cannot be undone.")
        }
    }
}

struct AddCredentialButton: View {
    @Binding var path: NavigationPath

    var body: some View {
        Menu {
            Button {
                path.append(CredentialType.Document)
            } label: {
                Label("Add Document", systemImage: "doc.text.viewfinder")
            }

            Button {
                path.append(CredentialType.Reference)
            } label: {
                Label("Add Document Reference", systemImage: "doc.badge.plus")
            }

            Divider()

            Button {
                path.append(CredentialType.Email)
            } label: {
                Label("Add Email", systemImage: "envelope")
            }

            Button {
                path.append(CredentialType.Phone)
            } label: {
                Label("Add Phone Number", systemImage: "phone")
            }
        } label: {
            Label("Add", systemImage: "plus")
        }
    }
}
