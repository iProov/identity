//
//  ScanQrCodeButton.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//
import SwiftUI

struct ScanQRCodeButton : View {
    @StateObject private var viewModel: ScanQRCodeViewModel
    @Binding private var pendingDeepLinkURI: String?
    private let onCredentialOfferScanned: (String) -> Void

    init(
        failure: Binding<AlertDialog?>,
        reloadCredentials: @escaping () -> Void,
        pendingDeepLinkURI: Binding<String?>,
        onCredentialOfferScanned: @escaping (String) -> Void
    ) {
        _viewModel = StateObject(
            wrappedValue: ScanQRCodeViewModel(failure: failure, reloadCredentials: reloadCredentials)
        )
        _pendingDeepLinkURI = pendingDeepLinkURI
        self.onCredentialOfferScanned = onCredentialOfferScanned
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
                    viewModel.handleQrCode(code: qr, onCredentialOfferScanned: onCredentialOfferScanned)
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
        .sheet(item: $viewModel.presentationRequest) { request in
            PresentationRequestSheet(
                request: request,
                onDismiss: { viewModel.dismissPresentationRequest() },
                onSuccess: { outcome in viewModel.handlePresentationSuccess(outcome) }
            )
        }
        .sheet(isPresented: Binding(
            get: { viewModel.proximityRetrievalUri != nil },
            set: { if !$0 { viewModel.proximityRetrievalUri = nil } }
        )) {
            if let uri = viewModel.proximityRetrievalUri {
                ProximityRetrievalSheet(
                    uri: uri,
                    onDismiss: { viewModel.proximityRetrievalUri = nil },
                    onCompleted: { response in
                        viewModel.proximityRetrievalUri = nil
                        viewModel.handleProximitySuccess(response)
                    }
                )
            }
        }
        .onAppear {
            consumePendingDeepLink()
        }
        .onChange(of: pendingDeepLinkURI) { _, _ in
            consumePendingDeepLink()
        }
    }

    private func consumePendingDeepLink() {
        guard let uri = pendingDeepLinkURI else { return }
        pendingDeepLinkURI = nil
        viewModel.handleQrCode(code: uri, onCredentialOfferScanned: onCredentialOfferScanned)
    }
}
