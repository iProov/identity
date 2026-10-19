import Foundation
import iProovIdentity

// Kotlin exports certificate lists as [KotlinByteArray]; these take DER certificates as Data instead.
// They're disfavoured so an untyped empty literal, such as `certificates: []`, still picks the generated
// initialiser rather than becoming ambiguous.

public extension IssuerTrustPolicy.TrustedCertificates {
    /// Trusts a credential whose Document Signer certificate chains to one of `certificates`, the issuer's
    /// IACA root certificates in DER, and carries the mDL Document Signer key usage (1.0.18013.5.1.2).
    @_disfavoredOverload
    convenience init(certificates: [Data]) {
        self.init(certificates: certificates.map(\.kotlinByteArray))
    }

    /// Like `init(certificates:)`, but the Document Signer certificate must carry `documentSignerKeyUsage`
    /// instead, or no key usage when it is nil.
    @_disfavoredOverload
    convenience init(certificates: [Data], documentSignerKeyUsage: String?) {
        self.init(certificates: certificates.map(\.kotlinByteArray), documentSignerKeyUsage: documentSignerKeyUsage)
    }
}

public extension ReaderTrustPolicy.DoNotEnforce {
    /// Accepts every reader; with `certificates`, the reader CA roots in DER, `readerAuth` still reports which readers chain to them.
    @_disfavoredOverload
    convenience init(certificates: [Data]) {
        self.init(certificates: certificates.map(\.kotlinByteArray))
    }
}

public extension ReaderTrustPolicy.EnforceIfPresent {
    /// Accepts a signed reader whose chain reaches one of `certificates`, the reader CA roots in DER, and an unsigned one.
    @_disfavoredOverload
    convenience init(certificates: [Data]) {
        self.init(certificates: certificates.map(\.kotlinByteArray))
    }
}

public extension ReaderTrustPolicy.AlwaysRequire {
    /// Like `EnforceIfPresent`, but refuses an unsigned reader.
    @_disfavoredOverload
    convenience init(certificates: [Data]) {
        self.init(certificates: certificates.map(\.kotlinByteArray))
    }
}
