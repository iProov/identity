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
    @Published var legacyCredentials: [LegacyCredential] = []
    @Published var credentialSummary = CredentialSummary(credentials: [:], failures: [:])
    @Published var isLoading = false
    @Published var alert: AlertDialog? = nil

    private let wallet = WalletFactory.shared.instance!

    /// Fetches the user's credentials from the wallet.
    func loadCredentials() {
        isLoading = true
        Task {
            do {
                let summary = try wallet.getCredentials()
                let legacy = try wallet.getLegacyCredentials()

                await MainActor.run {
                    credentialSummary = summary
                    legacyCredentials = legacy
                    isLoading = false
                }
            } catch {
                await MainActor.run {
                    alert = AlertDialog(title: "Failed to load credentials", message: error.localizedDescription)
                    credentialSummary = CredentialSummary(credentials: [:], failures: [:])
                    isLoading = false
                }
            }
        }
    }

    /// Deletes a specific credential from the wallet and reloads the list.
    func deleteLegacyCredential(_ credential: LegacyCredential) {
        isLoading = true
        Task {
            do {
                try wallet.deleteCredential(credential: credential)
                loadCredentials()  // Reload to reflect the change
            } catch {
                alert = AlertDialog(title: "Failed to delete credential", message: error.localizedDescription)
            }
            isLoading = false
        }
    }

    func deleteCredential(metadata: CredentialMetadata) {
        isLoading = true
        Task {
            do {
                try wallet.deleteCredential(metadata: metadata)
                loadCredentials()
            } catch {
                alert = AlertDialog(title: "Failed to delete credential", message: error.localizedDescription)
            }
            isLoading = false
        }
    }

    func verify(_ credential: LegacyCredential) {
        let hasDtc =  credential.claims.contains{ claim in claim.name == "com.svipe:dtc"}

        guard hasDtc else {
            alert = AlertDialog(title: "Not Supported", message: "Only credentials with a DTC can be verified")
            return
        }

        isLoading = true
        do {
            let events = try wallet.addFaceVerification(credential: credential, loginRequest: nil, options: nil)
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
                self.isLoading = false
                self.alert = AlertDialog(title: "Error whilst verifying face", message: error.localizedDescription)

            }
        } catch {
            isLoading = false
            alert = AlertDialog(title: "Couldn't start face verification", message: error.localizedDescription)
        }
    }
}
