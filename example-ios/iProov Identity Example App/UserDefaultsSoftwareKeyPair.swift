import CryptoKit
import Foundation
import identity

/// An intentionally simple software signing key for demonstrating the Swift overlay.
///
/// This example persists raw private-key material in `UserDefaults`, which is not
/// secure storage. Production applications should use the Keychain, Secure Enclave,
/// or an appropriately protected external key provider.
///
/// The example app does not instantiate or use this class.
final class UserDefaultsSoftwareKeyPair: WalletSigningKey {
    private let privateKey: P256.Signing.PrivateKey

    /// Loads the existing P-256 private key or creates and persists a new one.
    init(
        userDefaults: UserDefaults = .standard,
        storageKey: String = "com.iproov.identity.example.software-signing-key"
    )  {
        if let storedKey = userDefaults.data(forKey: storageKey) {
            privateKey = try! P256.Signing.PrivateKey(rawRepresentation: storedKey)
        } else {
            let generatedKey = P256.Signing.PrivateKey()
            userDefaults.set(generatedKey.rawRepresentation, forKey: storageKey)
            privateKey = generatedKey
        }
    }

    var publicKey: WalletPublicKey {
        get throws {
            let representation = privateKey.publicKey.x963Representation
            guard representation.count == 65, representation.first == 0x04 else {
                throw UserDefaultsSoftwareKeyPairError.invalidPublicKey
            }

            let coordinates = representation.dropFirst()
            let x = Data(coordinates.prefix(32))
            let y = Data(coordinates.dropFirst(32))

            return WalletPublicKey(
                x: x.base64URLEncodedString,
                y: y.base64URLEncodedString
            )
        }
    }

    var subjectPublicKeyInfo: Data {
        privateKey.publicKey.derRepresentation
    }

    func sign(_ message: Data) throws -> Data {
        try privateKey.signature(for: message).derRepresentation
    }
}

private enum UserDefaultsSoftwareKeyPairError: Error {
    case invalidPublicKey
}

private extension Data {
    var base64URLEncodedString: String {
        base64EncodedString()
            .replacingOccurrences(of: "+", with: "-")
            .replacingOccurrences(of: "/", with: "_")
            .replacingOccurrences(of: "=", with: "")
    }
}
