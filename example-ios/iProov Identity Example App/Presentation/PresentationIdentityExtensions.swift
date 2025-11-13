import Foundation
import identity

extension RespondablePresentationRequest: Identifiable {}

extension CredentialQuery: Identifiable {}



extension CredentialQueryMatchResult: Identifiable {
    public var id: String { metadata.uuid }
}

extension CredentialQueryMatchResult: Equatable {
    public static func == (lhs: CredentialQueryMatchResult, rhs: CredentialQueryMatchResult) -> Bool {
        lhs.metadata.uuid == rhs.metadata.uuid
    }
}
