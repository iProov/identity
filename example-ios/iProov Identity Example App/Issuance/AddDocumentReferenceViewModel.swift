//
//  AddDocumentReferenceViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//

import Foundation
import SwiftUI
import identity

@MainActor
class AddDocumentReferenceViewModel: ObservableObject {
    @Published var reference = ""
    @Published var isLoading = false
    @Published var alert: AlertDialog? = nil

    private let completion: () -> Void

    private let wallet = WalletFactory.shared.instance!

    init(completion: @escaping () -> Void) {
        self.completion = completion
    }

    func addDocumentWithReference() {
        isLoading = true

        do {
            let events = try wallet.addDocumentWithReference(
                reference: reference,
                demoReferencePhoto: nil,
                loginRequest: nil,
                options: nil
            )

            events.collect(
                onEach: { event in
                    if case _ as VerificationEvent.Completed = event {
                        self.alert = AlertDialog(title: "Success", message: "Identity added using reference.")
                        self.isLoading = false
                        self.completion()
                    } else if case let failure as VerificationEvent.Error = event {
                        self.alert = AlertDialog(title: "Face verification failed", message: failure.message)
                        self.isLoading = true
                    } else if case _ as VerificationEvent.Loading = event {
                        self.isLoading = false
                    } else if case _ as VerificationEvent.Canceled = event {
                        self.isLoading = false
                    }
                },
                onError: { error in
                    self.alert = AlertDialog(title: "Face verification error", message: error.localizedDescription)
                    self.isLoading = false
                }
            )

        } catch {
            alert = AlertDialog(title: "Reference error", message: error.localizedDescription)
            isLoading = false
        }
    }

    func cancelReference() {
        isLoading = false
        reference = ""
    }

    private func validateReference() -> Bool {
        if reference.isEmpty {
            alert = AlertDialog(title: "Empty reference", message: "Please enter a valid reference.")
            return false
        }

        return true
    }
}
