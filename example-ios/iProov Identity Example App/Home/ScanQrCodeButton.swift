//
//  ScanQrCodeButton.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//
import SwiftUI

struct ScanQRCodeButton : View {
    @StateObject private var viewModel: ScanQRCodeViewModel
    
    init(failure: Binding<AlertDialog?>, reloadCredentials: @escaping () -> Void) {
        _viewModel = StateObject(
            wrappedValue: ScanQRCodeViewModel(failure: failure, reloadCredentials: reloadCredentials)
        )
    }
    
    var body: some View {
        Button(action: {
            viewModel.isShowingSheet = true
        }) {
            Image(systemName: "qrcode.viewfinder")
                .font(.title.weight(.semibold))
                .padding()
                .background(Color.accentColor)
                .foregroundColor(.white)
                .clipShape(Circle())
                .shadow(radius: 4)
        }
        .disabled(viewModel.isLoading)
        .sheet(isPresented: $viewModel.isShowingSheet) {
            ScanQrCodeSheet(
                dismiss: { viewModel.isShowingSheet = false },
                onQrScanned: { qr in
                    viewModel.isShowingSheet = false
                    viewModel.handleQrCode(code: qr)
                }
            )
        }
        .sheet(item: $viewModel.loginRequest) { request in
            SelectiveDisclosureSheet(loginRequest: request) {
                viewModel.loginRequest = nil
                Task {
                    // Deny the request if the sheet is dismissed without sharing
                    try await request.deny()
                }
            }
        }
    }
}
