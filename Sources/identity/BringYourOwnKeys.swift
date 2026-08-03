import Foundation
import iProovIdentity

/// The public portion of an ES256 P-256 signing key.
///
/// `x` and `y` are unsigned 32-byte coordinates encoded with unpadded Base64URL.
public struct WalletPublicKey: Equatable, Sendable {
    public let algorithm: String
    public let curve: String
    public let keyType: String
    public let x: String
    public let y: String
    public let keyID: String?

    public init(
        algorithm: String = "ES256",
        curve: String = "P-256",
        keyType: String = "EC",
        x: String,
        y: String,
        keyID: String? = nil
    ) {
        self.algorithm = algorithm
        self.curve = curve
        self.keyType = keyType
        self.x = x
        self.y = y
        self.keyID = keyID
    }
}

/// ISO/IEC 18045 resistance levels accepted in OID4VCI key-attestation evidence.
public enum WalletKeyAttestationSecurityLevel: String, Sendable {
    case high = "iso_18045_high"
    case moderate = "iso_18045_moderate"
    case enhancedBasic = "iso_18045_enhanced-basic"
    case basic = "iso_18045_basic"
}

/// Evidence used when an issuer requires OID4VCI key attestation.
public struct WalletKeyAttestationEvidence: Equatable, Sendable {
    /// DER-encoded certificates, leaf first, without the self-signed trust anchor.
    public let certificateChainDER: [Data]
    public let keyStorageLevel: WalletKeyAttestationSecurityLevel
    public let userAuthenticationLevel: WalletKeyAttestationSecurityLevel

    public init(
        certificateChainDER: [Data],
        keyStorageLevel: WalletKeyAttestationSecurityLevel,
        userAuthenticationLevel: WalletKeyAttestationSecurityLevel
    ) {
        self.certificateChainDER = certificateChainDER
        self.keyStorageLevel = keyStorageLevel
        self.userAuthenticationLevel = userAuthenticationLevel
    }
}

/// A caller-owned wallet signing key expressed entirely in native Swift types.
///
/// The key must be ES256 on P-256. `subjectPublicKeyInfo` is the DER-encoded
/// X.509 SubjectPublicKeyInfo for the same key represented by `publicKey`.
/// The SDK reports caller-owned keys to the backend as `SECURITY_LEVEL_CUSTOMER`.
public protocol WalletSigningKey: AnyObject {
    var publicKey: WalletPublicKey { get throws }
    var subjectPublicKeyInfo: Data { get throws }

    /// Signs `message` with ECDSA/SHA-256 and returns an ASN.1 DER signature.
    func sign(_ message: Data) throws -> Data
}

/// Optional capability for signing keys that can supply key-attestation evidence.
public protocol AttestableWalletSigningKey: WalletSigningKey {
    /// Returns `nil` when attestation evidence is currently unavailable.
    var keyAttestationEvidence: WalletKeyAttestationEvidence? { get }
}

/// A caller-owned key used to encrypt the wallet's persisted local data.
///
/// Implementations must use authenticated encryption and include all framing
/// required by `decrypt(_:)` in the returned ciphertext.
public protocol WalletStorageEncryptionKey: AnyObject {
    func encrypt(_ plaintext: Data) throws -> Data
    func decrypt(_ ciphertext: Data) throws -> Data
}

/// Optional capability for storage keys that support cryptographic erasure.
public protocol ResettableWalletStorageEncryptionKey: WalletStorageEncryptionKey {
    func reset() throws
}

public extension WalletFactory {
    /// Creates a wallet with a caller-owned Swift signing key and the default storage engine.
    func getInstance(
        baseUrl: String,
        isLoggingEnabled: Bool = false,
        signingKeyFactory: @escaping () -> any WalletSigningKey
    ) -> Wallet {
        getInstance(
            baseUrl: baseUrl,
            isLoggingEnabled: isLoggingEnabled,
            storageEngine: DeviceBoundAppleStorageEngine(
                accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked
            ),
            signingKeyFactory: signingKeyFactory
        )
    }

    /// Creates a wallet with a caller-owned Swift signing key.
    func getInstance(
        baseUrl: String,
        isLoggingEnabled: Bool = false,
        storageEngine: any StorageEngine,
        signingKeyFactory: @escaping () -> any WalletSigningKey
    ) -> Wallet {
        getInstance(
            baseUrl: baseUrl,
            isLoggingEnabled: isLoggingEnabled,
            storageEngine: storageEngine,
            signingKeyPairFactory: {
                makeKotlinSigningKey(signingKeyFactory())
            }
        )
    }

    /// Creates a wallet with a caller-owned Swift signing key, authorization-code issuance and the
    /// default storage engine.
    func getInstance(
        baseUrl: String,
        clientConfiguration: OID4VCIClientConfiguration,
        isLoggingEnabled: Bool = false,
        signingKeyFactory: @escaping () -> any WalletSigningKey
    ) -> Wallet {
        getInstance(
            baseUrl: baseUrl,
            clientConfiguration: clientConfiguration,
            isLoggingEnabled: isLoggingEnabled,
            storageEngine: DeviceBoundAppleStorageEngine(
                accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked
            ),
            signingKeyFactory: signingKeyFactory
        )
    }

