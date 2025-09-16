//
//  CredentialsView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 16/01/2025.
//

import Foundation
import SwiftUI
import identity

struct CredentialsView: View {

    let credentials: [Credential]
    @State var list: [Displayable]
    let deleteCredential: ((Credential) -> Void)
    let verifyCredential: ((Credential) -> Void)

    init(
        credentials: [Credential],
        deleteCredential: @escaping ((Credential) -> Void),
        verifyCredential: @escaping ((Credential) -> Void)
    ) {
        self.credentials = credentials
        self.list = credentials.toDisplayable()
        self.deleteCredential = deleteCredential
        self.verifyCredential = verifyCredential
    }

    var body: some View {
        List {
            ForEach(credentials) { credential in
                Section {
                    ForEach(credential.claims) { claim in
                        NavigationLink(
                            destination: JwtView(displayName: claim.displayName ?? claim.name, jwt: claim.jwt)
                        ) {
                            Text(claim.displayName ?? claim.name)
                        }
                    }
                    if credential is Credential.IdentityCredentialMrtd && !credential.claims.contains(where: {
                        $0.name == "com.svipe:face_verified"
                    }){
                        Button("Verify") {
                            verifyCredential(credential)
                        }
                    }

                    if !credential.source.contains("wallet:") {
                        Button("Delete", role: .destructive) {
                            deleteCredential(credential)
                        }
                    }
                } header: {
                    Text(credential.source)
                }
            }
        }
    }
}

struct Displayable: Identifiable {
    let text: String
    let isParent: Bool
    let items: [Displayable]?
    let id: String
}

extension Claim: Identifiable, Comparable {
    public static func < (lhs: Claim, rhs: Claim) -> Bool {
        return true
    }
}
extension Credential: Identifiable {}

extension [Credential] {
    func toDisplayable() -> [Displayable] {
        return self.map { credential in
            let items = credential.claims.map { claim in
                Displayable(text: claim.name, isParent: false, items: nil, id: claim.name)
            }
            return Displayable(text: credential.source, isParent: true, items: items, id: credential.source)
        }
    }
}
