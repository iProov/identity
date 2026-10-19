# Credential verification status

How the SDK establishes whether a credential is valid, revoked or expired. It covers which issuers the
wallet trusts, how an mDL's status is read from its IETF Token Status List, what each result and error
means, and the limits of the current support. The README holds the quick-start snippets; the standards
are listed under [Standards](#standards).

## At a glance

| | mDL (mdoc) | SD-JWT VC |
|---|---|---|
| Checks | Issuer signature and digests, issuer trust, MSO validity, then the MSO `status` reference | `exp` |
| Status API | `wallet.resolveStatus(credential)`, and the `status_list` result in `credential.getVerificationSummary()`. For an mDL received by the proximity reader, the same two calls on the `ReceivedMDocCredential`: `resolveStatus()` and `getVerificationSummary()` | Not checked yet |
| Network | Only for a credential that passed its own checks and carries a status reference, and not while a cached list is fresh | None |
| Trust configuration | `TrustConfiguration`, passed to `WalletFactory.getInstance` | — |

## Issuer trust

The README's [Trusting credential issuers](../../README.MD#trusting-credential-issuers) explains how to set it
up, step by step. In short:

- `TrustConfiguration.issuerTrust` is the default `IssuerTrustPolicy`. `issuerTrustByType` maps an mdoc `docType`,
  matched exactly, to its own policy, which replaces the default for that type. The `docType` is read from the
  signed MSO, and the proximity reader also requires the document's `docType` to match it.
- `TrustedCertificates(certificates, documentSignerKeyUsage)` holds IACA roots (DER) and the extended key usage the
  Document Signer must carry: mdlDS, `1.0.18013.5.1.2` (ISO/IEC 18013-5 Table B.3), by default, another OID, or
  null for none. An empty `certificates` list trusts nothing.
- `TrustAll`, the default, skips the chain check and is for development only. The mdoc's own signature, digests and
  signing date are still verified, but its summary adds `issuer_trust` `INDETERMINATE` ("Issuer trust is not
  configured") and never concludes `VALID`. Wallet creation logs, at info level, which docTypes aren't checked.
- **`jwksStatusListHosts`** opts in status-list hosts that publish their signing key in a JWKS (see
  [Which key signs the status list](#which-key-signs-the-status-list)). It is empty by default. Entries are host
  names, matched case-insensitively and on any port. The configuration throws when it is created (Swift:
  `try TrustConfiguration(…)`) for a host with a scheme, port or path, an `issuerTrustByType` key that is blank or has
  surrounding spaces, a root certificate that isn't DER X.509 with an EC key, or a `documentSignerKeyUsage` that isn't
  a dotted OID.
- Summaries of stored credentials use the most recently created wallet's configuration, so create one wallet per
  process.
- Debug log lines tagged `[IssuerTrust]` say whether a credential used its `issuerTrustByType` entry or the default.
  Issuer trust is checked against the root certificates before the Document Signer key usage, so a wrong issuer is
  logged as `no matching IACA root found`.

`IssuerTrustPolicy` was previously set per proximity session in `ProximityConfig.issuerTrust`. It is now set once for
the wallet; see [Upgrading to 0.6.0](migration-guide-0.6.0.md#breaking-changes).

## The credential is validated first

Token Status List §8.3 requires the credential itself to be validated before its status is evaluated,
and its status list not to be fetched if that validation fails. For an mDL the SDK checks, in order:

1. **The MSO signature**, made by the Document Signer certificate in `issuerAuth` (its `x5chain`,
   unprotected header first). A missing, empty or unparseable chain is `MALFORMED`.
2. **Every data element's digest** against the MSO.
3. **The MSO's `signedAt`** falls inside the Document Signer certificate's validity (§9.3.1 step 5a),
   under every trust policy.
4. **Under `TrustedCertificates`, the Document Signer chain to one of the IACA roots in the mdoc's
   rule** (see [Issuer trust](#issuer-trust)): the
   same ISO/IEC 18013-5 checks the proximity reader applies (the 457-day limit, the chain and its
   validity now, key usage, and the country match), plus the rule's extended key usage. That is mdlDS
   (Table B.3) unless the rule names another or none.
5. **The MSO validity period** (`validFrom`, `validUntil`), allowing 60 seconds of clock skew.

A failure is reported as `issuer_signature` (`SIGNATURE_INVALID` or `MALFORMED`), `issuer_trust`
(`ISSUER_UNTRUSTED`; "Credential issuer certificate is outside its validity period" when the Document
Signer or its chain has expired, "Credential issuer is not trusted" otherwise), `expiry` (`EXPIRED`) or
`valid_from` (`NOT_YET_VALID`). No status list is fetched.

## Which key signs the status list

Token Status List §11.3 leaves key resolution to each ecosystem and recommends using the same key as the
credential. The SDK follows that recommendation by default: once the mdoc has passed its own checks, its
MSO says which key signs its list.

1. **The `certificate` in the MSO's `status_list`**, when present (ISO/IEC 18013-5 2nd edition). It
   must be inside its validity period and, under `TrustedCertificates`, issued by one of the IACA
   roots in the mdoc's rule; otherwise the result is `invalid` with `step` `signer`.
2. **Otherwise, the Document Signer certificate** that signed the MSO.

The Status List Token's signature must verify with that certificate's key, whatever its header carries.

**Opt-in JWKS hosts.** Some ecosystems sign their lists with a key published, by `kid`, in
`/.well-known/jwks.json` on the list's own host. For a host listed in `jwksStatusListHosts`, the SDK
verifies the list with that key instead. This lookup is an ecosystem convention, not part of the Token
Status List specification, and it trusts the key on the strength of TLS to that host alone, so only list
hosts you have agreed to trust this way.

## Reading the result

`wallet.resolveStatus(credential)` (Swift: `try await wallet.resolveStatus(credential:)`) returns a
`CredentialStatus`, whose cases match the EUDI wallet libraries':

| `CredentialStatus` | List value | In the summary |
|---|---|---|
| `Valid` | `0x00` | `VALID` |
| `Invalid` | `0x01`, revoked | `REVOKED`, "Credential has been revoked" |
| `Suspended` | `0x02`, temporarily invalid | `REVOKED`, "Credential is suspended" |
| `ApplicationSpecific(value)` | `0x03`, `0x0C`–`0x0F` | `INDETERMINATE`, `cause` `unrecognised_value` |
| `Reserved(value)` | any other | `INDETERMINATE`, `cause` `unrecognised_value` |

`wallet.resolveStatusById(credentialId)` does the same for a stored credential's `CredentialMetadata.uuid`.

An mDL the proximity reader received has the same two calls on its `ReceivedMDocCredential`: `resolveStatus()` and
`getVerificationSummary()` (Swift: `try await document.resolveStatus()`). They return what the wallet's calls return for
the same mDL held in the wallet, so one badge serves both. The reader authenticated the document when it arrived (its
signature, digests, signing date and issuer chain, under the wallet's `TrustConfiguration`). These calls check its
validity period again, then fetch the status list, and never during the session. The status is read from the signed
MSO, so a `status` multipaz can't parse still reports `unsupported` or `invalid`, not `no_status`. Under `TrustAll` the
holder can sign its own mDL, choosing the status list and its key: `resolveStatus()` can then return `Valid`, while the
summary concludes `INDETERMINATE`. A `ReceivedMDocCredential` built with its public constructor was never verified: its
summary concludes `INDETERMINATE` and `resolveStatus()` throws `NoStatusReference`. So check a document before copying
it into your own model.

When no status can be established, `resolveStatus` throws a `CredentialStatusException`, and the summary
reports `INDETERMINATE`. Neither ever means valid. `details` (on the exception, or on the summary's
`status_list` result) says why:

| Exception | `details["cause"]` | Reason | Typical next step |
|---|---|---|---|
| `NoStatusReference` | `no_status` | `Credential has no status reference` | None; the issuer publishes no status |
| `InvalidCredential` | `invalid_credential` (`check` names it) | The failed check, see above; `Credential could not be parsed` when it isn't an mdoc | Don't trust the credential |
| `Unsupported` | `unsupported` | `Status mechanism is not supported` (`mechanism`: `identifier_list` or `unknown`), or a non-mdoc credential (`format`) | See [Limits](#limits) |
| `RetrievalFailed` | `network` | `Status list could not be reached` | Retry when online |
| `RetrievalFailed` | `timeout` | `Status list request timed out` | Retry |
| `RetrievalFailed` | `http` | `Status list request failed` (`httpStatus` holds the code) | Report a 4xx; retry a 5xx |
| `VerificationFailed` | `invalid` | `Status list could not be verified` | Don't retry; the list, its signer or its claims are wrong |
| `IndexOutOfBounds` | `out_of_bounds` | `Status index is outside the status list` | Report to the issuer |

Failures also carry `step` (`status_list`, `signer`, `jwks` or `verification`), the request or check
that failed, and `uri`, the status list's address. A `status_list` that is present but malformed,
including an `idx` too large to address, is `invalid`.

In a summary, `concluded` reduces the results: `MALFORMED`, then `SIGNATURE_INVALID`, then `REVOKED`,
then `EXPIRED`. It is `VALID` only when every result is valid (or there are none), and `INDETERMINATE`
otherwise, including for `ISSUER_UNTRUSTED`, `NOT_YET_VALID` and `TrustAll`.

## How the status list is checked

1. The status list URI must be https.
2. The Status List Token is fetched with `Accept: application/statuslist+jwt`.
3. The token must have `typ` `statuslist+jwt`, a `sub` equal to the URI, an `iat` that isn't in the
   future, no `nbf` in the future, an unexpired `exp` (all allowing 60 seconds of clock skew, as the DC
   API does), and a signature that verifies with the key chosen above. No maximum lifetime is imposed,
   because Token Status List §5.1 sets none.
4. `status_list.bits` must be 1, 2, 4 or 8. `lst` is inflated from any valid zlib header (§4.1 only
   recommends the highest compression level) and its checksum verified.
5. An index outside the list makes no statement (§8.3 step 6).

The whole check, both requests included, has 10 seconds. Cancelling the caller cancels it.

A token that carries `ttl` is cached in memory for that long from when it was fetched, never beyond its
`exp`, and then answers for every credential on that list that expects the same signer. Up to 16 lists
are cached for the process, and the oldest is dropped first. A token without `ttl` is fetched every time.

## Trust model

- Trust in an mdoc comes from the IACA roots in the rule for its `docType`; trust in its status list
  comes from the validated MSO. The integrator chooses each type's rule, so a credential can't choose a
  weaker one. Under `TrustAll`, nothing anchors the mdoc to a real issuer, so treat its status as
  informational.
- JWKS lookup, when opted in for a host, rests on TLS to that host.
- A credential's status list index identifies it on the list and is never logged.

## Logging

Logs use the `[StatusList]` tag, with the credential's docType and the status list URI:

- debug: no status reference, each request, the JWKS URL and `kid`, the list's size, whether it was
  cached, and cache hits;
- info: resolved statuses;
- error: failed credential checks, undetermined statuses with the failing step and its exception, and
  HTTP error bodies (truncated).

## Limits

- Status lists served as CWT (`statuslist+cwt`) and ISO/IEC 18013-5 identifier lists are not supported
  yet, and report `unsupported` or `invalid` (#61). The 1st edition of ISO/IEC 18013-5 in
  `docs/standards` leaves revocation out of scope.
- Response and inflated sizes are not yet bounded (#63).
- SD-JWT VC status lists are not checked yet.

## Standards

- IETF Token Status List, [draft-ietf-oauth-status-list-21](https://datatracker.ietf.org/doc/draft-ietf-oauth-status-list/):
  §4.1 compression, §5.1 the JWT Status List Token, §7.1 status types, §8.3 validation rules, §11.3 key
  resolution.
- ISO/IEC 18013-5: §9.3 mdoc issuer authentication, Annex B certificate profiles.
