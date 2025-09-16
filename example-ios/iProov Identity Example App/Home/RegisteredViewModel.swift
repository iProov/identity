//
//  RegisteredViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//

import Foundation
import SwiftUI
import identity

@MainActor
class RegisteredViewModel: ObservableObject {
    @Published var credentials: [Credential] = []
    @Published var isLoading = false
    @Published var alert: AlertDialog? = nil

    private let wallet = WalletFactory.shared.instance!

    /// Fetches the user's credentials from the wallet.
    func loadCredentials() {
        isLoading = true
        do {
            credentials = try wallet.getCredentials()
        } catch {
            alert = AlertDialog(title: "Failed to load credentials", message: error.localizedDescription)
        }
        isLoading = false
    }

    /// Deletes a specific credential from the wallet and reloads the list.
    func deleteCredential(_ credential: Credential) {
        isLoading = true
        Task {
            do {
                try await wallet.deleteCredential(credential: credential)
                loadCredentials()  // Reload to reflect the change
            } catch {
                alert = AlertDialog(title: "Failed to delete credential", message: error.localizedDescription)
            }
            isLoading = false
        }
    }

    func verify(_ credential: Credential) {
        guard let mrtd = credential as? Credential.IdentityCredentialMrtd else {
            alert = AlertDialog(title: "Not Supported", message: "Only MRTD based documents can be verified")
            return
        }

        isLoading = true
        do {
            let events = try wallet.addFaceVerification(credential: mrtd, loginRequest: nil, options: nil)
            events.collect { [weak self] event in

                guard let self = self else { return }
                print("Face verification event: \(String(describing: event))")

                if let error = event as? VerificationEvent.Error {
                    isLoading = false
                    alert = AlertDialog(
                        title: "Verification Failed",
                        message: error.message
                    )
                    return
                }

                if event is VerificationEvent.Completed {
                    isLoading = false
                    alert = AlertDialog(
                        title: "Verification Successful",
                        message: "You have successfully verified your identity"
                    )
                    loadCredentials()  // Reload to reflect the change
                    return
                }
                
                if event is VerificationEvent.Canceled {
                    isLoading = false
                    return
                }
                
            } onError: { error in
                self.alert = AlertDialog(title: "Error whilst verifying face", message: error.localizedDescription)

            }
        } catch {
            alert = AlertDialog(title: "Couldn't start face verification", message: error.localizedDescription)
        }
    }
}
