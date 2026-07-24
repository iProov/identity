# Bring your own key management

By default, the wallet manages two device-bound keys in secure hardware:

- A signing key used for wallet registration, challenge signing, and OID4VCI/OID4VP proofs.
- A storage-encryption key used to protect the local credential store.

You can supply either or both keys when your organization needs to own key management through its
own secure-element wrapper, keystore, or HSM.

> [!IMPORTANT]
> You are responsible for the security of any key you supply. Prefer hardware-backed keys stored in
> a secure element, the Android Keystore, or the Apple Secure Enclave.

## Public contracts

The key contracts are in `com.iproov.identity.cryptography` and are split by capability:

```kotlin
interface ResettableKey {
    fun reset()
}

interface KeyPair : ResettableKey {
    fun getJwk(): EllipticCurvePublicKey
    fun getPublicKey(): ByteArray
    fun getKeySecurityLevel(): String = "SECURITY_LEVEL_CUSTOMER"
    fun sign(data: ByteArray): ByteArray
}

interface EncryptionKey {
    fun encrypt(data: ByteArray): ByteArray
    fun decrypt(data: ByteArray): ByteArray
}

data class KeyAttestationEvidence(
    val certificateChainDer: List<ByteArray>,
    val keyStorageLevel: String,
    val userAuthenticationLevel: String,
)

interface AttestableKeyPair : KeyPair {
    fun getKeyAttestationEvidence(): KeyAttestationEvidence?
}
```

Those are the Kotlin contracts. Swift applications use the native `WalletSigningKey` and
`WalletStorageEncryptionKey` protocols, whose cryptographic inputs and outputs are Foundation
`Data`. A Swift signing key can additionally implement `AttestableWalletSigningKey`; a Swift
storage key can implement `ResettableWalletStorageEncryptionKey` when SDK-driven deletion is
wanted.

## Signing-key contract

Every key returned by `signingKeyPairFactory` is validated before it reaches wallet registration,
challenge signing, OID4VCI issuance, OID4VP presentation, or DC API presentation. It must meet all
of these requirements:

- `getJwk()` returns `alg = "ES256"`, `kty = "EC"`, and `crv = "P-256"`.
- JWK `x` and `y` are Base64URL values that each decode to exactly 32 bytes.
- `getPublicKey()` returns the same P-256 public key as DER-encoded X.509 SubjectPublicKeyInfo.
- `sign(data)` signs with the matching private key using ECDSA with SHA-256 and returns an
  ASN.1/DER-encoded ECDSA signature. The SDK converts it to raw `R || S` where required.
- The SDK always reports an injected signing key to the backend as `SECURITY_LEVEL_CUSTOMER`.
  A caller-supplied `getKeySecurityLevel()` override is ignored. OID4VCI attestation uses the
  explicit values in `KeyAttestationEvidence`.
- All protocol methods are synchronous. They can call an on-device keystore or secure element but
  cannot wait for a remote HSM.

An incompatible JWK fails immediately with `InvalidSigningKeyException`. Its message identifies
the rejected field and required value.

Factories are lazy and can be called more than once. They must return handles to the same underlying
keys each time; generating a new key on every call breaks registration and proof binding.

### Kotlin implementation

The `companyKeys` methods below represent your keystore or secure-element adapter:

```kotlin
class CompanySigningKey : AttestableKeyPair {
    override fun getJwk() = EllipticCurvePublicKey(
        alg = "ES256",
        jwk = OnDeviceKeyPairJwk(
            crv = "P-256",
            kty = "EC",
            x = companyKeys.xCoordinateBase64Url(),
            y = companyKeys.yCoordinateBase64Url(),
        ),
    )

    override fun getPublicKey(): ByteArray = companyKeys.publicKeySpkiDer()
    override fun sign(data: ByteArray): ByteArray = companyKeys.signEs256Der(data)

    // Injected signing keys are caller-managed.
    override fun reset() = Unit

    override fun getKeyAttestationEvidence(): KeyAttestationEvidence? =
        companyKeys.attestation()?.let { attestation ->
            KeyAttestationEvidence(
                certificateChainDer = attestation.certificateChainDerLeafFirstWithoutRoot,
                keyStorageLevel = attestation.keyStorageIso18045,
                userAuthenticationLevel = attestation.userAuthenticationIso18045,
            )
        }
}
```

Implement `KeyPair` instead when the issuer does not require key attestation.

### Swift implementation

