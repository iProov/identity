//
//  iProov_Identity_Sample_AppApp.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 19/12/2024.
//

import SwiftUI
import identity

@main
struct SampleApp: App {

    let wallet = WalletFactory.shared.getInstance(
        baseUrl: "https://api.dev-eu.iproov.id",
        clientConfiguration: OID4VCIClientConfiguration(
            clientId: AuthorizationCodeSettings.clientId,
            redirectUri: AuthorizationCodeSettings.redirectUri
        ),
        isLoggingEnabled: true
    )
    
    var body: some Scene {
        WindowGroup {
            HomeView(wallet: wallet)
        }
    }
}
 
