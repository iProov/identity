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
    @Published var presentationRequest: RespondablePresentationRequest? = nil
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
        guard let normalized = normalizedQrCode(code),
              let url = URL(string: normalized) else {
            alert = AlertDialog(title: "Invalid QR Code", message: "The scanned QR code does not contain a valid URL.")
            return
        }

        guard let scheme = url.scheme?.lowercased() else {
            alert = AlertDialog(title: "Invalid QR Code", message: "The scanned QR code does not contain a valid protocol.")
            return
        }

        switch scheme {
        case "https":
            handleHttpsRequest(url)
        case "openid4vp":
            handleOpenId4VpRequest(normalized)
        default:
            alert = AlertDialog(title: "Unsupported QR Code", message: "The scanned QR code uses an unsupported protocol.")
        }
    }

    private func handleHttpsRequest(_ url: URL) {
        if url.path().contains("email/verify") {
            handleEmailVerification(url)
            return
        }

        handleLoginRequest(uri: url)
    }

    private func handleOpenId4VpRequest(_ uri: String) {
        isLoading = true
        wallet.getPresentationRequest(uri: uri) { [weak self] request, error in
            guard let self else {
                return
            }
            self.isLoading = false

            if let error {
                self.alert = AlertDialog(
                    title: "Failed to get presentation request",
                    message: error.localizedDescription
                )
                return
            }

            guard let request else {
                self.alert = AlertDialog(
                    title: "Failed to get presentation request",
                    message: "The verifier did not return a valid request."
                )
                return
            }

            self.presentationRequest = request
        }
    }

    func handleEmailVerification(_ url: URL) {
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
    private func handleLoginRequest(uri: URL) {
        isLoading = true
        let isNfcCapable = NFCNDEFReaderSession.readingAvailable

        wallet.getLoginRequest(uri: String(describing: uri), isNfcCapable: isNfcCapable) { [weak self] presentationRequest, error in
            guard let self = self else {
                return
            }
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

    func dismissPresentationRequest() {
        presentationRequest = nil
    }

    func handlePresentationSuccess(_ outcome: PresentationOutcomeSuccess) {
        var message = "Credentials shared successfully."
        if let redirect = outcome.redirectUri, !redirect.isEmpty {
            message += "\nVerifier redirect: \(redirect)"
        }
        alert = AlertDialog(title: "Success", message: message)
        presentationRequest = nil
        reloadCredentials()
    }

    private func normalizedQrCode(_ code: String) -> String? {
        let trimmed = code.trimmingCharacters(in: .whitespacesAndNewlines)
        guard !trimmed.isEmpty else { return nil }

        guard trimmed.lowercased().hasPrefix("openid4vp://"),
              let requestUriRange = trimmed.range(of: "request_uri=") else {
            return trimmed
        }

        let valueStart = requestUriRange.upperBound
        let remainder = trimmed[valueStart...]
        let endIndex = remainder.firstIndex(of: "&") ?? trimmed.endIndex
        let encodedValue = trimmed[valueStart..<endIndex]

        guard encodedValue.contains("%"),
              let decodedValue = encodedValue.removingPercentEncoding else {
            return trimmed
        }

        var normalized = trimmed
        normalized.replaceSubrange(valueStart..<endIndex, with: decodedValue)
        return normalized
    }
}
