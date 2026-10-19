# Migration Guide: iOS storage requires an App Group (0.5.x → 0.6.0)

Applies to iOS integrators using the SDK's storage engine, `DeviceBoundAppleStorageEngine`. Custom
`StorageEngine` implementations and Android are unchanged.

## What changed

- The storage engine always takes an App Group identifier. Every constructor starts with
  `appGroupIdentifier`, and every constructor can throw.
- The wallet file no longer has two possible homes with nothing recording which one is live. Until the
  app is entitled to the group the file stays in the app sandbox, exactly as in 0.5.x. Once the
  container resolves, the file is moved into it, and the SDK records where it went.
- Misplacement is loud. A lost entitlement, a changed group while the old one still holds data, or a
  container that already holds another app's wallet throws `StorageLocationException` instead of
  opening an empty wallet.
- `keychainAccessGroup` stays optional and is the switch for the Digital Credentials API.

## Migration steps

### 1. Choose a dedicated App Group identifier

Pick a group used by this app and its document-provider extension only, for example
`group.com.example.wallet`. A container that already holds another app's wallet is refused at startup,
so never reuse a group shared with another app. You do not need to add the App Groups capability yet.

### 2. Pass the identifier when creating the wallet

The overloads that built a storage engine for you now take the identifier:

```swift
let wallet = try WalletFactory.shared.getInstance(
    baseUrl: "https://api.beta-eu.iproov.id",
    appGroupIdentifier: "group.com.example.wallet",
    isLoggingEnabled: true
)
```

Or construct the engine yourself:

```swift
let storageEngine = try DeviceBoundAppleStorageEngine(
    appGroupIdentifier: "group.com.example.wallet",
    accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked
)
```

Both can throw, so wallet creation needs `try`. Without the entitlement the wallet runs in the sandbox
as before; nothing else about your app changes.

### 3. Adopting the Digital Credentials API

When you add the document-provider extension, add the App Groups and Keychain Sharing capabilities to
**both** targets, with the same two identifiers, and pass the keychain group to the engine in both:

```swift
let storageEngine = try DeviceBoundAppleStorageEngine(
    appGroupIdentifier: "group.com.example.wallet",
    accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked,
    keychainAccessGroup: "TEAMID.com.example.wallet.signing"
)
```

Declaring the identifiers once per target in Info.plist, with `$(AppIdentifierPrefix)` for the
keychain group, keeps the two targets from drifting apart; the example app's `WalletGroups.swift`
shows the pattern. Launch the app once before relying on the extension: the first open moves the wallet
into the container, and `registerAllCredentialsForDCApi()` on launch keeps the OS registrations in step.

### 4. Build

Every call that stops compiling is one of the removed shapes below. Replace it with the equivalent that
names the group.

## What happens on first launch

| Device state | Result |
|---|---|
| Not entitled to the group | The wallet stays in the sandbox. `isDCApiAvailable()` is false. |
| Entitled, sandbox wallet present | Copied into the container, read back and compared, recorded, then the sandbox copy is deleted. |
| Entitled, no wallet yet | The first write creates the wallet in the container. |
| Keychain group passed, container unavailable | Construction throws `StorageException`. Add the App Groups entitlement. |

## Breaking changes

| Removed | Use instead |
|---|---|
| `DeviceBoundAppleStorageEngine(accessControlPolicy:)` and the other constructors without a group | The same constructors with `appGroupIdentifier` first |
| `WalletFactory.getInstance(baseUrl:)`, `(baseUrl:isLoggingEnabled:)`, and the `clientConfiguration` variants without a storage engine | `getInstance(baseUrl:appGroupIdentifier:…)` |
| Swift `getInstance(baseUrl:…signingKeyFactory:)` overloads that built a default engine | The same overloads with `appGroupIdentifier` |
| `getDeviceBoundStorageEngine(...)` on iOS | Construct `DeviceBoundAppleStorageEngine` directly (the functions remain on Android) |
| `FileStorage(fileName:)` | `FileStorage(fileName:appGroupIdentifier:)` |

New: `DCApiStatus.notConfigured`, returned while the engine has no keychain group;
`StorageLocationException`, a `StorageException` for a misplaced wallet.

`Credential.getVerificationSummary()` is now a suspend function on every platform, because an mDL's
status check goes to the network. Call it from a coroutine in Kotlin and with `try await` in Swift, where
it was previously synchronous. For mDLs the summary now also reports issuer signature, issuer trust,
validity and revocation; see [Credential verification status](credential-status.md).

