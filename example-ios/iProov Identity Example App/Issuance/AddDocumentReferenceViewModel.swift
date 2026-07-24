//
//  AddDocumentReferenceViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//

import Foundation
import SwiftUI
import identity
import AuthenticationServices

@MainActor
class AddDocumentReferenceViewModel: ObservableObject {
    @Published var reference = ""
    @Published var isLoading = false
    @Published var alert: AlertDialog? = nil
    @Published var offerSheet: CredentialOfferSheetState? = nil

    private let completion: () -> Void
    private let wallet = WalletFactory.shared.instance!
    private var activeAuthSession: ASWebAuthenticationSession?

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
                options: nil,
                addLegacyCredential: false,
                
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
        let hasPreAuth = offer.availableGrants.contains { $0 is AvailableGrant.PreAuthorizedCode }
        let hasAuthCode = offer.availableGrants.contains { $0 is AvailableGrant.AuthorizationCode }
        let preferAuthCode = AppSettings.shared.preferAuthorizationCode
        let useAuthCode = (preferAuthCode && hasAuthCode) || !hasPreAuth

        Task {
            do {
                let result = useAuthCode
                    ? try await offer.authorize(credentials: selected)
                    : try await offer.accept(credentials: selected)

                // Authorization code flow: dismiss sheet and launch browser externally
                if let authRequired = result as? IssuanceResultAuthorizationRequired {
                    await handleAuthorizationRequired(authRequired, offer: offer)
                    return
                }

                self.updateOfferSheet(id: sheetId) { state in
                    self.apply(result: result, to: &state)
                }
            } catch {
                self.updateOfferSheet(id: sheetId) { state in
                    state.status = .failed(message: error.localizedDescription)
                }
            }
        }
    }

    // MARK: - Authorization Code Flow

    private func handleAuthorizationRequired(
        _ authRequired: IssuanceResultAuthorizationRequired,
        offer: RespondableCredentialOffer
    ) async {
        guard let url = URL(string: authRequired.authorizationUrl) else {
            alert = AlertDialog(title: "Authorization Error", message: "Invalid authorization URL")
            return
        }

        // Dismiss the sheet first - ASWebAuthenticationSession can't present over it
        offerSheet = nil
        isLoading = true

        // Wait for sheet dismissal animation to complete
        try? await Task.sleep(nanoseconds: 600_000_000)

        do {
            let response = try await launchAuthSession(url: url)
            isLoading = true
            let summary = try await authRequired.respond(
                authorizationCode: response.authorizationCode,
                state: response.state
            )
            isLoading = false

            // Re-present the offer sheet with completed status
            var completedSheet = CredentialOfferSheetState(offer: offer)
            completedSheet.status = .completed(summary: summary)
            offerSheet = completedSheet
        } catch is CancellationError {
            isLoading = false
        } catch {
            isLoading = false
            alert = AlertDialog(title: "Authorization Failed", message: error.localizedDescription)
        }
    }

    private func launchAuthSession(url: URL) async throws -> (authorizationCode: String, state: String) {
        defer { activeAuthSession = nil }

        return try await withCheckedThrowingContinuation { continuation in
            let session = ASWebAuthenticationSession(
                url: url,
                callbackURLScheme: "com.iproov.identity"
            ) { callbackURL, error in
                if let error = error as? ASWebAuthenticationSessionError,
                   error.code == .canceledLogin {
                    continuation.resume(throwing: CancellationError())
                    return
                }

                if let error = error {
                    continuation.resume(throwing: error)
                    return
                }

                guard let callbackURL = callbackURL,
                      let components = URLComponents(url: callbackURL, resolvingAgainstBaseURL: false),
                      let authorizationCode = components.queryItems?.first(where: { $0.name == "code" })?.value,
                      let state = components.queryItems?.first(where: { $0.name == "state" })?.value else {
                    continuation.resume(throwing: NSError(
                        domain: "AuthError", code: 1,
                        userInfo: [NSLocalizedDescriptionKey: "Authorization response is missing its code or state"]
                    ))
                    return
                }

                continuation.resume(returning: (authorizationCode, state))
            }

            session.presentationContextProvider = WebAuthContextProvider.shared
            session.prefersEphemeralWebBrowserSession = false
            activeAuthSession = session

            if !session.start() {
                activeAuthSession = nil
                continuation.resume(throwing: NSError(
                    domain: "AuthError", code: 2,
                    userInfo: [NSLocalizedDescriptionKey: "Failed to start authorization browser"]
                ))
            }
        }
    }

    // MARK: - Transaction Code Flow

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
                self.updateOfferSheet(id: sheetId) { state in
                    state.status = .completed(summary: summary)
                }
            } catch {
                self.updateOfferSheet(id: sheetId) { state in
                    state.status = .failed(message: error.localizedDescription)
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

        // AuthorizationRequired is handled before reaching apply()
        state.status = .failed(message: "Unsupported issuance result")
    }
}
