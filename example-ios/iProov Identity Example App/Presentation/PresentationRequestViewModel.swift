import Foundation
import SwiftUI
import identity

@MainActor
final class PresentationRequestViewModel: ObservableObject {
    struct PresentationAlert: Identifiable {
        let id = UUID()
        let title: String
        let message: String
    }

    @Published var isLoading = false
    @Published private(set) var matchResult: DCQLMatchResult?
    @Published var selectedCredentials: [CredentialQuery: CredentialQueryMatchResult] = [:]
    @Published var disclosedCredentials: [CredentialQuery: DisclosedCredential] = [:]
    @Published var shareBlockers: [String] = ["Loading request details…"]
    @Published var alert: PresentationAlert?
    @Published var successOutcome: PresentationOutcomeSuccess?

    let request: RespondablePresentationRequest

    init(request: RespondablePresentationRequest) {
        self.request = request
        Task { await loadRequestDetails() }
    }

    var availableQueries: [CredentialQuery] {
        credentialMatches.keys.sorted { $0.id < $1.id }
    }

    func matches(for query: CredentialQuery) -> [CredentialQueryMatchResult] {
        credentialMatches[query] ?? []
    }

    func selectableClaims(for query: CredentialQuery, match: CredentialQueryMatchResult) -> [ClaimQuery] {
        let available = Array(matchingClaims(for: match).keys)
        if let requested = query.claims, !requested.isEmpty {
            return requested.filter { requestedClaim in
                available.contains(where: { $0 == requestedClaim })
            }
        }
        return available
    }

    func claimDisplayName(_ claim: ClaimQuery) -> String {
        if let identifier = claim.id, !identifier.isEmpty {
            return identifier
        }
        return claim.path.joined(separator: ".")
    }

    func value(for claim: ClaimQuery, in match: CredentialQueryMatchResult) -> String {
        let map = matchingClaims(for: match)
        if let value = map[claim] {
            return String(describing: value)
        }
        return "—"
    }

    func selectedClaims(for query: CredentialQuery) -> Set<ClaimQuery> {
        disclosedCredentials[query]?.claims ?? []
    }

    func isClaimRequired(_ claim: ClaimQuery, for query: CredentialQuery) -> Bool {
        if let claimSets = query.claimSets, !claimSets.isEmpty {
            guard let claimId = claim.id else { return false }
            var intersection = Set(claimSets.first ?? [])
            for set in claimSets.dropFirst() {
                intersection.formIntersection(set)
            }
            return intersection.contains(claimId)
        }

        guard let requested = query.claims, !requested.isEmpty else { return false }
        guard let claimId = claim.id else { return false }
        return requested.compactMap(\.id).contains(claimId)
    }

    func loadRequestDetails() async {
        guard !isLoading else { return }
        isLoading = true
        defer { isLoading = false }
        do {
            matchResult = try await fetchMatchResult()
        } catch {
            alert = PresentationAlert(
                title: "Unable to load request",
                message: error.localizedDescription
            )
        }
        recomputeShareBlockers()
    }

    func select(_ match: CredentialQueryMatchResult, for query: CredentialQuery) {
        selectedCredentials[query] = match
        let claims = defaultClaims(for: query, match: match)
        disclosedCredentials[query] = DisclosedCredential(credential: match.credential, claims: claims)
        recomputeShareBlockers()
    }

    func toggle(_ claim: ClaimQuery, in query: CredentialQuery) {
        guard let match = selectedCredentials[query] else { return }
        var claims = disclosedCredentials[query]?.claims ?? []
        if claims.contains(claim) {
            claims.remove(claim)
        } else {
            claims.insert(claim)
        }
        disclosedCredentials[query] = DisclosedCredential(credential: match.credential, claims: claims)
        recomputeShareBlockers()
    }

    func clearAlert() {
        alert = nil
    }

    var canShare: Bool {
        !isLoading && shareBlockers.isEmpty
    }

    func share() async {
        guard let result = matchResult else { return }
        guard shareBlockers.isEmpty else { return }

        isLoading = true
        defer { isLoading = false }

        do {
            let submission = CredentialSubmission(
                disclosedCredentials: disclosedCredentials,
                matchResult: result
            )
            let outcome = try await respond(with: submission)
            switch outcome {
            case let success as PresentationOutcomeSuccess:
                successOutcome = success
            case let declined as PresentationOutcomeDeclined:
                alert = PresentationAlert(
                    title: "Presentation declined",
                    message: declined.reason ?? "The verifier declined this request."
                )
            case let rejected as PresentationOutcomeRejected:
                alert = PresentationAlert(
                    title: "Presentation rejected",
                    message: rejected.description_ ?? "The verifier rejected this request."
                )
            default:
                alert = PresentationAlert(
                    title: "Unknown response",
                    message: "The verifier returned an unexpected response."
                )
            }
        } catch {
            alert = PresentationAlert(
                title: "Failed to share credentials",
                message: error.localizedDescription
            )
        }
    }

