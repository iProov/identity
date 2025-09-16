//
//  JwtView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 27/01/2025.
//

import SwiftUI
import identity

struct JwtView: View {
    let displayName: String
    let jwt: Jwt
    
    var body: some View {
        NavigationView {
            List {
                if (jwt.value != nil ) {
                    Section{
                        Text(String(describing: jwt.value!))
                    } header: { Text("Value") }
                }
                
                Section{
                    Text("Verification Status: \(String(describing: jwt.verificationStatus))")
                } header: { Text("Metadata") }
            }
            .background(.background.secondary)
            .navigationTitle(displayName)
        }
    }
}

#Preview {
    JwtView(displayName:"Example", jwt: Jwt(compactString: "dsfsddsfdsxcxv.xadsdawe.eewasdsa"))
}
