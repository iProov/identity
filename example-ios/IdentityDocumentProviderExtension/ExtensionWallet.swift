//
//  ExtensionWallet.swift
//  iProov Identity Example App
//
//  Created by Owen Woodward on 26/08/2026.
//
import identity


enum ExtensionWallet {

    /// Both groups come from this target's Info.plist (see `WalletGroups`), so they cannot drift from
    /// the app's. A misconfigured container fails the request that needs the wallet, not the process.
    static let shared: Result<Wallet, Error> = Result {
        try WalletFactory.shared.getInstance(
            baseUrl: "https://api.dev-eu.iproov.id",
            isLoggingEnabled: true,
            storageEngine: DeviceBoundAppleStorageEngine(
                appGroupIdentifier: WalletGroups.appGroupIdentifier,
                accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked,
                keychainAccessGroup: WalletGroups.keychainAccessGroup
            ),
            trustConfiguration: TrustConfiguration()
        )
    }
}
