# Errors at the Apple boundary

The SDK uses Kotlin 2.2.21 and exports an Objective-C framework for Swift consumers on iOS 16 and later.

## Follow the existing contracts

- Use `@Throws(Exception::class)` on exported functions and constructors that can propagate ordinary SDK, parsing, storage, or network exceptions. `Wallet`, `RespondableCredentialOffer`, and `OID4VCIClient` use this contract.
- Keep the broader `@Throws(Throwable::class)` contract on the key/storage interfaces and related cryptographic entry points. Some existing crypto and unsupported-operation paths throw `Error` subclasses, which `Exception::class` does not cover. The OID4VP presentation entry points (`RespondablePresentationRequest`, `Query`, `DefaultOID4VPOrchestrator`) reach those paths when signing, so they use it too.
- Put the declaration on an exported interface when its implementations share the contract. The generated framework inherits it on those overrides; `StorageEngine` and `CredentialFactory` are examples.
- Annotate Apple `actual` implementations explicitly. With this toolchain, an annotation on the shared `expect` declaration alone does not establish the exported Apple contract. The symmetric-key constructors and device-key factory are checked in the generated header.
- Private and internal helpers called from Kotlin do not create an Objective-C boundary. Their exceptions must be covered at the exported caller.

Swift callers must use `try` for newly throwing synchronous APIs, including wallet factories and validating constructors. The native Swift key overlay propagates those errors, and the example app handles wallet creation with `Result`.

## Completion callbacks

An annotation on a completion lambda does not give an Objective-C block an NSError channel. The `AppleCallback.kt` helper catches result-conversion failures and resumes the suspended call with the failure. DeviceCheck and OID4VCI callbacks use it. A callback received after cancellation or completion skips conversion.

Flow-based APIs already deliver collection failures through `FlowWrapper.collect`'s `onError` callback. An annotation on the function that starts collection cannot catch a failure raised later in the coroutine.

## Limits of the annotation

This protects exceptions declared by callable APIs; it does not make every operation in the framework safe for arbitrary input. Kotlin/Native does not apply a constructor's annotation to generated data-class `doCopy` methods. Swift callers should use the throwing initializer when replacing validated fields. Property access and raw function-type callbacks also have no throwing contract added by annotating a different function.

The annotation does not catch Objective-C `NSException`, native memory faults, or Kotlin throwable types outside the declared list. See the [Kotlin/Native error interoperability contract](https://kotlinlang.org/docs/native-objc-interop.html#errors-and-exceptions).

## Verification

`identity/libs/identity-ios/consumer-fixture/verify-swift-consumer.sh` compiles the Swift overlay and consumer fixtures against the generated device framework.

With an arm64 iOS simulator booted, run:

```sh
bash identity/libs/identity-ios/consumer-fixture/verify-apple-errors.sh
```

This checks emitted NSError contracts and runs Swift calls that reject malformed credentials, constructor arguments, Apple parser input, and corrupt storage. Every runtime check requires a caught error carrying a Kotlin exception. Removing a required annotation causes a header-check failure, Swift compilation failure, or process termination.

It also runs the iOS example's presentation view model against the real framework with a fake transport.
These checks verify one credential-free decline, a visible notification failure, response guards during sharing,
local closure after a share timeout, and QR-flow rejection of both DC API modes.

The Apple unit tests additionally exercise callback conversion failure, cancellation before callback delivery, and repeated delivery after completion.
