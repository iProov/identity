//
//  RegisteredView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 28/01/2025.
//
import SwiftUI
import identity
import CoreNFC

struct RegisteredView: View {
    @StateObject private var viewModel = RegisteredViewModel()
    @State private var path = NavigationPath()
    let deleteWallet: () -> Void
    
    var body: some View {
        NavigationStack(path: $path) {
            ZStack(alignment: .bottomTrailing) {
                if viewModel.isLoading {
                    ProgressView()
                } else {
                    CredentialsView(
                        credentials: viewModel.credentials,
                        deleteCredential: viewModel.deleteCredential,
                        verifyCredential: viewModel.verify,
                    )
                }
                
                ScanQRCodeButton(failure: $viewModel.alert, reloadCredentials: viewModel.loadCredentials).padding()
            }
            .toolbar {
                ToolbarItem(placement: .topBarTrailing) {
                    AddCredentialButton(path: $path)
                }
                ToolbarItem(placement: .topBarTrailing) {
                    DeleteWalletButton(onConfirmedDeletion: deleteWallet)
                }
            }
            .navigationDestination(for: CredentialType.self) { location in
                credentialCreationView(for: location)
            }
        }
        .onAppear {
            viewModel.loadCredentials()
        }
        .refreshable {
            viewModel.loadCredentials()
        }
        .alert(item: $viewModel.alert) { error in
            Alert(title: Text(error.title), message: Text(error.message))
        }
    }
    
    /// Provides the correct view for the credential creation flow.
    @ViewBuilder
    private func credentialCreationView(for type: CredentialType) -> some View {
        let completion = {
            path.removeLast()
            viewModel.loadCredentials()
        }
        
        switch type {
        case .Document:
            AddDocumentView(path: $path, loginRequest: nil, completion: completion)
        case .Email:
            AddEmailView(path: $path, completion: completion)
        case .Phone:
            AddPhoneView(completion: completion)
        case .Reference:
            AddDocumentReferenceView(completion: completion)
        }
    }
}

extension RespondableLoginRequest: Identifiable {}

struct DeleteWalletButton: View {
    @State var isShowingConfirmation = false
    let onConfirmedDeletion: (() -> Void)

    var body: some View {
        Button {
            isShowingConfirmation = true
        } label: {
            Label("Delete Wallet", systemImage: "trash")
        }.confirmationDialog(
            "Are you sure?",
            isPresented: $isShowingConfirmation
        ) {
            Button("Confirm delete?", role: .destructive) { onConfirmedDeletion() }
        }
    }
}

struct AddCredentialButton: View {
    @State var isShowingConfirmation = false
    @Binding var path: NavigationPath

    var body: some View {
        Menu {
            Button("Add Document") { path.append(CredentialType.Document) }
            Button("Add Document Reference") { path.append(CredentialType.Reference) }
            Button("Add Email") { path.append(CredentialType.Email) }
            Button("Add Phone Number") { path.append(CredentialType.Phone) }
        } label: {
            Label("Add", systemImage: "plus")
        }
    }
}
