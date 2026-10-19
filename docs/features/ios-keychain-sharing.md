# iOS: sharing keys and storage with the Identity Document Provider extension

Why the SDK shares two Secure Enclave keys between the app and its extension, what exactly is shared,
and how the migration for existing installs behaves. Written to answer the security review of the
DC API work; see `AppleKeychainSharing` (`AppExtension.kt`), `AppleKeyPair` (`KeyPair.apple.kt`) and
`FileStorage` (`FileStorage.apple.kt.kt`).

## Why sharing exists

Apple's IdentityDocumentServices runs presentment in an **app extension**: a separate process, while
the containing app is not running, with no IPC route back to it. The extension therefore has to be
able to do two things on its own:

1. **Decrypt the credential file** — so it needs the storage encryption key.
2. **Sign the `DeviceResponse` with the mdoc `DeviceKey`** — ISO/IEC 18013-5 mdoc authentication
   requires the signature to come from the key the issuer committed to in the MSO. A different key
   is rejected by every verifier, which is why the extension is forbidden from creating keys
   (`AppleKeyPair.init`).

Both are the same Secure Enclave keys the app already uses. Sharing them is the minimum the
architecture allows; there is no variant that avoids it.

## What is shared — and where it lives

| Mechanism | Nature | Contents |
|---|---|---|
| App Group container (`appGroupIdentifier`) | shared **filesystem** directory | `com.iproov.identity`, the credential store, **ciphertext** under the storage key, plus `com.iproov.identity.owner`, the bundle identifier of the app that owns the container. Never key material. The app sandbox keeps `com.iproov.identity.location`, the group holding the wallet. |
| Keychain access group (`keychainAccessGroup`) | **ACL attribute** on keychain items | the two SDK key items, tagged `com.iproov.identity` (device signing key) and `com.iproov.identity.encryption` (storage key) |

Private key material is never in either place:

- On devices the keys are created with `kSecAttrTokenIDSecureEnclave`. The private key exists only
  inside the Secure Enclave; the keychain item is an SE-wrapped reference usable only by that
  device's SE. Neither the app nor the extension can read the key bytes — they can only ask the SE
  to sign (`SecKeyCreateSignature`) or decrypt (`SecKeyCreateDecryptedData`).
- The access-control policy (`kSecAttrAccessibleWhenUnlockedThisDeviceOnly` plus the configured
  `KeyPairAccessPolicy`) is enforced by the SE on every use, in the extension exactly as in the app.
- The only `SecKeyCopyExternalRepresentation` in the SDK exports the **public** key.
- The software-key fallback (`Location.KEYCHAIN`) is taken only when SE creation fails, i.e. on the
  simulator; even then the key stays keychain-encrypted and non-exported.

Sharing an access group changes **who may use** a key, not where it lives or whether it can be read.

## Who can reach an access group

Only executables signed with the same Team ID whose entitlements list the group. The group name is
Team-ID-prefixed and enforced by provisioning; a third-party app cannot join it. The exposure boundary
therefore widens from "this app" to "this app plus this team's extension that declares the group".

## What is not shared

- the OID4VCI issuance key (`com.iproov.identity.signing`) — issuance happens in the app only
- bring-your-own keys — the consumer owns their sharing (see README)
- the `deviceID` keychain entry — the extension never persists one

`AppleKeychainSharing.sharedKeyTags` is an explicit allow-list of the two tags above; nothing else
can be moved by the SDK.

## Migration for existing installs

Installs that predate sharing hold both keys in the app's private access group and the credential
file in the app sandbox. On upgrade:

| Step | Where | Behaviour |
|---|---|---|
| Move keys | app startup (`getWalletInstance`) and before every DC API registration | `SecItemUpdate` of `kSecAttrAccessGroup` on each SDK key that exists but is not yet in the group. A metadata change — nothing copied, nothing exported. Never creates a key. No-op when sharing is not configured or when running in the extension. |
| Verify | before every DC API registration (`AppleDCApiRegistrar.ensureKeysShared`) | if any SDK key exists and the group is unset, blank, or cannot reach that key, registration throws `DCApiRegistrationException`. Empty synchronization only removes registrations and skips this check. Bring-your-own keys remain the integrator’s responsibility. The app can verify its own access, but cannot verify the extension’s signed entitlements. |
| Move file | first open once the App Group container resolves (`FileStorage.read`) | until the app is entitled, the sandbox file stays in use. Then the file is copied into the container, read back and compared, the group recorded in the sandbox and the owner recorded in the container, and the sandbox copy deleted. A failed step throws `StorageLocationException` and is retried on the next open; a failed read of an existing shared file throws rather than serving anything older. Opening afterwards with a different or unreachable group throws instead of showing an empty wallet. |

Design choices that keep this fail-safe:

- **Tag-based, not instantiation-based.** Instantiating the key factory would mint a key on a fresh
  install and could trigger side effects of a consumer-supplied factory. Moving by tag only relocates
  keys that already exist.
- **Move, never copy.** A key item has exactly one access group; after the update there is one item.
- **Fail closed.** Registration refuses rather than lets the extension discover the problem later.
- **The extension never migrates or creates.** It fails with `KeyPairException` if it cannot see a key,
  and it never claims the container or writes the wallet.
- **One writer.** Engines in a process share one lock and reload when the file has changed under their
  cache. Construct one engine per process.

## Integrator controls

1. Use a dedicated, Team-ID-prefixed access group (e.g. `TEAMID.com.example.wallet.signing`) — not the
   app's default group, and never one shared with unrelated apps.
2. Add the group and a **dedicated** App Group to both the app target and the extension target, and
   nothing else. A container that already holds another app's wallet is refused.
3. Launch the app once after upgrading before relying on the extension (the move and the key
   migration run there).
4. Treat `DCApiRegistrationException` mentioning access groups, and `StorageLocationException`, as
   configuration errors to fix, not to catch and ignore.
5. `digitalCredentialsStatus()` returns `.notConfigured` while the engine has no keychain group: the
   DC API is off by choice, not misconfigured.

## Verifying on a device

1. Install the pre-sharing build; add credentials.
2. Upgrade to the sharing build; open the app; do not perform any API activity. The sandbox file
   moves into the container and the sandbox copy disappears.
3. `digitalCredentialsStatus()` reports `.authorized`; registration succeeds (keys verified).
4. Present from Safari: the extension signs with the original device key and the verifier accepts.
5. Negative: omit the shared group from storage configuration while SDK keys exist — registration
   fails with the access-group message. Clearing all registrations must still succeed.
6. Separately remove the extension's keychain-access-groups entitlement and rebuild — presentation
   fails in the extension. App-side registration cannot detect this entitlement mismatch.

## References

- ISO/IEC 18013-5 — mdoc authentication (`DeviceAuth` signed with the `DeviceKey` in the MSO)
- Apple, *Sharing access to keychain items among a collection of apps*:
  https://developer.apple.com/documentation/security/sharing-access-to-keychain-items-among-a-collection-of-apps
- Apple, IdentityDocumentServices: https://developer.apple.com/documentation/IdentityDocumentServices
