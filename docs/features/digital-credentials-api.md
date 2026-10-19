# Digital Credentials API (DC API) on Android and iOS

How a website's `navigator.credentials.get()` call reaches the wallet, what the SDK does with it on each
platform, what an integrating app has to provide, and the limits of the current support. This is the
feature reference; the README holds the quick-start snippets, and the standards the SDK implements are
linked under [References](#references).

## At a glance

| | Android | iOS |
|---|---|---|
| Minimum OS | Android 14, API 34, with Google Play services credential support | iOS 26 |
| Platform API | Credential Manager and the AndroidX credentials registry | IdentityDocumentServices with an Identity Document Provider extension |
| Request protocols | `openid4vp-v1-unsigned`, `openid4vp-v1-signed` | `org-iso-mdoc` (ISO/IEC TS 18013-7 Annex C) |
| Credential formats presented | mdoc and SD-JWT VC through OpenID4VP | mdoc only |
| Who shows the consent UI | The SDK's `CredentialSelectionActivity` | Your extension, using the SDK to match and respond |
| Registration | `registerAllCredentialsForDCApi()` | `registerAllCredentialsForDCApi()`; registrations carry the MSO expiry |
| Availability | `isDCApiAvailable()`: API 34+ | `isDCApiAvailable()`: iOS 26+ and the SDK engine built with a keychain group; `digitalCredentialsStatus()` for the platform's authorization state |
| Storage prerequisites | None beyond the wallet | App Group and keychain access group shared with the extension |

## How a request flows

1. A website calls `navigator.credentials.get()` with a digital-credential request.
2. The platform matches the request against what wallets have registered and shows its picker, or
   launches the one provider that can answer.
3. The platform hands the chosen wallet the raw request together with the **calling origin**. The SDK
   takes the origin from the platform, never from the request body.
4. The SDK validates the envelope and the protocol-specific parameters, then matches the stored
   credentials against the query. Anything invalid is answered with a protocol error before any
   credential is read.
5. The user sees who is asking and what is requested, chooses what to disclose, and authenticates.
6. The SDK signs, encrypts where the request demands it, and returns the response through the platform
   to the website.

Registration is what makes step 2 possible. It is explicit on both platforms and should run on app
start and after any credential is added or deleted; deleting a credential or destroying the wallet
also clears its registration. Where the DC API is unavailable, registration is a no-op, so the same
call is safe on every device.

## Android

### Requirements

- Android 14 or later, with Google Play services that support Credential Manager.
- The SDK ships the OpenID4VP matcher as an asset of its own AAR; nothing is added to the app's assets.

### Manifest

Declare the SDK's selection activity; the credential provider service and its
`credential_provider.xml` come from the SDK's manifest through manifest merging.

```xml
<activity android:name="com.iproov.identity.CredentialSelectionActivity" android:exported="true">
    <intent-filter>
        <action android:name="androidx.identitycredentials.action.GET_CREDENTIALS" />
        <action android:name="androidx.credentials.registry.provider.action.GET_CREDENTIAL" />
        <category android:name="android.intent.category.DEFAULT" />
    </intent-filter>
</activity>
```

### Registration

```kotlin
if (wallet.isDCApiAvailable()) {
    wallet.registerAllCredentialsForDCApi()
}
```

Registration writes two registries, one for mdoc and one for SD-JWT credentials, with the display
properties the system picker shows. It is a set operation: credentials no longer in the wallet are
removed from the registry. `isCredentialRegisteredForDCApi(...)` answers from this instance's last
sync, so call the registration first.

### Request handling

`CredentialSelectionActivity` handles the whole exchange: it receives the platform's intent, parses
the request, validates it, matches credentials, shows the picker for selective disclosure, builds the
VP token and returns the response. No app code runs in that path.

The same pipeline is available to an app that wants its own UI:

```kotlin
when (val result = wallet.processDCApiRequest(requestJson, callingOrigin, trustedVerifierCertificates)) {
    is DCApiMatchResult.Success -> {
        // result.matchResult lists the candidates per credential query; show consent, then:
        val response = wallet.buildDCApiResponse(result, submission)
    }
    is DCApiMatchResult.NoMatch -> { /* nothing in the wallet satisfies the query */ }
    is DCApiMatchResult.InvalidRequest -> { /* result.code and result.message are safe to return */ }
}
```

`trustedVerifierCertificates` holds extra trust anchors for signed requests; the platform trust store
is always consulted. A request that lists several providers is answered with the first one the SDK
supports.

### Errors returned to the website

Protocol errors travel inside a fulfilled response, `{ "error": ... }`, as OpenID4VP Appendix A.4
describes, rather than as a platform exception.

| Situation | Code |
|---|---|
| Malformed request, failed signature or origin check, incomplete disclosure | `invalid_request` |
| `response_type` other than `vp_token` | `unsupported_response_type` |
| Request carries `transaction_data` | `invalid_transaction_data` |
| No matching credential | `access_denied` |
| Internal or signing failure | `server_error` |
| User cancelled | The platform's cancellation exception |

Error messages are fixed strings; wallet-internal exception text never reaches the caller.

## iOS

### Requirements

- iOS 26 or later.
- The `com.apple.developer.identity-document-services.document-provider.mobile-document-types`
  entitlement on both the app and the extension, listing the document types you provide. Apple grants
  it on request and restricts the values.
- An Identity Document Provider extension target, extension point
  `com.apple.identity-document-services.document-provider-ui`.
- An App Group and a keychain access group shared by both targets, so the extension can read the
  credential file and use the SDK's keys. See
  [iOS keychain sharing](ios-keychain-sharing.md) for what is shared and why, and the
  [0.6.0 migration guide](migration-guide-0.6.0.md) for the storage model.

### Project setup

Both targets carry the same three capabilities:

```xml
<key>com.apple.developer.identity-document-services.document-provider.mobile-document-types</key>
<array>
    <string>org.iso.18013.5.1.mDL</string>
    <string>eu.europa.ec.eudi.pid.1</string>
</array>
<key>com.apple.security.application-groups</key>
<array>
    <string>group.com.example.wallet</string>
</array>
<key>keychain-access-groups</key>
<array>
    <string>$(AppIdentifierPrefix)com.example.wallet.signing</string>
</array>
```

Both targets construct the storage engine with the same two identifiers. Passing the keychain group is
what enables the DC API; without it the engine never shares keys and the API reports `.notConfigured`.

```swift
let wallet = try WalletFactory.shared.getInstance(
    baseUrl: "https://api.dev-eu.iproov.id",
    isLoggingEnabled: false,
    storageEngine: DeviceBoundAppleStorageEngine(
        appGroupIdentifier: "group.com.example.wallet",
        accessControlPolicy: KeyPairAccessPolicy.companion.DeviceUnlocked,
        keychainAccessGroup: "TEAMID.com.example.wallet.signing"
    ),
    // readerRoots: [Data], one DER reader CA root each; see "Reader trust" below.
    trustConfiguration: try TrustConfiguration(
        issuerTrust: IssuerTrustPolicy.TrustAll.shared,
        issuerTrustByType: [:],
        jwksStatusListHosts: [],
        readerTrust: ReaderTrustPolicy.EnforceIfPresent(certificates: readerRoots)
    )
)
```

The extension runs in its own process and builds its own `Wallet`, so give it the same
`TrustConfiguration`, with your reader roots, as the app. A wallet built without one is on the default
`EnforceIfPresent` with no roots, which refuses every signed verifier.

Declaring the two identifiers once per target in Info.plist, with `$(AppIdentifierPrefix)` for the
keychain group, keeps the targets in step; `example-ios/Shared/WalletGroups.swift` shows the pattern.
Open the app once after enabling sharing and before relying on the extension: the wallet moves into
the container and the keys into the keychain group on that launch.

### Registration

```swift
try await wallet.registerAllCredentialsForDCApi()
try await wallet.unregisterCredentialFromDCApi(credentialId: id)
```

Only mdoc credentials are registered; others are skipped with a log line. Each registration carries
the document's MSO `validUntil`, so iOS stops offering a credential when it expires. The first
registration triggers the system authorization prompt. Before advertising anything, the SDK moves its
keys into the keychain group and refuses to register if any SDK key is still unreachable there, so a
misconfiguration fails at registration rather than at presentment.

`digitalCredentialsStatus()` returns:

| Value | Meaning |
|---|---|
| `.authorized` | The user has allowed the app as a document provider |
| `.notDetermined` | The user has not been asked yet |
| `.notAuthorized` | The user turned "Allow on websites" off in Settings |
| `.notSupported` | Entitlement missing, or a document type not permitted |
| `.unsupportedOSVersion` | Below iOS 26 |
| `.notConfigured` | The SDK storage engine was built without a keychain group |

The platform reports the user and the entitlement; `.notConfigured` reports the engine.

### Handling a request in the extension

iOS releases the raw request only inside `sendResponse`, after the user has authenticated, so the
extension's sequence is fixed:

```swift
// 1. Authenticate the user, then ask the platform for the request.
try await context.sendResponse { rawRequest in
    // 2. Parse and validate. Everything below is checked here, before any UI.
    let request = try await wallet.digitalCredentialsRequest(
        requestJson: String(data: rawRequest.requestData, encoding: .utf8)!,
        origin: context.requestingWebsiteOrigin!
    )
    // 3. Match: which stored documents satisfy each document request.
    let candidates = try await request.match()
    // 4. Show who is asking (request.readerAuth) and what, collect the user's choice, then:
    return try await request.respond(disclosed: chosen)
}
```

Creating the request validates the envelope, the `EncryptionInfo`, that the reader's key lies on the
P-256 curve, and reader authentication according to `TrustConfiguration.readerTrust`. A request that fails any of these
throws before claim selection. `context.cancel()` declines. `request.readerAuth` carries the reader
authentication result for the consent screen; the example extension's `DocumentProviderExtension.swift`
is a complete implementation.

`ReaderTrustPolicy`, set once per wallet in `TrustConfiguration.readerTrust`, has three forms:
`DoNotEnforce(certificates)`, which accepts every reader but, given roots, still reports in `readerAuth`
whether a signing reader chains to them, for a consent screen that warns rather than blocks;
`EnforceIfPresent(certificates)`, the default, which rejects a signed reader whose chain does not reach its
certificates; and `AlwaysRequire(certificates)`, which also rejects unsigned requests and needs at least one
root. In Swift all three take the certificates as `[Data]`. Production apps supply their reader CA roots, in
the extension's wallet as well as the app's.

## Security model

- **Origin.** The calling origin comes from the platform. For ISO mdoc it is serialised per RFC 6454
  into the session transcript and the verifier identity, and a conflicting origin in the request is
  rejected. For signed OpenID4VP requests it must appear in `expected_origins`; a missing, empty or
  mismatched list returns `invalid_request` before any credential is read. Unsigned requests ignore
  that parameter, as the specification says.
- **Signed requests** (`openid4vp-v1-signed`): `typ` must be `oauth-authz-req+jwt`, `alg` ES256 or
  ES384, the `x5c` chain must reach the platform trust store or a supplied anchor, `client_id` must bind
  to the leaf certificate through `x509_san_dns` or `x509_hash`, the signature must verify, and
  unsupported JOSE critical headers are rejected. Any failure returns `invalid_request`.
- **Required parameters.** `response_type` and `response_mode` are required; `response_mode` must be
  `dc_api` or `dc_api.jwt`; `client_id` is ignored on unsigned requests; `transaction_data` is not
  supported and is rejected.
- **Encrypted responses.** For `dc_api.jwt` the response echoes the recipient key's `kid`, requires an
  explicit supported JWK `alg`, defaults `enc` to A128GCM only when the supported-algorithms parameter
  is absent, rejects a list with no mutual algorithm, and carries only `vp_token` in the JWE. On iOS
  the Annex C response is HPKE-sealed to the reader's key, and the signed session transcript is bound
  to the actual encryption key's JWK thumbprint, including when browser handover information is
  supplied.
- **Disclosure never widens.** The user's selection can narrow the reader's request but never add
  to it; elements the reader did not request are dropped and logged by identifier.
- **Keys and storage.** The device signing key the issuer committed to in the MSO is the only key that
  can sign a valid response, which is why the iOS extension shares the app's keys rather than minting
  its own, and why an extension that cannot see a key fails instead of creating one. The extension
  only ever reads the shared wallet.

## Matching rules

The OpenID4VP path uses DCQL; the ISO path uses the document requests in the request body.

- `meta.doctype_value` matches an mdoc's MSO `docType`; claim paths select the namespace and element
  independently.
- A submission must cover every requested claim when `claim_sets` is absent, or one complete
  permitted option when present. Incomplete selections are rejected before signing.
- `NoMatch` is reported when a required credential query or set cannot be satisfied, including when
  only optional credentials match.
- `trusted_authorities` uses the `{type, values}` wire format. Authority Key Identifier queries match
  certificate AKI bytes in mdoc or SD-JWT chains. This filters candidates; it is not a substitute for
  the verifier's own issuer trust.
- ISO requests include elements whose `intent_to_retain` is false. Empty element requests match on
  document type only and disclose nothing selectively disclosable.

## Limitations

| Platform | Not supported |
|---|---|
| Android | `org-iso-mdoc` requests (Annex C is the iOS path); `openid4vp-v1-multisigned`, so full HAIP 1.0 conformance is not claimed |
| iOS | Anything other than mdoc: SD-JWT VCs cannot be presented, and OpenID4VP over the DC API is not delivered to iOS wallets by Safari |
| Both | `transaction_data`; `meta.doctype_value` is tolerated when absent for compatibility with a 0.5.2 workaround, although OpenID4VP requires it |

## Verifying an integration

1. Issue an mdoc, register, and confirm the platform offers it: the Android picker, or
   `digitalCredentialsStatus()` returning `.authorized` on iOS.
2. Present from a browser to a verifier with a signed request; confirm the verifier accepts the
   device signature.
3. Negative cases: a signed request whose origin is not in `expected_origins` must fail with
   `invalid_request`; on iOS, a reader chain that does not reach your roots must fail at request
   creation under `EnforceIfPresent`.
4. iOS entitlement mismatches between the app and the extension cannot be detected from the app;
   test presentment on a device after any entitlement change. `example-ios` includes a storage probe
   that reports where keys and files live from either process.

## References

- [OpenID for Verifiable Presentations 1.0](https://openid.net/specs/openid-4-verifiable-presentations-1_0-final.html),
  Appendix A for the DC API profile
- [ISO/IEC TS 18013-7](https://www.iso.org/standard/91154.html), Annex C
- [HAIP 1.0](https://openid.net/specs/openid4vc-high-assurance-interoperability-profile-1_0-final.html)
- Apple, IdentityDocumentServices: https://developer.apple.com/documentation/IdentityDocumentServices
- Android, Digital Credentials: https://developer.android.com/identity/digital-credentials
- Related: [iOS keychain sharing](ios-keychain-sharing.md), [0.6.0 migration guide](migration-guide-0.6.0.md)
