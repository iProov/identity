# Release notes

## 0.6.0

### Fixed: proximity reader authentication used a COSE algorithm wallets do not accept

- The reader's `ReaderAuth` COSE_Sign1 protected header now carries ES256 (-7) or ES384 (-35),
  the identifiers ISO/IEC 18013-5 requires, instead of the fully-specified ESP256 (-9) /
  ESP384 (-48). Holders that validate the header, including GOV.UK Wallet, rejected every
  signed request as an unsupported algorithm. The signature bytes are unchanged; only the
  label was wrong. No API change.

### Breaking: iOS credential storage requires an App Group

- `DeviceBoundAppleStorageEngine` takes `appGroupIdentifier` as the first parameter of every
  constructor, and every constructor can throw. The engine-less constructors, the iOS
  `getDeviceBoundStorageEngine` functions and the `WalletFactory.getInstance` overloads without a
  storage engine are removed; `getInstance(baseUrl:appGroupIdentifier:…)` variants build the SDK
  engine for you. Custom `StorageEngine` implementations and Android are unchanged.
  See [docs/features/migration-guide-0.6.0.md](features/migration-guide-0.6.0.md).
- Until the app is entitled to the group the wallet stays in the sandbox, as in 0.5.x. Once the
  container resolves, the sandbox file is moved into it: copied, verified, recorded, then deleted.
  No pre-sharing copy is left behind.
- The wallet file and its location markers are excluded from iCloud and device backups. Earlier
  releases passed an unrecognised resource key, so the exclusion never took effect. It is now
  applied on every save and every open, and to the moved file before the sandbox copy is deleted.
  Restoring a backup onto another device therefore yields an empty wallet, rather than a file its
  device-bound key cannot decrypt.
- The SDK records which App Group holds the wallet. A lost entitlement, a different group while the
  old one still holds data, or a container owned by another app throws `StorageLocationException` (a
  `StorageException`) instead of opening an empty wallet. `deleteAll()` clears every location the
  app owns and never touches another app's container. Use an App Group dedicated to the app and its
  extension.
- `keychainAccessGroup` stays optional and is the Digital Credentials API switch. Without it
  `isDCApiAvailable()` is false, `digitalCredentialsStatus()` returns `NOT_CONFIGURED` and
  registration is a no-op. Requesting sharing without the App Group entitlement fails at
  construction.
- Rolling back to 0.5.x after the move is not supported; that version reads the sandbox only.
- Engine instances in one process share a lock and reload when the file on disk has changed under
  their cache, so a second engine on the same wallet can no longer overwrite newer data. Construct
  one engine per process; the extension never writes the shared wallet.

### Credential verification status

- New `TrustConfiguration`, passed to `WalletFactory.getInstance`, says which issuers the wallet
  trusts: `issuerTrust` holds the IACA root certificates (ISO/IEC 18013-5 §9.3) and applies at
  issuance, to status checks and to the proximity reader. Under `TrustedCertificates`, an issued
  mdoc whose Document Signer chain doesn't reach a root is refused (`untrusted_issuer` in the
  issuance summary's errors). The default stays `TrustAll`, for development only.
