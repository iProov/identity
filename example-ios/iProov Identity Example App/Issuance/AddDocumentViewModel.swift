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

@MainActor
class AddDocumentViewModel: ObservableObject {
    @Published var isLoading = false
    @Published var failure: AlertDialog? = nil
    @Published var offerSheet: CredentialOfferSheetState? = nil
    
    private let wallet = WalletFactory.shared.instance!
    private let loginRequest: LoginRequest?
    private let completion: () -> Void
    
    init(loginRequest: LoginRequest?, completion: @escaping () -> Void) {
        self.loginRequest = loginRequest
        self.completion = completion
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
            let description = txRequired.challenge.details.description_ ?? "A transaction code is required to complete issuance."
            state.status = .transactionCodeRequired(description: description)
            return
        }

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
