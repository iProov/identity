//
//  StorageProbe.swift
//  iProov Identity Example App
//
//  Created by Owen Woodward on 27/08/2026.
//

import Foundation
import Security

/// Reports where the wallet's storage actually lives.
///
/// Useful from both the app and the extension: run it in each and compare. The keys should read the
/// same access group in both, and the App Group container should report the same size — the app's own
/// Application Support is never visible to the extension.
///
/// Deliberately raw `Security`/`Foundation` calls, so it still reports when the SDK itself throws.
enum StorageProbe {
    static let appGroup = (try? WalletGroups.appGroupIdentifier) ?? "unset"
    static let signingKeyTag = "com.iproov.identity"
    static let encryptionKeyTag = "com.iproov.identity.encryption"

    static func report(_ label: String) -> String {
        var out = ["[probe:\(label)]"]
        for tag in [signingKeyTag, encryptionKeyTag] {
            let groups = allKeyGroups(tag)
            switch groups.count {
            case 0:
                out.append("  key \(tag) -> UNREACHABLE")
            case 1:
                out.append("  key \(tag) -> \(groups[0])")
            default:
                // Two keys under one tag means something created a second one. SecItemCopyMatching
                // returns an unspecified single match, so which one the SDK gets is then a coin toss.
                out.append("  key \(tag) -> DUPLICATE x\(groups.count): \(groups.joined(separator: ", "))")
            }
        }
        out.append("  file AppSupport -> \(appSupportFile())")
        out.append("  file AppGroup   -> \(appGroupFile())")
        return out.joined(separator: "\n")
    }

    /// Every key carrying [tag], across all groups this process can reach.
    ///
    /// Unscoped on purpose — no `kSecAttrAccessGroup` — so it finds a key wherever it lives. A miss
    /// cannot distinguish "absent" from "present but unreachable"; compare the app and the extension
    /// to tell those apart.
    private static func allKeyGroups(_ tag: String) -> [String] {
        let query: [String: Any] = [
            kSecClass as String: kSecClassKey,
            kSecAttrApplicationTag as String: Data(tag.utf8),
            kSecAttrKeyType as String: kSecAttrKeyTypeECSECPrimeRandom,
            kSecReturnAttributes as String: true,
            kSecMatchLimit as String: kSecMatchLimitAll,
        ]
        var items: CFTypeRef?
        guard SecItemCopyMatching(query as CFDictionary, &items) == errSecSuccess,
              let attrs = items as? [[String: Any]] else { return [] }
        return attrs.compactMap { $0[kSecAttrAccessGroup as String] as? String }
    }

    private static func appSupportFile() -> String {
        guard let dir = FileManager.default
            .urls(for: .applicationSupportDirectory, in: .userDomainMask).first
        else { return "no dir" }
        return size(dir.appendingPathComponent("com.iproov.identity"))
    }

    private static func appGroupFile() -> String {
        guard let container = FileManager.default
            .containerURL(forSecurityApplicationGroupIdentifier: appGroup)
        else { return "CONTAINER NIL (entitlement not applied)" }
        return size(container.appendingPathComponent("com.iproov.identity"))
    }

    private static func size(_ url: URL) -> String {
        guard let bytes = (try? FileManager.default
            .attributesOfItem(atPath: url.path))?[.size] as? Int
        else { return "absent" }
        return "\(bytes) bytes"
    }
}
