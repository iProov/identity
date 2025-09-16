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
                let documentChallenge = try await wallet.addDocumentWithMrz(mrz: demoDocument.mrz, loginRequest: loginRequest)

                let signature: Data?  = nil
                try await documentChallenge.respond?.withMrtd(mrtd: demoDocument, accessControl: .bac, signature: signature)
                
                completion()
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
                
                let challenge = try await wallet.addDocumentWithFields(documentNumber: documentNumber, dateOfBirth: dob, dateOfExpiry: doe, loginRequest: loginRequest)
                
                let key = MRZKey(documentNumber: documentNumber, dateOfBirth: dob, dateOfExpiry: doe).key
                
                let passportReader = PassportReader()
                let result = try await passportReader.readPassport(mrzKey: key)
                let mrtd = try result.dataGroupsRead.toMrtd()
                
                let accessControl: AccessControl = result.PACEStatus == .success ? .pace : .bac
                        
                let signature: Data? = nil
                try await challenge.respond!
                    .withMrtd(mrtd: mrtd, accessControl: accessControl, signature: signature)
                
                completion()
                
            } catch {
                failure = AlertDialog(title: "Failed to read document", message: error.localizedDescription)
            }
            isLoading = false
        }
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