    /// Creates a wallet with a caller-owned Swift signing key and authorization-code issuance.
    func getInstance(
        baseUrl: String,
        clientConfiguration: OID4VCIClientConfiguration,
        isLoggingEnabled: Bool = false,
        storageEngine: any StorageEngine,
        signingKeyFactory: @escaping () -> any WalletSigningKey
    ) -> Wallet {
        getInstance(
            baseUrl: baseUrl,
            clientConfiguration: clientConfiguration,
            isLoggingEnabled: isLoggingEnabled,
            storageEngine: storageEngine,
            signingKeyPairFactory: {
                makeKotlinSigningKey(signingKeyFactory())
            }
        )
    }
}

public extension DeviceBoundAppleStorageEngine {
    /// Creates device-bound storage encrypted by a caller-owned Swift key.
    convenience init(
        accessControlPolicy: KeyPairAccessPolicy,
        storageEncryptionKeyFactory: @escaping () -> any WalletStorageEncryptionKey
    ) {
        self.init(
            accessControlPolicy: accessControlPolicy,
            encryptionKeyFactory: {
                makeKotlinStorageEncryptionKey(storageEncryptionKeyFactory())
            }
        )
    }
}

private class KotlinSigningKeyAdapter: NSObject, KeyPair {
    let signingKey: any WalletSigningKey

    init(_ signingKey: any WalletSigningKey) {
        self.signingKey = signingKey
    }

    func getJwk() throws -> EllipticCurvePublicKey {
        let key = try signingKey.publicKey
        return EllipticCurvePublicKey(
            alg: key.algorithm,
            jwk: OnDeviceKeyPairJwk(
                crv: key.curve,
                kty: key.keyType,
                x: key.x,
                y: key.y,
                keyId: key.keyID
            )
        )
    }

    func getPublicKey() throws -> KotlinByteArray {
        try signingKey.subjectPublicKeyInfo.kotlinByteArray
    }

    func getKeySecurityLevel() throws -> String {
        "SECURITY_LEVEL_CUSTOMER"
    }

    func sign(data: KotlinByteArray) throws -> KotlinByteArray {
        try signingKey.sign(data.swiftData).kotlinByteArray
    }

    /// Caller-supplied signing keys remain caller-managed during wallet teardown.
    func reset() throws {}
}

private final class KotlinAttestableSigningKeyAdapter:
    KotlinSigningKeyAdapter,
    AttestableKeyPair
{
    private let attestableSigningKey: any AttestableWalletSigningKey

    init(_ signingKey: any AttestableWalletSigningKey) {
        attestableSigningKey = signingKey
        super.init(signingKey)
    }

    func getKeyAttestationEvidence() -> KeyAttestationEvidence? {
        guard let evidence = attestableSigningKey.keyAttestationEvidence else {
            return nil
        }

        return KeyAttestationEvidence(
            certificateChainDer: evidence.certificateChainDER.map(\.kotlinByteArray),
            keyStorageLevel: evidence.keyStorageLevel.rawValue,
            userAuthenticationLevel: evidence.userAuthenticationLevel.rawValue
        )
    }
}

private func makeKotlinSigningKey(_ signingKey: any WalletSigningKey) -> any KeyPair {
    if let attestableSigningKey = signingKey as? any AttestableWalletSigningKey {
        return KotlinAttestableSigningKeyAdapter(attestableSigningKey)
    }
    return KotlinSigningKeyAdapter(signingKey)
}

private class KotlinStorageEncryptionKeyAdapter: NSObject, EncryptionKey {
    let encryptionKey: any WalletStorageEncryptionKey

    init(_ encryptionKey: any WalletStorageEncryptionKey) {
        self.encryptionKey = encryptionKey
    }

    func encrypt(data: KotlinByteArray) throws -> KotlinByteArray {
        try encryptionKey.encrypt(data.swiftData).kotlinByteArray
    }

    func decrypt(data: KotlinByteArray) throws -> KotlinByteArray {
        try encryptionKey.decrypt(data.swiftData).kotlinByteArray
    }
}

private final class KotlinResettableStorageEncryptionKeyAdapter:
    KotlinStorageEncryptionKeyAdapter,
    ResettableKey
{
    private let resettableEncryptionKey: any ResettableWalletStorageEncryptionKey

    init(_ encryptionKey: any ResettableWalletStorageEncryptionKey) {
        resettableEncryptionKey = encryptionKey
        super.init(encryptionKey)
    }

    func reset() throws {
        try resettableEncryptionKey.reset()
    }
}

private func makeKotlinStorageEncryptionKey(
    _ encryptionKey: any WalletStorageEncryptionKey
) -> any EncryptionKey {
    if let resettableEncryptionKey =
        encryptionKey as? any ResettableWalletStorageEncryptionKey
    {
        return KotlinResettableStorageEncryptionKeyAdapter(resettableEncryptionKey)
    }
    return KotlinStorageEncryptionKeyAdapter(encryptionKey)
}

private extension Data {
    var kotlinByteArray: KotlinByteArray {
        let result = KotlinByteArray(size: Int32(count))
        for (index, byte) in enumerated() {
            result.set(index: Int32(index), value: Int8(bitPattern: byte))
        }
        return result
    }
}

private extension KotlinByteArray {
    var swiftData: Data {
        Data(toNSData())
    }
}
