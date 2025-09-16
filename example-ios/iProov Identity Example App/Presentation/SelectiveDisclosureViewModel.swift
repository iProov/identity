//
//  LoginRequestViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 28/01/2025.
//

import Foundation
import identity
import SwiftUI

typealias ClaimNameToValue = [String:Claim]

enum CredentialType: Identifiable {
    var id: Self { self }
    
    case Document
    case Reference
    case Email
    case Phone
}

class SelectiveDisclosureViewModel: ObservableObject{
       
    @Published var isLoading = false
    @Published var claimsInWallet: ClaimNameToValue = [:]
    @Published var claimsToShare : ClaimNameToValue = [:]
    @Published var requiredClaimsNotBeingShared: [RequestedClaim]  = []
    
    @Published var isShowingSuccessAlert = false
    
    let loginRequest: RespondableLoginRequest
    
    init(loginRequest: RespondableLoginRequest){
        self.loginRequest = loginRequest
    }
    
    func load(){
        isLoading = true
        DispatchQueue.global(qos: .userInitiated).async {
            let claims = (try? WalletFactory.shared.instance!.getAllClaims()) ?? []
            var inWallet : ClaimNameToValue = [:]
            for claim in claims{ inWallet[claim.name] = claim }
            
            // Automatically share claims that are required and in the wallet
            var toShare: ClaimNameToValue = [:]
            for requestedClaim in self.loginRequest.claims{
                if inWallet.keys.contains(where: {$0 == requestedClaim.name}) {
                    toShare[requestedClaim.name] = inWallet[requestedClaim.name]
                } else if requestedClaim.source != nil && !self.requiredClaimsNotBeingShared.contains(
                    where: {$0.source == requestedClaim.source}) {
                    self.requiredClaimsNotBeingShared.append(requestedClaim)
                }
            }
        
            DispatchQueue.main.sync {
                self.isLoading = false
                self.claimsInWallet = inWallet
                self.claimsToShare = toShare
                print("loaded claims from wallet")
                print("Required claims not being shared: \(self.requiredClaimsNotBeingShared)")
            }
        }
    }

    // Determines if all essential claims are present in the claimsToShare dictionary
    var canShare: Bool {
       loginRequest.claims.filter { $0.isEssential }.allSatisfy { claimsToShare[$0.name] != nil }
    }
   
    // Returns an array of requested claims that are essential but not yet included in claimsToShare
//    var requiredClaimsNotBeingShared: [RequestedClaim] {
//       loginRequest.claims.filter { $0.isEssential && claimsToShare[$0.name] == nil }
//    }
}

extension RequestedClaim {
    static let knownClaimsNamesToSource: [String: CredentialType] = [
        "name": .Document, "given_name": .Document, "family_name": .Document,
        "birthdate": .Document, "gender": .Document, "com.svipe:document_number": .Document,
        "com.svipe:document_portrait": .Document, "com.svipe:document_issuing_country": .Document,
        "com.svipe:document_issuing_country_en": .Document, "com.svipe:document_nationality": .Document,
        "com.svipe:document_nationality_en": .Document, "com.svipe:document_type": .Document,
        "com.svipe:document_verified": .Document, "com.svipe:face_verified": .Document,
        "com.svipe:document_administrative_number": .Document, "com.svipe:document_type_sdn": .Document,
        "com.svipe:document_expiry_date": .Document, "com.svipe:document_type_sdn_en": .Document,
        "phone_number": .Phone, "email_address": .Email
    ]
    
    var source: CredentialType? {
        RequestedClaim.knownClaimsNamesToSource[self.name]
    }
}
