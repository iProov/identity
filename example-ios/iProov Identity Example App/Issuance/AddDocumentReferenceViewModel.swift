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
    @Published var offerSheet: CredentialOfferSheetState? = nil

    private let completion: () -> Void

    private let wallet = WalletFactory.shared.instance!

    init(completion: @escaping () -> Void) {
        self.completion = completion
    }

    func addDocumentWithReference() {
        guard validateReference() else { return }

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
                    switch event {
                    case let completed as VerificationEvent.Completed:
                        guard let offer = completed.offer else {
                            self.alert = AlertDialog(
                                title: "No credential offer",
                                message: "The issuer did not return a credential offer."
                            )
                            self.isLoading = false
                            return
                        }

                        self.isLoading = false
                        self.presentOffer(offer)

                    case let failureEvent as VerificationEvent.Error:
                        self.alert = AlertDialog(title: "Face verification failed", message: failureEvent.message)
                        self.isLoading = false

                    case is VerificationEvent.Loading:
                        self.isLoading = true

                    case is VerificationEvent.Canceled:
                        self.isLoading = false

                    default:
                        break
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

    private func presentOffer(_ offer: RespondableCredentialOffer) {
        alert = nil
        offerSheet = CredentialOfferSheetState(offer: offer)
    }

    func toggleCredentialSelection(id: UUID) {
        guard var sheet = offerSheet else { return }
        sheet.toggleSelection(id: id)
        if case .failed = sheet.status {
            sheet.status = .idle
        }
        offerSheet = sheet
    }

    func confirmCredentialSelection() {
        guard let sheet = offerSheet else { return }
        let selected = sheet.selectedDescriptors
        guard !selected.isEmpty else {
            alert = AlertDialog(
                title: "Select a credential",
                message: "Choose at least one credential to add."
            )
            return
        }

        var submitting = sheet
        submitting.status = .submitting
        offerSheet = submitting

        let offer = sheet.offer
        let sheetId = sheet.id

        Task {
            do {
                let result = try await offer.accept(credentials: selected)
                await MainActor.run {
                    self.updateOfferSheet(id: sheetId) { state in
                        self.apply(result: result, to: &state)
                    }
                }
            } catch {
                await MainActor.run {
                    self.updateOfferSheet(id: sheetId) { state in
                        state.status = .failed(message: error.localizedDescription)
                    }
                }
            }
        }
    }

    func submitTransactionCode(_ code: String) {
        guard let sheet = offerSheet,
              case .transactionCodeRequired(let challenge) = sheet.status else { return }

        var submitting = sheet
        submitting.status = .submitting
        offerSheet = submitting

        let sheetId = sheet.id

        Task {
            do {
                let summary = try await challenge.respond(txCode: code)
                await MainActor.run {
                    self.updateOfferSheet(id: sheetId) { state in
                        state.status = .completed(summary: summary)
                    }
                }
            } catch {
                await MainActor.run {
                    self.updateOfferSheet(id: sheetId) { state in
                        state.status = .failed(message: error.localizedDescription)
                    }
                }
            }
        }
    }

    func dismissOfferSheet() {
        let shouldComplete: Bool
        if case .completed = offerSheet?.status {
            shouldComplete = true
        } else {
            shouldComplete = false
        }

        offerSheet = nil

        if shouldComplete {
            completion()
        }
    }

    private func updateOfferSheet(id: UUID, mutate: (inout CredentialOfferSheetState) -> Void) {
        guard var sheet = offerSheet, sheet.id == id else { return }
        mutate(&sheet)
        offerSheet = sheet
    }

    private func apply(result: IssuanceResult, to state: inout CredentialOfferSheetState) {
        if let immediate = result as? IssuanceResultImmediate {
            state.status = .completed(summary: immediate.summary)
            return
        }

        if result is IssuanceResultEmpty {
            state.status = .failed(message: "The issuer did not issue any credentials.")
            return
        }

        if let txRequired = result as? IssuanceResultTransactionCodeRequired {
            state.status = .transactionCodeRequired(challenge: txRequired.challenge)
            return
        }

        state.status = .failed(message: "Unsupported issuance result")
    }
}
