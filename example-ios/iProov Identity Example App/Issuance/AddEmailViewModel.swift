//
//  AddPhoneViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//

import Foundation
import SwiftUI
import identity

@MainActor
class AddEmailViewModel: ObservableObject {
    @Published var email = ""
    @Published var isLoading = false
    @Published var alert: AlertDialog?
    
    private let completion: () -> Void
    
    init(completion: @escaping () -> Void) {
        self.completion = completion
    }
    
    /// Initiates the process of adding an email address.
    func addEmailAddress() {
        isLoading = true
        Task {
            do {
                let uri = "mailto:\(email)"
                try await WalletFactory.shared.instance!.addUriCredential(uri: uri)
                UserDefaults.standard.set(uri, forKey: "email")
                alert = AlertDialog(title: "Confirmation required", message: "Please click the link in the email or scan the QR code to confirm your email address.")
                // The completion is called here because the rest of the flow happens outside the app
                completion()
            } catch {
                alert = AlertDialog(title: "Failed to add email address", message: error.localizedDescription)
            }
            isLoading = false
        }
    }
}