`ProximityConfig` is split into `ProximityConfig.Holder` and `ProximityConfig.Reader`, and both issuer
trust and reader trust are now set once for the wallet in `TrustConfiguration`, which applies to issuance,
status checks, proximity and the iOS Digital Credentials API. On iOS the extension builds its own wallet,
so pass it the same `TrustConfiguration`. The Android Digital Credentials API is not covered: signed
OpenID4VP requests keep the per-call `trustedVerifierCertificates` of `processDCApiRequest`, and
`org.iso.mdoc` requests carry no reader authentication check:

| Removed | Use instead |
|---|---|
| `ProximityConfig(issuerTrust = …)` | `WalletFactory.getInstance(…, trustConfiguration = TrustConfiguration(issuerTrust = …))` |
| `ProximityConfig(readerTrust = …, trustedReaderCertificates = roots)` | `TrustConfiguration(readerTrust = ReaderTrustPolicy.EnforceIfPresent(roots))` |
| `ProximityConfig(readerTrust = DoNotEnforce, trustedReaderCertificates = roots)` | `TrustConfiguration(readerTrust = ReaderTrustPolicy.DoNotEnforce(roots))`, which still reports trust without blocking |
| `DCApiConfig(…)` passed to `digitalCredentialsRequest` | the same `TrustConfiguration.readerTrust` |
| `ProximityConfig()` | `ProximityConfig.Holder()` to present, `ProximityConfig.Reader()` to retrieve, or omit it in Kotlin |

## Rollback

Downgrading to 0.5.x after the wallet has moved into the container is not supported. 0.5.x reads only
the sandbox and would show an empty wallet. Decide the App Group identifier before shipping 0.6.0 and
keep it.

## Troubleshooting

| Message | Meaning | Remedy |
|---|---|---|
| `App Group container unavailable for '…'. Add the App Groups entitlement…` at construction | A keychain group was passed, so sharing was requested, but the target is not entitled to the App Group | Add the capability to the target, or drop the keychain group until you are ready |
| `Credential storage was moved into App Group '…', which this app is no longer entitled to` | The entitlement was removed after the wallet moved | Restore the entitlement, or call `deleteAll()` to start empty |
| `Credential storage lives in App Group '…' but this engine is configured with '…'` | The identifier changed while the old container still holds the wallet | Keep the original identifier, or call `deleteAll()` to start empty |
| `App Group '…' already holds a wallet owned by '…'` | Another app from your team uses the same group | Use a group dedicated to this app and its extension |
| `digitalCredentialsStatus()` returns `.notConfigured` | The engine has no keychain group, so the Digital Credentials API is off | Pass `keychainAccessGroup` in both targets when you adopt the extension |

Construct one storage engine per process and reuse it. A second engine with a different App Group or
keychain group is refused at construction, so changing either means restarting the app. The extension
reads the shared wallet and never writes it.

## Android and Kotlin Multiplatform

`getDeviceBoundStorageEngine` and the wallet-factory defaults keep working on Android.

The SDK no longer declares an Android backup agent or `com.google.android.backup.api_key` in its manifests. If you
added `tools:remove="android:backupAgent"` or `tools:replace` to work around them, you can drop it. Android Auto Backup
and device-to-device transfer now run for your app, because the agent no longer switches them off. If you use
`EncryptedPreferencesAndroidStorageEngine`, add the README's backup rules. If you have users on 0.5.x, also exclude `<exclude domain="file" path="com.iproov.identity"/>` in both rule files, and keep it after they move to
0.6.0. Opening 0.6.0 moves the wallet file out of new backups, but a backup taken earlier can still hold it, and a copy
restored to another device can't be decrypted there. Add both rules even if you set `allowBackup="false"`: on some
manufacturers' devices it doesn't stop device-to-device transfer for apps targeting Android 12 and above, and only
the `<device-transfer>` section of `dataExtractionRules` applies to that transfer. These unused classes are removed:

| Removed | Use instead |
|---|---|
| `BackedUpStorageEngine` (every call threw) | `getDeviceBoundStorageEngine(...)` |
| `BackedUpKeyValueStorage` (Android backup agent) | Nothing; the wallet is deliberately not backed up |
| `getSyncedKeyValueStorage()` on Android | Nothing; it is unchanged on iOS |
