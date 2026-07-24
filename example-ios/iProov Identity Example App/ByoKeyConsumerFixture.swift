// Swift consumer fixture for the "bring your own key management" overlay.
//
// This is deliberately not used by the example app. It keeps the public Swift
// contracts type-checked as part of the example target.

import Foundation
import identity

/// A caller-supplied signing key implemented entirely in Swift.
class TestSigningKey: WalletSigningKey {
    var publicKey: WalletPublicKey {
        WalletPublicKey(
            x: "bbOOQ8Qo4gtS1HWOLEE-K7u9iOQPIJsvRLMkXKrQqjY",
            y: "8t3r-0kkZE9RS8870QtwSKODU4hYnLm_v_oNkRuQ0Us"
        )
    }

    var subjectPublicKeyInfo: Data {
        Data([0x30, 0x59])
    }

    func sign(_ message: Data) throws -> Data {
        // A minimal, valid DER ECDSA-shaped signature: SEQUENCE { INTEGER 1, INTEGER 2 }.
        Data([0x30, 0x06, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02])
    }
}

/// Proves a Swift-defined signing key can opt into key attestation.
final class TestAttestableSigningKey: TestSigningKey, AttestableWalletSigningKey {
    var keyAttestationEvidence: WalletKeyAttestationEvidence? {
        WalletKeyAttestationEvidence(
            certificateChainDER: [Data([0x30, 0x01, 0x00])],
            keyStorageLevel: .moderate,
            userAuthenticationLevel: .moderate
        )
    }
}

/// A caller-supplied storage-encryption key implemented entirely in Swift.
final class TestStorageEncryptionKey: WalletStorageEncryptionKey {
    func encrypt(_ plaintext: Data) throws -> Data {
        plaintext
    }

    func decrypt(_ ciphertext: Data) throws -> Data {
        ciphertext
    }
}

/// Proves the Swift-native factories accept the overlay protocols end to end.
///
/// This is intentionally not called; creating a wallet is outside this fixture's
/// runtime checks.
private func makeWalletWithSwiftKeys() -> Wallet {
    let signingKey = TestSigningKey()
    let storageKey = TestStorageEncryptionKey()
    let storageEngine = DeviceBoundAppleStorageEngine(
        accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked,
        storageEncryptionKeyFactory: { storageKey }
    )

    return WalletFactory.shared.getInstance(
        baseUrl: "https://api.beta.iproov.id",
        storageEngine: storageEngine,
        signingKeyFactory: { signingKey }
    )
}

/// Exercises the Swift-native contracts without exposing any Kotlin bridge types.
@discardableResult
func runByoKeyConsumerFixtureChecks() throws -> String {
    let signer: any WalletSigningKey = TestSigningKey()
    let attestableSigner: any AttestableWalletSigningKey = TestAttestableSigningKey()
    let encryptionKey: any WalletStorageEncryptionKey = TestStorageEncryptionKey()

    let publicKey = try signer.publicKey
    let signature = try signer.sign(Data([0x01, 0x02, 0x03]))
    let attestationEvidence = attestableSigner.keyAttestationEvidence
    let attestedSignature = try attestableSigner.sign(Data([0x04, 0x05, 0x06]))

    let plaintext = Data([0x09, 0x08, 0x07])
    let roundTripped = try encryptionKey.decrypt(encryptionKey.encrypt(plaintext))

    precondition(publicKey.algorithm == "ES256", "unexpected algorithm")
    precondition(!signature.isEmpty, "empty signature")
    precondition(attestationEvidence != nil, "missing attestation evidence")
    precondition(
        attestationEvidence?.certificateChainDER.count == 1,
        "unexpected attestation certificate chain"
    )
    precondition(!attestedSignature.isEmpty, "empty attested-key signature")
    precondition(roundTripped == plaintext, "storage round-trip changed data")

    return "BYO key fixture OK — algorithm=\(publicKey.algorithm), "
        + "sigBytes=\(signature.count), "
        + "attestationCertificates=\(attestationEvidence?.certificateChainDER.count ?? 0), "
        + "storageRoundTripBytes=\(roundTripped.count)"
}
