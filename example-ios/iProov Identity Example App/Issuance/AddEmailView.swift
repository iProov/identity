//
//  AddEmailView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 03/02/2025.
//

import SwiftUI
import identity

struct AddEmailView: View {
    @StateObject private var viewModel: AddEmailViewModel
    @Binding var path: NavigationPath
    
    init(path: Binding<NavigationPath>, completion: (() -> Void)?) {
        _path = path
        _viewModel = StateObject(wrappedValue: AddEmailViewModel(completion: completion ?? {}))
    }
    
    var body: some View {
        NavigationView {
            VStack(alignment: .leading) {
                Text("Enter your email address below to get started.")
                    .font(.subheadline)
                
                TextField("Email", text: $viewModel.email)
                    .keyboardType(.emailAddress)
                    .textContentType(.emailAddress)
                    .autocorrectionDisabled()
                    .textFieldStyle(.roundedBorder)
                        
                Button("Continue") {
                    viewModel.addEmailAddress()
                }
                .padding()
                .buttonStyle(.borderedProminent)
                .disabled(viewModel.isLoading || viewModel.email.isEmpty)
                .frame(maxWidth: .infinity)
            }
            .padding(.horizontal)
            .navigationTitle("Add Email Address")
            .alert(item: $viewModel.alert) { alert in
                Alert(title: Text(alert.title), message: Text(alert.message))
            }
        }
    }
}
