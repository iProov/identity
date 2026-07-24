// The public `identity` Swift module wraps the generated `iProovIdentity`
// framework. In addition to the native Swift API in this target, linking it
// pulls in the Kotlin framework and its runtime dependencies — the iProov
// Biometrics SDK and JOSESwift — without consumers adding them manually.
//
// Re-export the generated framework so applications using the native overlay
// continue to need only `import identity`.
@_exported import iProovIdentity
