//
//  ScanQrCodeViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//


import Foundation
import SwiftUI
import identity
import CoreNFC

@MainActor
class ScanQRCodeViewModel: ObservableObject {
    @Published var isShowingSheet = false
    @Published var loginRequest: RespondableLoginRequest? = nil
    @Published var isLoading = false
    @Binding var alert: AlertDialog?
    let reloadCredentials: () -> Void
    
    private let wallet = WalletFactory.shared.instance!
    
    init(failure: Binding<AlertDialog?>, reloadCredentials: @escaping () -> Void) {
        _alert = failure
        self.reloadCredentials = reloadCredentials
    }
    
    /// Handles the scanned QR code content.
    func handleQrCode(code: String) {
        guard let url = URL(string: code) else {
            alert = AlertDialog(title: "Invalid QR Code", message: "The scanned QR code does not contain a valid URL.")
            return
        }
        
        if (url.path().contains("email/verify")) {
            return handleEmailVerification(url)
        }
        
        handlePresentationRequest(uri: url)
    }
    
    func handleEmailVerification(_ url: URL){
        isLoading = true
        if let emailToVerify = UserDefaults.standard.string(forKey: "email") {
            wallet.verifyUriCredential(uri: emailToVerify, token: String(describing: url)) { error in
                self.isLoading = false
                if let error {
                   print("Failed to verify: \(String(describing: url))")
                   self.alert = AlertDialog(title: "Failed to verify email", message: error.localizedDescription)
                   return
                } else {
                   self.alert = AlertDialog(title: "Success", message: "Your email address has been added to your wallet.")
                   self.reloadCredentials()
                   return
                }
            }
        } else {
            alert = AlertDialog(
                title: "Failed to verify email",
                message: "You have not tried to add an email to your wallet yet."
            )
        }
        
    }
    
    /// Initiates a login request from a given URI.
    private func handlePresentationRequest(uri: URL) {
        isLoading = true
        let isNfcCapable = NFCNDEFReaderSession.readingAvailable
        
        wallet.getLoginRequest(uri: String(describing: uri), isNfcCapable: isNfcCapable) { [weak self] presentationRequest, error in
            guard let self = self else { return }
            self.isLoading = false
            
            if let error {
                self.alert = AlertDialog(title: "Failed to get login request", message: error.localizedDescription)
                return
            }
            
            guard let presentationRequest else {
                self.alert = AlertDialog(title: "Failed to get login request", message: "Unable to get presentation request")
                return
            }
            
            self.loginRequest = presentationRequest
        }
    }
}
