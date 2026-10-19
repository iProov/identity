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

    /// Storage is shared with the document-provider extension, which needs the credential file and
    /// both keys to build a response in its own process. Both groups come from Info.plist, see
    /// `WalletGroups`; passing the keychain group is what enables the Digital Credentials API.
    private let wallet: Result<Wallet, Error> = Result {
        try WalletFactory.shared.getInstance(
            baseUrl: "https://api.dev-eu.iproov.id",
            clientConfiguration: OID4VCIClientConfiguration(
                clientId: AuthorizationCodeSettings.clientId,
                redirectUri: AuthorizationCodeSettings.redirectUri
            ),
            isLoggingEnabled: true,
            storageEngine: DeviceBoundAppleStorageEngine(
                appGroupIdentifier: WalletGroups.appGroupIdentifier,
                accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked,
                keychainAccessGroup: WalletGroups.keychainAccessGroup
            ),
            trustConfiguration: TrustConfiguration()
        )
    }

    var body: some Scene {
        WindowGroup {
            switch wallet {
            case .success(let wallet):
                HomeView(wallet: wallet)
            case .failure(let error):
                ErrorContent(reason: error.localizedDescription)
            }
        }
    }
}
