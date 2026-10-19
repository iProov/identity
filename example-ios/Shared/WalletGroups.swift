//
//  WalletGroups.swift
//  iProov Identity Example App
//
//  Compiled into both the app and the document-provider extension.
//

import Foundation

/// The two groups the wallet is configured with, read from the target's own Info.plist so each target
/// declares them once, next to the entitlements they must match. The keychain group is written as
/// `$(AppIdentifierPrefix)…` in the plist, so the team ID is never typed by hand.
enum WalletGroups {
    static var appGroupIdentifier: String {
        get throws { try value("IPIAppGroupIdentifier") }
    }

    static var keychainAccessGroup: String {
        get throws { try value("IPIKeychainAccessGroup") }
    }

    private static func value(_ key: String) throws -> String {
        guard let value = Bundle.main.object(forInfoDictionaryKey: key) as? String, !value.isEmpty else {
            throw Failure.missing(key)
        }
        // Only the Info.plist processor expands $(AppIdentifierPrefix); an unexpanded value means the
        // target has no Development Team, and the SDK would then look for keys in a group that cannot exist.
        guard !value.contains("$(") else { throw Failure.unexpanded(key) }
        return value
    }

    enum Failure: LocalizedError {
        case missing(String)
        case unexpanded(String)

        var errorDescription: String? {
            switch self {
            case .missing(let key):
                "Info.plist has no \(key)."
            case .unexpanded(let key):
                "Info.plist \(key) was not expanded. Set a Development Team on this target."
            }
        }
    }
}
