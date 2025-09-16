//
//  AddPhoneView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 03/02/2025.
//
import SwiftUI
import identity

struct AddPhoneView: View {
    @StateObject private var viewModel: AddPhoneViewModel
    
    init(completion: (() -> Void)?) {
        _viewModel = StateObject(wrappedValue: AddPhoneViewModel(completion: completion ?? {}))
    }
    
    var body: some View {
        NavigationView {
            VStack(alignment: .leading) {
                Text("Enter your phone number below to get started (including country code e.g +44.")
                    .font(.subheadline)
                    .padding(.horizontal)
                
                TextField("Your phone number", text: $viewModel.phoneNumber)
                    .keyboardType(.phonePad)
                    .textContentType(.telephoneNumber)
                    .textFieldStyle(.roundedBorder)
                    .padding(.horizontal)
                        
                Button("Continue") {
                    viewModel.addPhoneNumber()
                }
                .padding()
                .buttonStyle(.borderedProminent)
                .disabled(viewModel.isLoading || viewModel.phoneNumber.isEmpty)
                .frame(maxWidth: .infinity)
            }
            .navigationTitle("Add Phone Number")
            .alert("Enter OTP", isPresented: $viewModel.isShowingOtpView) {
                OtpAlertContentView(viewModel: viewModel)
            }
            .alert(item: $viewModel.alert) { alert in
                Alert(title: Text(alert.title), message: Text(alert.message))
            }
        }
    }
}

// MARK: - Subviews

private struct OtpAlertContentView: View {
    @ObservedObject var viewModel: AddPhoneViewModel
    
    var body: some View {
        VStack {
            TextField("e.g., 123456", text: $viewModel.otp)
                .keyboardType(.numberPad)
                .onChange(of: viewModel.otp) { newValue in
                    let filtered = newValue.filter { $0.isNumber }
                    if filtered.count > 6 {
                        viewModel.otp = String(filtered.prefix(6))
                    } else if viewModel.otp != filtered {
                        viewModel.otp = filtered
                    }
                }

            Button("OK") {
                viewModel.confirmOtp()
            }
            .disabled(viewModel.otp.count != 6)
            
            Button("Cancel", role: .cancel) {
                viewModel.cancelOtp()
            }
        }
    }
}
