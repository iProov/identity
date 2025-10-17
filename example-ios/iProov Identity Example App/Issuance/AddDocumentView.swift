//
//  AddDocumentView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 31/01/2025.
//
import SwiftUI
import identity
import MRZScanner

struct AddDocumentView: View {
    @StateObject private var viewModel: AddDocumentViewModel
    @Binding var path: NavigationPath
    @State private var isScanningMrz = false
    
    init(path: Binding<NavigationPath>, loginRequest: LoginRequest?, completion: @escaping () -> Void) {
        _path = path
        _viewModel = StateObject(wrappedValue: AddDocumentViewModel(loginRequest: loginRequest, completion: completion))
    }
    
    var body: some View {
        NavigationView {
            VStack(alignment: .leading) {
                InstructionsView()
            }
            .padding()
            .frame(maxWidth: .infinity, maxHeight: .infinity, alignment: .topLeading)
            .safeAreaInset(edge: .bottom) {
                ActionButtonsView(
                    isLoading: $viewModel.isLoading,
                    onStartScanning: { isScanningMrz = true },
                    onAddDemo: viewModel.addDemoDocument
                )
            }
            .navigationTitle("Adding a document")
            .navigationBarBackButtonHidden(viewModel.isLoading)
            .sheet(isPresented: $isScanningMrz) {
                MrzCaptureView { result in
                    isScanningMrz = false
                    viewModel.readDocument(from: result.result)
                }
            }
            .alert(item: $viewModel.failure) { error in
                Alert(title: Text(error.title), message: Text(error.message))
            }
            .sheet(item: $viewModel.offerSheet) { sheet in
                CredentialOfferSheet(
                    state: sheet,
                    onToggleSelection: viewModel.toggleCredentialSelection,
                    onConfirm: viewModel.confirmCredentialSelection,
                    onDismiss: viewModel.dismissOfferSheet
                )
                .presentationDetents([.medium, .large])
            }
        }
    }
}

// MARK: - Subviews

private struct InstructionsView: View {
    var body: some View {
        VStack(alignment: .leading) {
            Text("Please have your document ready for the following steps.")
                .font(.subheadline)

            InstructionStep(title: "MRZ Scanning", description: "You will scan the MRZ page of the document")
                .padding(.top)
            
            InstructionStep(title: "NFC Reading", description: "Then you will scan the document's NFC chip")
        }
    }
}

private struct InstructionStep: View {
    let title: String
    let description: String
    
    var body: some View {
        VStack(alignment: .leading) {
            Text(title)
                .font(.headline)
                .padding(.bottom, 2)
            
            Text(description)
        }
        .font(.body)
        .padding(16)
        .frame(maxWidth: .infinity, alignment: .leading)
        .background(Color(uiColor: .secondarySystemBackground))
        .cornerRadius(8)
    }
}

private struct ActionButtonsView: View {
    @Binding var isLoading: Bool
    let onStartScanning: () -> Void
    let onAddDemo: () -> Void
    
    var body: some View {
        VStack {
            Button("Start Scanning", action: onStartScanning)
                .disabled(isLoading)
                .controlSize(.large)
                .buttonStyle(.borderedProminent)
            
            Button("Add a demo document", action: onAddDemo)
                .disabled(isLoading)
                .controlSize(.large)
                .padding()
        }
    }
}
