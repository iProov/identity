//
//  AddDocumentReferenceView.swift
//  iProov Identity Example App
//
//  Created by Josh Everett on 07/07/2025.
//
import SwiftUI

struct AddDocumentReferenceView: View {
    @StateObject private var viewModel: AddDocumentReferenceViewModel

    init(completion: (() -> Void)?) {
        _viewModel = StateObject(wrappedValue: AddDocumentReferenceViewModel(completion: completion ?? {}))
    }

    var body: some View {
        NavigationView {
            VStack(alignment: .leading) {
                Text("Enter your reference with correct identifier (e.g. iProov:<uuid>)")
                    .font(.subheadline)
                    .padding(.horizontal)

                TextField("Your reference", text: $viewModel.reference)
                    .textFieldStyle(.roundedBorder)
                    .padding(.horizontal)

                Button("Continue") {
                    viewModel.addDocumentWithReference()
                }
                .padding()
                .buttonStyle(.borderedProminent)
                .disabled(viewModel.isLoading || viewModel.reference.isEmpty)
                .frame(maxWidth: .infinity)
            }
            .navigationTitle("Add Reference")
            .alert(item: $viewModel.alert) { alert in
                Alert(title: Text(alert.title), message: Text(alert.message))
            }
            .sheet(item: $viewModel.offerSheet) { sheet in
                CredentialOfferSheet(
                    state: sheet,
                    onToggleSelection: viewModel.toggleCredentialSelection,
                    onConfirm: viewModel.confirmCredentialSelection,
                    onSubmitTransactionCode: viewModel.submitTransactionCode,
                    onDismiss: viewModel.dismissOfferSheet
                )
                .presentationDetents([.medium, .large])
            }
        }
    }
}
