//
//  AddDocumentViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//

import Foundation
import SwiftUI
import identity
import NFCPassportReader
import MRZScanner
import AuthenticationServices

@MainActor
class AddDocumentViewModel: ObservableObject {
    @Published var isLoading = false
    @Published var failure: AlertDialog? = nil
    @Published var offerSheet: CredentialOfferSheetState? = nil
    @Published var isScanningCredentialOffer = false

    private let wallet = WalletFactory.shared.instance!
    private let loginRequest: LoginRequest?
    private let initialCredentialOfferUri: String?
    private let completion: () -> Void
    private let authorizationLauncher = AuthorizationSessionLauncher()
    private var sheetDismissalContinuation: CheckedContinuation<Void, Never>?
    private var hasHandledInitialCredentialOffer = false

    init(
        loginRequest: LoginRequest?,
        initialCredentialOfferUri: String?,
        completion: @escaping () -> Void
    ) {
        self.loginRequest = loginRequest
        self.initialCredentialOfferUri = initialCredentialOfferUri
        self.completion = completion
    }

    func handleAppear() {
        guard !hasHandledInitialCredentialOffer,
              let initialCredentialOfferUri else { return }

        hasHandledInitialCredentialOffer = true
        handleCredentialOfferUri(initialCredentialOfferUri)
    }

    // MARK: - OID4VCI Credential Offer

    /// Handles a scanned OID4VCI credential offer QR code.
    func handleCredentialOfferQrCode(_ code: String) {
        isScanningCredentialOffer = false
        handleCredentialOfferUri(code)
    }

    private func handleCredentialOfferUri(_ uri: String) {
        guard let url = URL(string: uri),
              OpenIdSchemeSupport.route(for: url) == .credentialOffer else {
            failure = AlertDialog(
                title: "Invalid QR Code",
                message: "The scanned QR code is not a valid OID4VCI credential offer. Expected scheme: openid-credential-offer:// or haip-vci://"
            )
            return
        }

        addCredentialWithOffer(uri: uri)
    }

    /// Initiates the OID4VCI credential offer flow with the given URI.
    private func addCredentialWithOffer(uri: String) {
        isLoading = true
        Task {
            do {
                let offer = try await wallet.addCredentialWithOffer(uri: uri)
                isLoading = false
                presentOffer(offer)
            } catch {
                isLoading = false
                failure = AlertDialog(
                    title: "Failed to resolve credential offer",
                    message: error.localizedDescription
                )
            }
        }
    }
    
    /// Adds a pre-defined demo MRTD credential to the wallet.
    func addDemoDocument() {
        isLoading = true
        Task {
            do {
                let demoDocument = try await wallet.createDemoMrtd()
                let documentChallenge = try await wallet.addDocumentWithMrz(
                    mrz: demoDocument.mrz,
                    loginRequest: loginRequest,
                    addLegacyCredential: false
                )

                guard let responder = documentChallenge.respond else {
                    throw NSError(domain: "AddDocumentError", code: 2, userInfo: [NSLocalizedDescriptionKey: "No credential offer responder returned."])
                }

                guard let offer = try await responder.withMrtd(
                    mrtd: demoDocument,
                    accessControl: .bac,
                    signature: nil
                ) else {
                    throw NSError(domain: "AddDocumentError", code: 4, userInfo: [NSLocalizedDescriptionKey: "No credential offer returned by issuer."])
                }

                isLoading = false
                presentOffer(offer)
                return
            } catch {
                failure = AlertDialog(title: "Failed to add demo document", message: error.localizedDescription)
            }
            isLoading = false
        }
    }
    
    /// Reads document data from an NFC chip using the scanned MRZ result.
    func readDocument(from mrzResult: ParsedResult) {
        isLoading = true
        Task {
            do {
                guard let documentNumber = mrzResult.documentNumber,
                      let dob = mrzResult.birthdate?.toYYMMDDString(),
                      let doe = mrzResult.expiryDate?.toYYMMDDString() else {
                    throw NSError(domain: "AddDocumentError", code: 1, userInfo: [NSLocalizedDescriptionKey: "Invalid MRZ data."])
                }
                
                let challenge = try await wallet.addDocumentWithFields(
                    documentNumber: documentNumber,
                    dateOfBirth: dob,
                    dateOfExpiry: doe,
                    loginRequest: loginRequest,
                    addLegacyCredential: false
                )
                
                let key = MRZKey(documentNumber: documentNumber, dateOfBirth: dob, dateOfExpiry: doe).key
                
                let passportReader = PassportReader()
                let result = try await passportReader.readPassport(mrzKey: key)
                let mrtd = try result.dataGroupsRead.toMrtd()
                
                let accessControl: AccessControl = result.PACEStatus == .success ? .pace : .bac

                guard let responder = challenge.respond else {
                    throw NSError(domain: "AddDocumentError", code: 3, userInfo: [NSLocalizedDescriptionKey: "No credential offer responder returned."])
                }

                guard let offer = try await responder.withMrtd(
                    mrtd: mrtd,
                    accessControl: accessControl,
                    signature: nil
                ) else {
                    throw NSError(domain: "AddDocumentError", code: 5, userInfo: [NSLocalizedDescriptionKey: "No credential offer returned by issuer."])
                }

                isLoading = false
                presentOffer(offer)
                return
                
            } catch {
                failure = AlertDialog(title: "Failed to read document", message: error.localizedDescription)
            }
            isLoading = false
        }
    }