```swift
import Foundation
import identity

final class CompanySigningKey: AttestableWalletSigningKey {
    var publicKey: WalletPublicKey {
        get throws {
            WalletPublicKey(
                x: companyKeys.xCoordinateBase64URL(),
                y: companyKeys.yCoordinateBase64URL()
            )
        }
    }

    var subjectPublicKeyInfo: Data {
        get throws {
            try companyKeys.publicKeySPKIDER()
        }
    }

    func sign(_ message: Data) throws -> Data {
        try companyKeys.signES256DER(message)
    }

    // This capability is non-throwing. Return nil when evidence is unavailable.
    var keyAttestationEvidence: WalletKeyAttestationEvidence? {
        guard let attestation = companyKeys.attestation() else { return nil }
        return WalletKeyAttestationEvidence(
            certificateChainDER: attestation.certificateChainDERLeafFirstWithoutRoot,
            keyStorageLevel: .moderate,
            userAuthenticationLevel: .moderate
        )
    }
}
```

Conform to `WalletSigningKey` instead when attestation is not supported or needed.

## Key attestation

The attestation decision is the same on Android and Apple:

1. When none of the selected credential configurations requires key attestation, the SDK creates
   ordinary JWT proofs and does not request evidence.
2. When attestation is required and the signing key does not implement `AttestableKeyPair` on
   Kotlin or `AttestableWalletSigningKey` on Swift,
   issuance throws `RequiredKeyAttestationUnavailableException`.
3. When the key implements the capability but returns `null` or invalid evidence, issuance throws
   the same exception with the relevant `credentialConfigurationId`.
4. Otherwise, the SDK creates the key-attestation JWT and credential proofs with the same injected
   signing key.

`KeyAttestationEvidence.certificateChainDer` on Kotlin and
`WalletKeyAttestationEvidence.certificateChainDER` on Swift contain the X.509 certificates placed
in the JWT `x5c` header. They must be DER-encoded, ordered leaf first, and omit the self-signed trust
anchor. The leaf certificate must certify the configured public key.

`keyStorageLevel` and `userAuthenticationLevel` must each use one of these ISO 18045 values:

- `iso_18045_high`
- `iso_18045_moderate`
- `iso_18045_enhanced-basic`
- `iso_18045_basic`

The SDK's default Apple Secure Enclave key does not provide an attestation certificate chain. An
Apple wallet targeting an issuer that requires key attestation must therefore inject an
`AttestableWalletSigningKey`.

OID4VCI key attestation is separate from iOS App Attestation.

## Storage-key contract

`EncryptionKey.encrypt(data)` on Kotlin and `WalletStorageEncryptionKey.encrypt(_:)` on Swift return
opaque bytes that the SDK persists unchanged. Decryption must recover the original bytes after an
app restart.

Use authenticated encryption and include everything required for decryption—such as a
format/version marker, nonce or IV, and authentication tag—in the encrypted value unless the key
provider persists it separately. The factory must return a handle to the same underlying key.

A custom storage key owns any authentication UI. The Android biometric retry flow applies only to
the SDK's default storage key.

## Configure the wallet

On Kotlin, pass the signing key through `signingKeyPairFactory` and the storage key through
`encryptionKeyFactory`. On Swift, use `signingKeyFactory` and
`storageEncryptionKeyFactory`. Omitting either uses the SDK's default device-bound key.

### Kotlin

```kotlin
val wallet = WalletFactory.getInstance(
    baseUrl = "https://api.beta.iproov.id",
    signingKeyPairFactory = { signingKey },
    storageEngine = getDeviceBoundStorageEngine(
        accessPolicy = KeyPairAccessPolicy.DeviceUnlocked,
        encryptionKeyFactory = { storageKey },
    ),
)
```

### Swift

```swift
let storageEngine = DeviceBoundAppleStorageEngine(
    accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked,
    storageEncryptionKeyFactory: { storageKey }
)

let wallet = WalletFactory.shared.getInstance(
    baseUrl: "https://api.beta.iproov.id",
    isLoggingEnabled: true,
    storageEngine: storageEngine,
    signingKeyFactory: { signingKey }
)
```

## Lifecycle and errors

The default signing key is SDK-managed and is reset by `wallet.destroy()` and `wallet.delete()`.
Every key returned by an explicitly supplied factory is caller-managed and is never reset by wallet
teardown.

Local wallet data is still deleted if an SDK-managed signing-key reset fails. If both operations
fail, the local-storage failure is thrown with the key-reset failure attached as suppressed.

An injected storage key is reset during `deleteAll()` only when it also implements `ResettableKey`
on Kotlin or `ResettableWalletStorageEncryptionKey` on Swift. Storage-key reset is best-effort.
Without that capability, storage-key deletion and rotation remain entirely caller-managed.

Kotlin implementations should throw `CryptographyException` or a subclass when a key operation
cannot complete. Swift overlay methods can throw any Swift `Error`. The Swift
`keyAttestationEvidence` property is deliberately non-throwing; return `nil` when evidence is
unavailable.