    func clearSuccess() {
        successOutcome = nil
    }

    // MARK: - Private helpers

    private var credentialMatches: [CredentialQuery: [CredentialQueryMatchResult]] {
        guard let dict = matchResult?.credentials else { return [:] }
        var typed: [CredentialQuery: [CredentialQueryMatchResult]] = [:]
        for (key, value) in dict {
            guard
                let query = key as? CredentialQuery,
                let matches = value as? [CredentialQueryMatchResult]
            else { continue }
            typed[query] = matches
        }
        return typed
    }

    private func fetchMatchResult() async throws -> DCQLMatchResult {
        try await withCheckedThrowingContinuation { continuation in
            request.query.execute { result, error in
                if let result {
                    continuation.resume(returning: result)
                } else if let error {
                    continuation.resume(throwing: error)
                } else {
                    continuation.resume(throwing: NSError(domain: "PresentationRequest", code: -1))
                }
            }
        }
    }

    private func respond(with submission: CredentialSubmission) async throws -> PresentationOutcome {
        try await withCheckedThrowingContinuation { continuation in
            request.respond(submission: submission) { outcome, error in
                if let outcome {
                    continuation.resume(returning: outcome)
                } else if let error {
                    continuation.resume(throwing: error)
                } else {
                    continuation.resume(throwing: NSError(domain: "PresentationRequest", code: -2))
                }
            }
        }
    }

    private func defaultClaims(for query: CredentialQuery, match: CredentialQueryMatchResult) -> Set<ClaimQuery> {
        let available = Array(matchingClaims(for: match).keys)
        if let claimSets = query.claimSets, !claimSets.isEmpty {
            let byId = Dictionary(uniqueKeysWithValues: available.compactMap { claim in
                claim.id.map { ($0, claim) }
            })
            for set in claimSets {
                let resolved = set.compactMap { byId[$0] }
                if resolved.count == set.count {
                    return Set(resolved)
                }
            }
            return []
        }

        guard let requested = query.claims else { return [] }
        return Set(requested.filter { requestedClaim in
            available.contains(where: { $0 == requestedClaim })
        })
    }

    private func matchingClaims(for match: CredentialQueryMatchResult) -> [ClaimQuery: Any] {
        if let typed = match.matchingClaims as? [ClaimQuery: Any] {
            return typed
        }

        var typed: [ClaimQuery: Any] = [:]
        for (key, value) in match.matchingClaims {
            guard let claim = key as? ClaimQuery else { continue }
            typed[claim] = value
        }
        return typed
    }

    private func recomputeShareBlockers() {
        guard let result = matchResult else {
            shareBlockers = isLoading ? ["Loading request details…"] : ["Request details unavailable."]
            return
        }

        var reasons: [String] = []
        let credentialMap = credentialMatches

        let missing = credentialMap.keys.filter { selectedCredentials[$0] == nil }
        if !missing.isEmpty {
            let labels = missing.map { $0.id }.joined(separator: ", ")
            reasons.append("Select a credential for: \(labels)")
        }

        for query in credentialMap.keys {
            guard let chosen = selectedCredentials[query] else { continue }
            let allowed = Set(matchingClaims(for: chosen).keys)
            let picked = disclosedCredentials[query]?.claims ?? []

            let invalid = picked.filter { !allowed.contains($0) }
            if !invalid.isEmpty {
                let names = invalid.map { claimDisplayName($0) }.joined(separator: ", ")
                reasons.append("Some selected fields are not available for “\(query.id)”: \(names)")
            }

            if let claimSets = query.claimSets, !claimSets.isEmpty {
                let pickedIds = Set(picked.compactMap { $0.id })
                let satisfies = claimSets.contains { set in
                    Set(set).isSubset(of: pickedIds)
                }
                if !satisfies {
                    reasons.append("Choose a valid combination of fields for “\(query.id)”.")
                }
            } else if let requested = query.claims, !requested.isEmpty {
                let missingClaims = requested.filter { !picked.contains($0) }
                if !missingClaims.isEmpty {
                    let names = missingClaims.map { claimDisplayName($0) }.joined(separator: ", ")
                    reasons.append("Select all required fields for “\(query.id)”: \(names)")
                }
            }
        }

        shareBlockers = reasons
        if reasons.isEmpty && result.credentials.count == 0 {
            shareBlockers = ["No verifiable credentials matched this request."]
        }
    }
}