    private func presentOffer(_ offer: RespondableCredentialOffer) {
        failure = nil
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
            failure = AlertDialog(
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

    /// Called by the sheet's `onDismiss` callback to signal that the sheet has fully dismissed.
    func onOfferSheetDismissed() {
        sheetDismissalContinuation?.resume()
        sheetDismissalContinuation = nil
    }

    /// Handles the authorization code flow by dismissing the sheet and launching
    /// ASWebAuthenticationSession directly (can't present browser over a sheet).
    private func handleAuthorizationRequired(
        _ authRequired: IssuanceResultAuthorizationRequired,
        offer: RespondableCredentialOffer
    ) async {
        guard let url = URL(string: authRequired.authorizationUrl) else {
            failure = AlertDialog(title: "Authorization Error", message: "Invalid authorization URL")
            return
        }

        // Dismiss the sheet and wait for the dismiss animation to fully complete
        // before presenting ASWebAuthenticationSession (can't present over a sheet).
        isLoading = true
        await withCheckedContinuation { continuation in
            sheetDismissalContinuation = continuation
            offerSheet = nil
        }

        do {
            let response = try await authorizationLauncher.authorize(url: url)
            isLoading = true
            let summary = try await authRequired.respond(
                authorizationCode: response.authorizationCode,
                state: response.state,
                iss: response.iss
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
            failure = AlertDialog(title: "Authorization Failed", message: error.localizedDescription)
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
            state.status = .failed(message: "The issuer did not return any credentials.")
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



struct MRZKey {  // Or whatever struct/class you're using to hold the key
    let key: String

    init(documentNumber: String, dateOfBirth: String, dateOfExpiry: String) {
        let paddedDocumentNumber = documentNumber.padding(toLength: 9, withPad: "<", startingAt: 0)

        let documentNumberField = MrzField(paddedDocumentNumber)
        let dateOfBirthField = MrzField(dateOfBirth)
        let dateOfExpiryField = MrzField(dateOfExpiry)

        self.key = documentNumberField.valueWithChecksum +
                   dateOfBirthField.valueWithChecksum +
                   dateOfExpiryField.valueWithChecksum
    }
}

let chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
let weights = [7, 3, 1]

struct MrzField {
    let value: String
    let checksum: Int

    init(_ value: String) {
        self.value = value
        self.checksum = MrzField.computeChecksum(value)
    }

    init?(fromStringWithChecksum value: String) {
        guard let checksum = Int(String(value.suffix(1))) else { return nil }
        self.value = String(value.prefix(value.count - 1))
        self.checksum = checksum
    }

    var isValid: Bool {
        return checksum == MrzField.computeChecksum(value)
    }

    var valueWithChecksum: String {
        return value + String(checksum)
    }

    static func computeChecksum(_ value: String) -> Int {
        var sum = 0
        for (i, char) in value.enumerated() {
            let weight = weights[i % weights.count]
            let charIndex: Int
            if char == "<" {
                charIndex = 0
            } else if let index = chars.firstIndex(of: char) {
                charIndex = chars.distance(from: chars.startIndex, to: index)
            } else {
                // Handle invalid characters (e.g., throw an error or return a default value)
                print("Invalid character in MRZ: \(char)") // Or throw an error
                return 0 // Or throw
            }
            sum += charIndex * weight
        }
        return sum % 10
    }
}


extension Date {
    func toYYMMDDString() -> String {
        let formatter = DateFormatter()
        formatter.dateFormat = "yyMMdd" // Note the lowercase 'yy' for two-digit year
        return formatter.string(from: self)
    }
}

extension Dictionary<DataGroupId, DataGroup>{

    func toMrtd() throws -> Mrtd{
        return Mrtd(
            sod: self[DataGroupId.SOD]!.bytes!,
            dg1: self[DataGroupId.DG1]!.bytes!,
            dg2: self[DataGroupId.DG2]!.bytes!,
            dg3: self[DataGroupId.DG3]?.bytes,
            dg4: self[DataGroupId.DG4]?.bytes,
            dg5: self[DataGroupId.DG5]?.bytes,
            dg6: self[DataGroupId.DG6]?.bytes,
            dg7: self[DataGroupId.DG7]?.bytes,
            dg8: self[DataGroupId.DG8]?.bytes,
            dg9: self[DataGroupId.DG9]?.bytes,
            dg10: self[DataGroupId.DG10]?.bytes,
            dg11: self[DataGroupId.DG11]?.bytes,
            dg12: self[DataGroupId.DG12]?.bytes,
            dg13: self[DataGroupId.DG13]?.bytes,
            dg14: self[DataGroupId.DG14]?.bytes,
            dg15: self[DataGroupId.DG15]?.bytes,
            dg16: self[DataGroupId.DG16]?.bytes,
            dg17: nil,
            dg18: nil,
            dg19: nil,
            com:  self[DataGroupId.COM]!.bytes!,
            cvca: nil
        )
    }
}


extension DataGroup {
    var bytes: Data? {
        return Data(self.data)
    }
}