- `TrustConfiguration.issuerTrustByType` gives a credential type (an mdoc `docType`) its own
  `IssuerTrustPolicy` in place of `issuerTrust`, so mDLs and, for example, photo IDs from another
  issuer can each chain to their own roots. `IssuerTrustPolicy.TrustedCertificates` gains
  `documentSignerKeyUsage`: the extended key usage the Document Signer must carry. It defaults to
  mdlDS (`1.0.18013.5.1.2`), so existing configurations behave as before; pass another OID, or null
  for issuers whose Document Signers carry none. `TrustConfiguration` throws at construction for a
  root that isn't DER X.509, a malformed OID, or a `docType` key with surrounding spaces. In Swift,
  `TrustedCertificates` and `ProximityConfig` also accept certificates as `[Data]`, so integrators
  no longer build `KotlinByteArray`s.
  See [Trusting credential issuers](../README.MD#trusting-credential-issuers).
- Breaking: `ProximityConfig.issuerTrust` is removed; set it once in `TrustConfiguration`. New
  `getInstance` overloads take a `trustConfiguration`, existing `getInstance` signatures are
  unchanged, and the Swift overlay's variants take one with a default. Under `TrustAll`, wallet
  creation logs at info level which docTypes aren't checked, and an mdoc summary never concludes
  `VALID`.
- New `wallet.resolveStatus(credential)` and `resolveStatusById(credentialId)` return an mDL's
  `CredentialStatus` from its IETF Token Status List (draft-ietf-oauth-status-list-21): `Valid`,
  `Invalid`, `Suspended`, `ApplicationSpecific` or `Reserved`, matching the EUDI wallet libraries.
  When no status can be established they throw a `CredentialStatusException` (`NoStatusReference`,
  `InvalidCredential`, `Unsupported`, `RetrievalFailed`, `VerificationFailed` or `IndexOutOfBounds`)
  whose `details["cause"]` says why.
- The example readers show each received mDL's status. Once the session completes, each document
  card runs `getVerificationSummary()` on the `ReceivedMDocCredential` and shows the same badge and
  per-check rows as a held credential, with a button to check again. The sheet's heading is the
  session result rather than "Verified": a document's status isn't known until its card has
  checked it, and one that can't be established shows as an issue, never as valid (#73).
- Breaking: `Credential.getVerificationSummary()` is a suspend function (Swift `try await`). For an
  mDL it reports the issuer signature and digests (`issuer_signature`), issuer trust (
  `issuer_trust`), MSO validity (`expiry`, `valid_from`) and the `status_list` result.
- As Token Status List §8.3 requires, an mDL is validated before its status is checked (its
  signature, digests, signing date, issuer chain and validity, with 60 seconds of clock skew), and
  its status list isn't fetched if that fails. At issuance, an mdoc whose `docType` doesn't match
  the requested configuration is refused. The list must be signed by the certificate the MSO names
  for it, or else by the mDL's Document Signer. Hosts in `TrustConfiguration.jwksStatusListHosts`
  are instead verified with the key their `/.well-known/jwks.json` publishes, an opt-in ecosystem
  convention. Lists with a `ttl` are cached in memory for that long.
  See [docs/features/credential-status.md](features/credential-status.md).
- An expired SD-JWT VC is now reported as `EXPIRED`. The expiry result was previously discarded.

### Proximity: holder and reader configuration

- Breaking: `ProximityConfig` is now sealed, with `ProximityConfig.Holder` for
  `startProximityPresentation` and `ProximityConfig.Reader` for every `startProximityRetrieval`
  overload, so a session's role is fixed by its type. Both keep `engagementTimeout` and
  `sessionInactivityTimeout`. `Holder.bleRoles` is the BLE mode the holder advertises, as before.
  `Reader.bleRoles` is new: the BLE roles the reader may take (`ReaderBLERole.Central`,
  `ReaderBLERole.Peripheral`), defaulting to both with Central preferred, and the session fails with
  a clear message when the holder offers neither. Kotlin callers can omit the config; Swift passes
  `ProximityConfig.Holder()` or `ProximityConfig.Reader()`, or sets the roles and timeouts through
  `init(bleRoles:engagementTimeoutSeconds:sessionInactivityTimeoutSeconds:)`. The `Duration`
  properties reach Swift as their raw `Int64` encoding, not seconds; read `engagementTimeoutSeconds`
  and `sessionInactivityTimeoutSeconds` instead.
- Breaking: reader trust moves to the wallet. `TrustConfiguration.readerTrust` takes a sealed
  `ReaderTrustPolicy` (`DoNotEnforce(certificates)`, `EnforceIfPresent(certificates)`,
  `AlwaysRequire(certificates)`), validated as DER at construction and applied to proximity on both
  platforms and to the iOS Digital Credentials API (ISO/IEC 18013-7 Annex C). `DoNotEnforce` accepts
  every reader and, given roots, still reports in `readerAuth` which readers chain to them;
  `AlwaysRequire` needs at least one root, or the wallet refuses to build. The iOS extension builds
  its own wallet, so it needs the same `TrustConfiguration` as the app. The Android Digital
  Credentials API is not covered: signed OpenID4VP requests keep the per-call
  `trustedVerifierCertificates` of `processDCApiRequest`, and `org.iso.mdoc` requests carry no
  reader authentication check. `ProximityConfig.readerTrust` and `trustedReaderCertificates`,
  `DCApiConfig`, and the `config` parameter of the iOS `digitalCredentialsRequest` are removed. In
  Swift, all three policies accept the certificates as `[Data]`. See [Upgrading to
  0.6.0](features/migration-guide-0.6.0.md#breaking-changes).
- `RespondableProximityRequest.raw` carries the `DeviceRequest` as received, after session
  decryption, as base64url CBOR, and `sessionTranscript` the SessionTranscript it was signed over,
  so integrators can inspect the request or verify reader authentication themselves. `request.raw`
  on the Digital Credentials API is the request JSON, whose transcript follows from it and the
  origin.
- On QR engagement, the reader reduces a BLE carrier that advertises both modes to the one it takes,
  where it previously failed the session with "Only Central Client or Peripheral Server mode is
  supported at one time". NFC engagement already received single-mode carriers from multipaz.
- On iOS NFC engagement, a holder whose carriers include no BLE mode the reader may take now fails
  the session with that message, where the scanning sheet previously kept polling. A holder offering
  only a non-BLE carrier is refused on every engagement path alike, since only BLE carries the
  transfer.

### Credential presentation

- DCQL `meta.doctype_value` now matches an mdoc's MSO `docType`. Claim paths continue to select the
  namespace and element independently. Verifiers that incorrectly supplied a namespace as the
  doctype must correct their queries.
- Malformed mdoc claim paths, empty `claims` arrays, and `claim_sets` without `claims` are rejected.
  Redirect presentation requests report these through `OID4VPError.InvalidAuthorizationRequest`.
- DC API matching reports `NoMatch` when required credential queries or sets cannot be satisfied,
  including when only optional credentials match.
- Submission validation checks the selected credential, including a reloaded copy, rather than the
  first candidate. The Android picker reuses the matched credential and its matching claims.
- Submissions must include all requested claims when `claim_sets` is absent, or cover a complete
  permitted option when it is present. A narrower or alternative option is accepted when the
  selected credential satisfies every disclosed claim, including value constraints. Incomplete
  selections are rejected before signing: DC API returns `INVALID_REQUEST`, and redirect
  presentation returns `PresentationOutcome.Declined`. Requests with no selectively disclosable
  claims still allow empty selections.
- ISO mdoc DC API requests include elements whose `intent_to_retain` is false. Empty or absent
  element requests retain doctype-only matching and disclose no selectively disclosable elements.
- `trusted_authorities` uses the OpenID4VP `{type, values}` wire format. AKI queries match
  certificate Authority Key Identifier bytes in either mdoc or SD-JWT certificate chains; unknown
  types and missing identifiers do not match. This filters candidates and does not replace the
  verifier's issuer-trust checks. Programmatic callers should use
  `CredentialQuery.trustedAuthorityQueries`; the old issuer-name `trustedAuthorities` property is
  deprecated and no longer serialized.
- Empty ISO `docRequests` lists are rejected at session creation. Responses with no disclosed issuer
  items omit the optional `issuerSigned.nameSpaces` field.
- `RespondablePresentationRequest.decline()` sends the verifier an `access_denied` error with the
  request's `state` (`direct_post` and `direct_post.jwt`). For `direct_post.jwt` the error is
  encrypted to the verifier's key when one is usable. Explicit content-encryption lists are
  respected; an incompatible list uses the plain error fallback. It returns the verifier's
  `redirectUri` and throws if the verifier can't be told within 30 seconds; a `dc_api` request
  throws `OID4VPError.UnsupportedResponseMode`. A new initializer takes `onDecline`; the existing
  one is kept.
- Both example apps' sharing modals now use **Decline**, wait for the notification, and follow the
  verifier's returned redirect without reporting credentials shared. Duplicate responses and
  implicit dismissal are blocked while responding. Failures allow the user to close locally without
  claiming verifier receipt. Compose's `PresentationRequestSheetProvider` has a new `onDeclined`
  callback for the result; the existing three-argument overload is kept.
- Sharing now gives the verifier 30 seconds to answer once the response is sent; user authentication
  beforehand doesn't count. `respond()` throws `ApiException.TimeoutError` when that deadline or the
  HTTP client's own timeout expires, instead of returning `PresentationOutcome.Declined`. On timeout
  both apps allow local **Close** and prevent another response on that request, since verifier
  receipt is uncertain.
- `RespondablePresentationRequest.respond()`/`decline()`, `Query.execute()` and the public
  `DefaultOID4VPOrchestrator` functions are annotated `@Throws(Throwable::class)`, so any Kotlin
  error reaches Swift as an `NSError` instead of terminating the app. Java callers of the
  non-suspend functions now see `throws Throwable`.
- Both examples' QR/deep-link flows reject DC API response modes with an unsupported-request
  message. DC API requests continue through the browser/OS credential-provider flow.
- `direct_post` and `direct_post.jwt` requests that also carry `redirect_uri` are rejected with
  `OID4VPError.InvalidAuthorizationRequest`, as OID4VP §8.2 requires.
  `PresentationOutcome.Success.redirectUri` now comes only from the verifier's response; the SDK no
  longer falls back to the request's `redirect_uri`.

### DC API security and errors

- ISO mdoc session transcripts and verifier identity use the platform-supplied calling origin. A
  conflicting origin in the request is rejected. Calling origin and nonce must be non-blank.
- Encrypted mdoc DC API responses bind the signed session transcript to the actual response
  encryption key's JWK thumbprint, including when browser handover information is supplied.
- ISO mdoc reader authentication covers the DeviceRequest 1.1 request-level `readerAuthAll` as well
  as per-document `readerAuth`. Each signature's chain must reach the roots in
  `TrustConfiguration.readerTrust` with the reader-authentication EKU, and every signature present
  must be trusted. Under the default `EnforceIfPresent`, a request signed only by an untrusted
  `readerAuthAll` is now rejected rather than treated as unsigned. Applies to the iOS Digital
  Credentials API and proximity alike.
- Signed OpenID4VP DC API requests require the platform origin to appear in `expected_origins`;
  missing, empty, or mismatched values return `INVALID_REQUEST` before credential access. Unsigned
  requests ignore this parameter.
- Signed OpenID4VP DC API requests (`openid4vp-v1-signed`) are verified: `typ` must be
  `oauth-authz-req+jwt`, `alg` must be ES256 or ES384, the `x5c` chain must reach the platform trust
  store or an anchor passed as `trustedVerifierCertificates` to `Wallet.processDCApiRequest`,
  `client_id` must bind to the leaf certificate (`x509_san_dns` or `x509_hash`), the leaf's KeyUsage
  must include `digitalSignature` when the extension is present, the signature must verify, and
  unsupported JOSE critical headers are rejected. When the Request Object carries `exp` or `nbf`,
  they must be numeric dates and are enforced with a 60-second clock-skew allowance (RFC 7519). Any
  failure returns `INVALID_REQUEST`.
- `response_type` and `response_mode` are required on incoming requests; `response_mode` must be
  `dc_api` or `dc_api.jwt`; `response_type` other than `vp_token` returns
  `unsupported_response_type`; requests carrying `transaction_data` are rejected with
  `invalid_transaction_data`; `client_id` is ignored on unsigned requests. Other parameters not
  defined for the DC API (OpenID4VP Appendix A.2) are dropped before decoding, so a value of an
  unexpected type, such as an object `state`, no longer rejects an otherwise valid request.
- Android returns OpenID4VP protocol errors inside the fulfilled DC API response (
  `{ "error": ... }`, Appendix A.4) instead of a platform exception; internal and signing failures
  map to `server_error`, no matching credential to `access_denied`, and user cancellation to the
  platform cancellation exception.
- Encrypted (`dc_api.jwt`) responses echo the recipient key's `kid`, require an explicit supported
  JWK `alg`, default `enc` to A128GCM only when the supported-algorithms parameter is absent, reject
  an explicit list with no mutual algorithm, and carry only `vp_token` in the JWE payload.
- A caller's disclosure selection can narrow the reader's request but never widen it; elements the
  reader did not request are dropped and logged by identifier. Applies to proximity and the DC API
  alike.
- Storage and signing failures return fixed messages instead of wallet-internal exception text.
  Registration failures are contained at the wallet's DC API request boundary.
- User cancellation of key authentication maps to `user_cancelled` during matching and
  `UserDeclined` during response building. Android returns a credential cancellation exception.
  Coroutine cancellation continues to propagate.
- For compatibility, `DCApiMatchResult.InvalidRequest` remains the existing failure container.
  Inspect its `code` to distinguish invalid input, internal failure, and user cancellation.

`meta.doctype_value` is still optional in the SDK for compatibility with the temporary workaround
for 0.5.2. OpenID4VP requires it in verifier queries. A release containing the matching fix should
be adopted before that leniency is removed.

### Digital Credentials API: iOS and registration

- iOS 26 support for ISO/IEC 18013-7 Annex C presentation through an Identity Document Provider
  extension: credentials are registered with `IdentityDocumentServices` (expiry taken from the MSO
  `validUntil`), the extension parses and answers requests with
  `RespondableDigitalCredentialsRequest`, and wallet-level `TrustConfiguration.readerTrust` controls
  reader trust. The session validates the envelope, EncryptionInfo and reader key on the P-256 curve,
  and applies the configured reader-authentication policy before claim-selection UI and signing.
  Apple's initial user authorization must happen first because the platform only releases the raw
  request inside `sendResponse`.
- The app and extension share storage through an App Group container and a keychain access group (
  `DeviceBoundAppleStorageEngine`). A missing shared access group is rejected when SDK-owned keys
  exist; unregistering all documents does not need key sharing. Existing keys are moved and the
  credential file is moved into the shared location on first launch (the sandbox copy is deleted
  after verification), an unreadable pre-sharing file surfaces as an error instead of an empty
  wallet, deletion removes every owned copy, and DC API registration refuses to advertise documents
  whose keys the extension could not reach.
  See [iOS keychain sharing](features/ios-keychain-sharing.md) and the README section "Digital
  Credentials API (iOS)".
- `delete()` and `destroy()` clear the wallet's DC API registrations before wiping it. Without the
  document-provider entitlement, or before the user allows the app, iOS refuses the registration
  store and there is nothing to clear, so both complete instead of throwing after the wipe.
- The Swift bridge deploys to iOS 16.0 with HPKE (iOS 17+) guarded, so the framework loads on iOS
  16; serialized origins bracket IPv6 hosts.
- Android registry failures and cancellation propagate to callers; tracking updates only after
  successful writes. Context-only registrars can remove credentials after their first successful
  synchronization. Android `unregisterCredential` rewrites the Credential Manager registry without
  the removed credential; both registries are always written, so an emptied wallet stops matching.
- `isDCApiAvailable()` and `isCredentialRegisteredForDCApi(...)` keep their synchronous signatures.
  On iOS the former requires OS support (26+) and configured storage/key sharing; authorization is
  reported separately by `digitalCredentialsStatus()`. The latter reflects registrations made
  through this wallet instance.
- Kept for 0.5.2 callers and deprecated in 0.6.0:
  `Wallet.registerCredentialForDCApi(metadata)` (iOS registers that one credential, Android logs and
  returns, as in 0.5.2), `DCApiOrchestrator.registerCredential(metadata)`,
  `DCApiRegistrar.registerCredential(metadata)`, `OpenID4VPResponse`, and
  `DeviceResponse.buildForDCApi` / `buildForProximity` (renamed `buildForOpenID4VPDCApi` /
  `buildWithSessionTranscript`). `DCApiResponse.forOpenID4VP` / `forOpenID4VPJWT` accept their 0.5.2
  arguments; `state` is ignored because it is not defined over the DC API.
- **Removed:** `createPlatformDCApiRegistrar()`, which was public by omission in 0.5.2. It is
  internal plumbing; use the `Wallet` registration methods.

HAIP 1.0 §5.2 multi-signed OpenID4VP requests remain unsupported; these changes do not establish
full HAIP conformance.

### Swift error propagation

- Added missing `@Throws` declarations to exported presentation, matching, parsing, storage,
  networking, factory, and validating-constructor APIs, including Apple `actual` implementations.
  Ordinary Kotlin failures on these paths can now reach Swift as errors.
- **Swift source change:** newly throwing synchronous calls, including `WalletFactory.getInstance`,
  require `try` and error handling. The Swift key overlay and example callers are updated.
- Apple OID4VCI and DeviceCheck completion callbacks now deliver conversion failures through the
  suspended operation, and skip late callbacks after cancellation/completion.
- See [Apple error handling](apple-error-handling.md) for the declaration conventions, verification
  commands, and limits for properties, callbacks, and generated data-class copies.

### Proximity: BLE link loss no longer crashes the app

- multipaz is updated from 0.99.0 to 0.100.0. When the other device dropped BLE mid-session (the app
  was killed or Bluetooth was turned off), the BLE central (the reader by default, or a holder
  configured with `ProximityBLERole.CentralClient`) crashed on Android with an uncatchable
  `java.lang.Error: Peripheral unexpectedly disconnected` thrown from a Bluetooth callback. The
  session now ends with `ProximityRetrievalEvent.Error` or `ProximityPresentationEvent.Failure`, and
  the transport is closed. While waiting for a message, the error reads
  `Failed while waiting for message`. A holder acting as the GATT peripheral (the default) still
  doesn't see the drop. It ends with `Session timed out` after `sessionInactivityTimeout`, as
  before.
- A malformed BLE data chunk from the other device also crashed the app on Android and iOS. It now
  fails the session the same way.
- A failed `DeviceResponse` signature or digest check no longer reports
  `Error verifying document N in DeviceResponse`. `ProximityRetrievalEvent.Error.message` now
  carries the underlying failure.
- On Android, a failing BLE L2CAP connection is now retried for up to about a minute, so the session
  ends with `Session timed out` when `ProximityConfig.engagementTimeout` expires, rather than
  failing straight away.

### Documents: reading the chip through the iProov NFC service

- New `addDocumentWithMrz(…, nfcServiceRead)` and `addDocumentWithFields(…, nfcServiceRead)`
  overloads opt in to having the iProov NFC service read the chip, through the iProov NFC reader
  SDK. The app then uploads no data groups, SOD or AA signature: the platform fetches the read
  itself. The platform team enables the mode per app.
- When the mode is on, the returned `DocumentChallenge` carries `nfcServiceReadToken`: pass it
  unchanged to the reader SDK, then pass the read's completion code to
  `DocumentChallengeResponder.withNfcServiceRead(completionCode)`. A null token means read the chip
  on the device, as before.
- If `init/doc` answers 456 (mode not set up for this app) or 422 (a server from before the mode),
  the SDK falls back to an on-device read with a fresh secret, so opting in never breaks adding a
  document. The platform's other errors arrive as `ApiException.HttpError`; see
  [Reading the chip through the iProov NFC service](../README.MD#reading-the-chip-through-the-iproov-nfc-service)
  for what each status means.
- Additive: existing signatures and Objective-C selectors are unchanged.

### Logging

- With `isLoggingEnabled` on, debug logs no longer contain End-User data. That covers the `vp_token`
  and DeviceResponse, presentation submissions, credential offers (which include pre-authorized
  codes), identity-platform request and response bodies (which include MRTD data groups), request
  headers, and the iOS issuance access token and issued credentials. They now log the request path,
  the HTTP status and the offer versions instead. Session-transcript and handover hex, which carry
  no holder data, are still logged for interoperability debugging.
- With `isLoggingEnabled` off, the SDK no longer prints stack traces or JWK thumbprint details, and
  the iOS JWE helper no longer writes to the unified log. A credential that fails to load is now
  logged by exception type only, without the stored record.

### multipaz output follows the logging flag

- With `isLoggingEnabled` off, multipaz's own debug and info output, for example from every
  proximity BLE session, no longer reaches Logcat or the console. It printed in every build because
  multipaz enables debug logging by default. Its warnings and errors are still printed. With logging
  on, multipaz logs as before.

### iOS issuance signing errors keep their message

- When proof or key-attestation signing failed during iOS issuance, for example when the user
  cancelled Face ID, the reason was lost. The error showed a generic "The operation couldn't be
  completed". The bridge stored the message under the literal key `"NSLocalizedDescriptionKey"`, but
  the constant's value is `"NSLocalizedDescription"`. It now uses the constant, so the reason
  reaches `OID4VCIException`.

### Logging

- The SDK's HTTP client now logs only when `isLoggingEnabled` is true. When it does, it logs each request's method, URL and response status, but no headers or bodies. The one exception: a response that fails to parse is logged with its parse error, which can quote part of the body. Previously it logged every request's URL and request and response headers whatever the flag said: to Logcat on Android, to stdout on iOS. Those headers included `x-instance-id` and, on iOS, `x-ios-assertion`.

### Android: minified release builds

- Host apps with `minifyEnabled true` failed in R8 with five missing `io.ktor` classes. The iProov KMP dependency brought in Ktor 2's OkHttp engine, which can't work against the Ktor 3 the SDK uses. The SDK now excludes that engine, and its own HTTP client uses the Ktor Android engine explicitly. No consumer ProGuard rules are needed: the libraries that need rules ship their own.

### No third-party request at registration

- The SDK no longer fetches claim display names from `https://cache.svipe.net/translations-en.json`. Previously it fetched them at registration, and on legacy login requests until a fetch succeeded. Each fetch sent the wallet's `x-instance-id`, session id and user agent to that host. If the host was unreachable, `register()` failed after the wallet was already registered. The same 65 English names are now built into the SDK, so `Claim.displayName` and `IdentityPlatformInterface.getTranslations()` return the same values as before. Wallets whose registration failed on that fetch now get the labels too.

### identity-components: no debug output

- `identity-components` no longer prints progress or debug output: about 60 `println`, `Log.i` and `printStackTrace` calls, mostly in the Android NFC and MRZ readers. It has no logging flag, so they printed in every build. Warnings and errors on real failures stay, and carry no MRZ, data-group or claim values. The NFC read-error warning logs only the exception type, because jmrtd's message can quote a malformed date of birth.

### Android: wallet file excluded from backups

- The default Android storage engine now keeps its wallet file in `noBackupFilesDir`, which Android never includes in cloud backups or device-to-device transfers. The file is encrypted with a Keystore key that never leaves the device, so a restored or transferred copy could never be decrypted. An existing file in `filesDir` is moved there the first time it is used; if the move fails, the old file keeps being used. `deleteAll()` also removes any copy left in `filesDir`. A backup made by an earlier release, or a device-to-device transfer from a phone still on one, can still carry the old file. It is moved like any other, and it can't be decrypted on the new device.
- Wallet writes are now atomic. Each write goes to a temp file beside the wallet, is synced to disk, then renamed over the wallet, one write at a time within the app's process. A crash or kill mid-write, or two writes at once, can no longer leave a truncated, undecryptable wallet. Two concurrent writes can still lose one of their updates. `deleteAll()` also removes a temp file left by an interrupted write.
- Hosts no longer need backup rules for the default engine. The README's rules applied only to `EncryptedPreferencesAndroidStorageEngine`'s preferences file, and now say so.

### iOS privacy manifest

- `iProovIdentity.framework` now ships a `PrivacyInfo.xcprivacy` in each slice of the XCFramework, for both SwiftPM and CocoaPods.
- It declares the two required-reason APIs the framework uses: file timestamps (`C617.1`), used to detect wallet-file changes, and user defaults (`CA92.1`), used by the embedded iProov KMP layer.
- It also declares the data the SDK collects: a device ID and sensitive information, meaning the document's biometric face image (DG2) that is uploaded with the identity document. Both are linked to the user, used for app functionality, and not used for tracking.
- Face biometrics stay declared by `iProov.framework`'s own manifest.
- Apps without their own declarations for these were rejected on upload with ITMS-91053.

### iProov Biometrics SDK versions

- The README now states the iProov Biometrics (Face) SDK versions the Identity SDK is built and tested against: Android 11.1.x (11.1.1, resolved transitively) and iOS 13.x from 13.1.0. The Identity SDK doesn't embed the Face SDK. The Android install snippet pins `11.1.1` instead of `<latest-version>`. The podspec now requires `iProov ~> 13.1`, matching SwiftPM's `from: "13.1.0"`; before, it accepted any version. That includes iProov 14.0.0, published on 15 Oct 2026, which this SDK isn't built against. Until 0.6.0, CocoaPods users of 0.5.2 should add `pod 'iProov', '~> 13.1'` to their Podfile.

### iOS face flows keep the typed error

- On iOS, errors delivered to `FlowWrapper.collect`'s `onError` now carry the Kotlin exception, as the async APIs' errors already did. This covers `addFaceVerification`, `addDocumentWithReference`, `FaceReverificationRequest.verify` and the proximity session `events`. `(error as NSError).kotlinException as? ApiException.HttpError` gives the `statusCode`, `errorCode` and `recoveryMessage` of a failed identity-platform call. The error's domain, code and `localizedDescription` are unchanged.

### Android: no backup agent forced onto host apps

- The SDK's manifest no longer declares `android:backupAgent` (`BackedUpKeyValueStorage`) or the `com.google.android.backup.api_key` meta-data. Both were merged into every host app.
- The agent had no zero-argument constructor, so it crashed the app whenever Android bound it, for example during a device-to-device transfer on Android 12+ (Samsung Smart Switch included), which `allowBackup="false"` doesn't prevent on some manufacturers' devices for apps targeting API 31+.
- For hosts that allow backup without `fullBackupOnly`, the agent also switched them to key/value backup, silently turning off Auto Backup for their own data. Auto Backup and D2D now run for host apps again. Hosts using `EncryptedPreferencesAndroidStorageEngine` should add the README's backup rules. Hosts with 0.5.x users should exclude `file/com.iproov.identity` and keep the rule, because backups taken before 0.6.0 can still hold that file; see the migration guide.
- A host declaring its own backup agent no longer needs `tools:replace`.
- **Removed** (all unused): `BackedUpStorageEngine`, whose every call threw; `BackedUpKeyValueStorage`; and Android's `getSyncedKeyValueStorage()`. It is unchanged on iOS. See the [0.6.0 migration guide](features/migration-guide-0.6.0.md#android-and-kotlin-multiplatform).

### iOS device ID stays on the device

- On iOS, the keychain item holding the device ID (the source of `x-instance-id`) is now `kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly`. It is never restored onto a different device, whether from that device's backup or through device migration. Previously a phone restored from another device's backup kept the old instance ID while its wallet, excluded from backups, started empty. A backup restored onto the same device still restores the ID, as Apple does for ThisDeviceOnly items.
- On the app's first launch with this release, the existing ID is moved to the new accessibility class with its value unchanged. The App Extension doesn't write it.
- The public `Keychain.set` now stores every item with that accessibility, updating an existing item in place rather than deleting and re-adding it.

### Identity-platform HTTP errors

- `ApiException.HttpError` has a new read-only `retryAfter` property. It holds the response's `Retry-After` header exactly as sent, which is either a number of seconds or an HTTP-date. Use it with `statusCode` (for example 429) and `errorCode` to decide when to retry.
- An error response whose body isn't a JSON object, such as a plain-text or empty 429 from a gateway, now surfaces as `HttpError` with its status. The first 200 characters of the body text become the `message`. Previously it surfaced as a JSON parsing exception with no status.
- The same applies to JSON fields that aren't plain values, such as an `error` object. Constructors and `copy` are unchanged.
- Two side effects follow from keeping the status:
  - A verifier's `request_uri` that answers with a non-JSON error now surfaces as `HttpError` rather than `OID4VPError.InvalidAuthorizationRequest`, as a JSON error already did.
  - A non-JSON 404 at registration now surfaces as `AppIdNotSupportedException`, as a JSON 404 already did. Check `baseUrl` before contacting support.

### Android 8–11: wallet storage works

- On Android 8–11 (API 26–30) the default storage engine couldn't read back anything it had written. Every operation after the first write failed with `Decryption failed: no such algorithm: ECDH for provider AndroidKeyStore`, so the wallet was unusable. Its ECIES scheme needs ECDH inside the AndroidKeyStore to decrypt, which only exists from API 31.
- Below API 31 the engine now uses an AES-256-GCM key held in the AndroidKeyStore. The access policy and `setUnlockedDeviceRequired` apply to it as before. Once that key exists it stays in use after an OS upgrade to Android 12 or later, so the data stays readable. Installs that start on API 31+ keep the existing key, so nothing changes for them. API 26 remains the minimum.
- Data written on API 26–30 by earlier releases could never be decrypted there. The SDK now discards it and logs once, so the wallet starts empty and the app registers again. No app code is needed. Any other read failure still throws, so an authentication failure can never wipe a readable wallet.
- `deleteAll()` also removes the unusable EC key an earlier release left behind, so a later write on Android 12+ can't reuse it. A device that moved to Android 12+ while still on an earlier release has that key too, and it can never decrypt there either: the SDK discards that data once in the same way and continues with the AES key.
- With an access policy that requires authentication, the AES key also needs it to encrypt, so writes now prompt when needed, as reads already did.

### Android: storage protected by user authentication

- With `UserPresent`, `AnyBiometrics` or `CurrentBiometrics`, storage built the documented way (`getDeviceBoundStorageEngine(policy)`, which holds the Application context) couldn't prompt. Once the validity window lapsed, every read threw `IllegalStateException`. The SDK now shows the prompt on whichever Activity is in the foreground, which it tracks itself. This also covers an engine built with an Activity that has since been recreated. For an engine holding the Application context with no Activity in the foreground, it throws `KeyPairAuthenticationError`. Storage calls that need authentication at the same time now share one prompt. Before, each showed its own, and the second cancelled the first, so that call failed with `KeyPairAuthenticationError` ("Fingerprint operation canceled").
- On API 30+, enrolling a new biometric under `CurrentBiometrics`, or removing the screen lock under any gated policy, permanently invalidates the storage key. Reads used to prompt for nothing and fail again. They now throw `KeyPermanentlyInvalidatedException` straight away; call `deleteAll()` and register again.
- A policy that requires authentication now needs an `authenticationValidityDuration` above 0 for storage. With 0, a prompt could never unlock the key, so storage now fails with an `IllegalArgumentException` that says so. After changing to a duration above 0, call `deleteAll()` once, because the existing key keeps the parameters it was created with.

### Face capture feedback codes

- `VerificationEvent.Error` has a new read-only `feedbackCodes` property: the iProov feedback codes behind a failed face capture, such as `ambiguous_outcome`. Branch on these rather than on the message, which is localized text. `message` is unchanged.
- When the iProov SDK reports an error with no message, `message` is now the error's title, for example the camera-permission or unsupported-device title. Previously it was a fixed "Verification failed.". Constructors and `copy` are unchanged.
- On iOS, a face capture started after an earlier one in the same app session no longer begins with that earlier capture's result. The iProov layer kept the last result between sessions, so the new capture could report the old failure, cancellation or success. Android already started clean.
- The event flows from `addFaceVerification`, `addDocumentWithReference` and `FaceReverificationRequest.verify` now complete after their final event. Before, they kept listening, so a later face capture in the same process also reached an earlier flow that was still being collected. On the new capture's success, that flow called the platform with its own, already-used token. Collectors that stop after a final event see no difference.
- Starting a face capture while another is still on screen, for example from a double tap, now cancels the earlier one and waits up to 5 seconds for it to end and its screen to close before launching. On iOS, relaunching straight away failed with `captureAlreadyActive`, or tried to present onto the closing screen, so no capture appeared.

### iOS: App Attest assertion after relaunch

- After an app relaunch, signed identity-platform requests now carry the `x-ios-assertion` App Attest header again. The SDK kept the App Attest key id only in memory and set it only during registration, so from the next launch on, every signed request went without an assertion. A registered wallet now restores the key id from storage before its first signed request. `initDocReference` and `refreshClaims` now also carry the assertion; they never did, even in the session that registered.
- If the stored key no longer works on the device, for example a custom storage engine restored onto a new phone, the signed request fails with an `AttestationException` instead of going out without an assertion. Call `delete()` and register again. `delete()` still wipes the wallet locally when the server revoke can't be signed. Calls made directly on `wallet.identityPlatformInterface` only carry the restored key after a `Wallet` method has run in the process.
