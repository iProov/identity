// The `identity` library product is backed by this thin wrapper target so that
// linking it also pulls in the iProov Identity binary framework's runtime
// dependencies — the iProov Biometrics SDK and JOSESwift — without consumers
// having to add them manually.
//
// The actual API lives in the binary framework, whose module is `identity`.
// Re-exporting it here means consumers can simply `import identity`.
@_exported import identity
