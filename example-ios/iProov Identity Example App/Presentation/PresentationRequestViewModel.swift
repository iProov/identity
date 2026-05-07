import Foundation
import SwiftUI
import identity

/**
 Represents a credential selected by the user that was a match for the presentation request
 */
struct CredentialSelection {
    /**
        The raw match result from the SDK
     */
    let match: CredentialQueryMatchResult
    
    /**
        The claims dislosed by the user for this credential (some are optional and this can be selected / toggled in the UI)
     */
    var disclosedClaims: Set<ClaimQuery>
}

@MainActor
final class PresentationRequestViewModel: ObservableObject {
    @Published var isLoading = false
    @Published private(set) var walletMatches: DCQLMatchResult?
    @Published var selections: [CredentialQuery: CredentialSelection] = [:]
    @Published var alert: AlertDialog?
    @Published var successOutcome: PresentationOutcomeSuccess?

    /**
        This is the presentation object returned by the SDK for the authorization request.
     */
    let request: RespondablePresentationRequest

    init(request: RespondablePresentationRequest) {
        self.request = request
        Task { await loadRequestDetails() }
    }

    private var credentialSets: [CredentialSetQuery]? {
        request.query.definition.credentialSets
    }

    // MARK: - 1. Load (match wallet credentials against the request)

    /// Matches wallet credentials against the verifier's request, populating `walletMatches`.
    /// Called automatically on init; can be invoked again to retry after a failure.
    func loadRequestDetails() async {
        guard !isLoading else { return }
        isLoading = true
        defer { isLoading = false }
        do {
            walletMatches = try await fetchMatchResult()
        } catch {
            alert = AlertDialog(
                title: "Unable to load request",
                message: error.localizedDescription
            )
        }
    }

    /// The verifier's credential queries that can be satisfied by at least one wallet credential,
    /// sorted by ID for consistency (no further reasoning behind the sorting).
    /// e.g an mDL credential and PID credential are being queried.
    var matchableQueries: [CredentialQuery] {
        (walletMatches?.credentials ?? [:]).keys.sorted { $0.id < $1.id }
    }

    /// Returns the (potentially multiple) credentials that satisfy the given query.
    /// A single query may be satisfiable by multiple wallet credentials.
    /// e.g the query is for an mDL and there are 2 that the wallet holds
    func matchingCredentials(for query: CredentialQuery) -> [CredentialQueryMatchResult] {
        walletMatches?.credentials[query] ?? []
    }

    // MARK: - 2. Select (user picks credentials and fields to share)

    /// Selects a wallet credential to satisfy a query, pre-populating disclosed claims with defaults.
    func select(_ match: CredentialQueryMatchResult, for query: CredentialQuery) {
        let claims = initialDisclosedClaims(for: query, match: match)
        selections[query] = CredentialSelection(match: match, disclosedClaims: claims)
    }

    /// Toggles whether a claim is included in the disclosed set for the given query.
    func toggle(_ claim: ClaimQuery, in query: CredentialQuery) {
        guard var selection = selections[query] else { return }
        if selection.disclosedClaims.contains(claim) {
            selection.disclosedClaims.remove(claim)
        } else {
            selection.disclosedClaims.insert(claim)
        }
        selections[query] = selection
    }

    /// Returns the claims available for disclosure, filtered to those both requested and present in the match.
    func claims(for query: CredentialQuery, match: CredentialQueryMatchResult) -> [ClaimQuery] {
        let available = Array(match.matchingClaims.keys)
        if let requested = query.claims, !requested.isEmpty {
            return requested.filter { requestedClaim in
                available.contains(where: { $0 == requestedClaim })
            }
        }
        return available
    }

    /// Returns the set of claims the user has chosen to disclose for the given query.
    func selectedClaims(for query: CredentialQuery) -> Set<ClaimQuery> {
        selections[query]?.disclosedClaims ?? []
    }

    func isQueryRequired(_ query: CredentialQuery) -> Bool {
        guard let result = walletMatches else { return true }
        guard let credentialSets, !credentialSets.isEmpty else { return true }

        if hasUnsatisfiedRequiredSet(result) {
            let requiredQueryIds = Set(
                credentialSets
                    .filter { $0.required }
                    .flatMap { $0.options.flatMap { $0 } }
            )
            return requiredQueryIds.contains(query.id)
        }

        return result.satisfiedSets
            .filter { $0.query.required }
            .contains { setResult in
                setResult.satisfiedOptions.contains { option in
                    option.contains(query.id)
                }
            }
    }

    /// Returns `true` if the claim must be disclosed.
    /// When `claimSets` exist, a claim is required only if it appears in every set.
    /// Without `claimSets`, all explicitly listed claims are required per the DCQL spec.
    func isClaimRequired(_ claim: ClaimQuery, for query: CredentialQuery) -> Bool {
        if let claimSets = query.claimSets, !claimSets.isEmpty {
            guard let claimId = claim.id else { return false }
            return claimSets.allSatisfy { $0.contains(claimId) }
        }
        guard let requested = query.claims, !requested.isEmpty else { return false }
        guard let claimId = claim.id else { return false }
        return requested.compactMap(\.id).contains(claimId)
    }

    /// Returns a display name for the claim, preferring its `id` and falling back to its dot-joined path.
    func claimName(_ claim: ClaimQuery) -> String {
        if let identifier = claim.id, !identifier.isEmpty {
            return identifier
        }
        return claim.path.joined(separator: ".")
    }

    /// Returns the credential's value for the given claim, or "—" if not present.
    func value(for claim: ClaimQuery, in match: CredentialQueryMatchResult) -> String {
        let map = match.matchingClaims
        if let value = map[claim] {
            return String(describing: value)
        }
        return "—"
    }

    // MARK: - 3. Share (submit the selection to the verifier)

    var shareBlockers: [String] {
        guard let result = walletMatches else {
            return isLoading ? ["Loading request details..."] : ["Request details unavailable."]
        }

        var reasons: [String] = []
        if hasUnsatisfiedRequiredSet(result) {
            reasons.append("This verifier request cannot be satisfied with the credentials currently in this wallet.")
        } else {
            let selectedIds = Set(selections.keys.map(\.id))
            let missingIds = missingSelectionsForRequiredSets(result, selectedQueryIds: selectedIds)
            if !missingIds.isEmpty {
                let labels = missingIds
                    .sorted()
                    .map(labelForQueryId)
                    .joined(separator: ", ")
                reasons.append("Select a credential for: \(labels)")
            }
        }

        for query in selections.keys.sorted(by: { $0.id < $1.id }) {
            guard let selection = selections[query] else { continue }
            let allowed = Set(selection.match.matchingClaims.keys)
            let picked = selection.disclosedClaims

            let invalidClaims = picked.filter { !allowed.contains($0) }
            if !invalidClaims.isEmpty {
                let names = invalidClaims
                    .map { claimName($0) }
                    .sorted()
                    .joined(separator: ", ")
                reasons.append("Some selected fields are not available for \"\(queryTitle(query))\": \(names)")
            }

            guard satisfiesDCQL(query, picked: picked) else {
                if let claimSets = query.claimSets, !claimSets.isEmpty {
                    let example = claimSets.first?.joined(separator: ", ") ?? "a valid combination"
                    reasons.append("Choose a valid combination of fields for \"\(queryTitle(query))\" (for example: \(example)).")
                } else {
                    let missingClaims = (query.claims ?? []).filter { !picked.contains($0) }
                    let names = missingClaims
                        .map { claimName($0) }
                        .sorted()
                        .joined(separator: ", ")
                    reasons.append("Select all required fields for \"\(queryTitle(query))\": \(names)")
                }
                continue
            }
        }

        return reasons
    }

    var canShare: Bool {
        !isLoading && walletMatches != nil && shareBlockers.isEmpty
    }

    /// Submits the current selections to the verifier. Sets `successOutcome` on success, or `alert` on failure.
    func share() async {
        guard shareBlockers.isEmpty else {
            alert = AlertDialog(
                title: "Unable to share credentials",
                message: shareBlockers.joined(separator: "\n")
            )
            return
        }
        guard let result = walletMatches else { return }

        isLoading = true
        defer { isLoading = false }

        do {
            let disclosedCredentials = selections.mapValues { selection in
                DisclosedCredential(credential: selection.match.credential, claims: selection.disclosedClaims)
            }
            let submission = CredentialSubmission(
                disclosedCredentials: disclosedCredentials,
                matchResult: result
            )
            let outcome = try await respond(with: submission)
            switch outcome {
            case let success as PresentationOutcomeSuccess:
                successOutcome = success
            case let declined as PresentationOutcomeDeclined:
                alert = AlertDialog(
                    title: "Presentation declined",
                    message: declined.reason ?? "The verifier declined this request."
                )
            case let rejected as PresentationOutcomeRejected:
                alert = AlertDialog(
                    title: "Presentation rejected",
                    message: rejected.description_ ?? "The verifier rejected this request."
                )
            default:
                alert = AlertDialog(
                    title: "Unknown response",
                    message: "The verifier returned an unexpected response."
                )
            }
        } catch {
            alert = AlertDialog(
                title: "Failed to share credentials",
                message: error.localizedDescription
            )
        }
    }

    // MARK: - Private helpers

    // The SDK uses completion handlers; these bridges let callers use async/await.
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

    /// Computes the claims that should be pre-selected for disclosure when the user first picks a credential.
    ///
    /// When the query specifies `claimSets` (alternative groups of acceptable claims), this returns
    /// the first group that can be fully satisfied by the credential. Without `claimSets`, it returns
    /// every explicitly requested claim that the credential contains.
    ///
    /// The result is used as the starting value for `CredentialSelection.disclosedClaims`; the user
    /// can then toggle optional claims on or off before sharing.
    private func initialDisclosedClaims(for query: CredentialQuery, match: CredentialQueryMatchResult) -> Set<ClaimQuery> {
        let available = Array(match.matchingClaims.keys)
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

    private func hasUnsatisfiedRequiredSet(_ result: DCQLMatchResult) -> Bool {
        result.satisfiedSets.contains { setResult in
            setResult.query.required && setResult.satisfiedOptions.isEmpty
        }
    }

    private func missingSelectionsForRequiredSets(
        _ result: DCQLMatchResult,
        selectedQueryIds: Set<String>
    ) -> Set<String> {
        guard let credentialSets, !credentialSets.isEmpty else {
            return Set(matchableQueries.map(\.id).filter { !selectedQueryIds.contains($0) })
        }

        var missing = Set<String>()
        for setResult in result.satisfiedSets where setResult.query.required {
            guard !setResult.satisfiedOptions.isEmpty else { continue }

            let alreadyCovered = setResult.satisfiedOptions.contains { option in
                option.allSatisfy { selectedQueryIds.contains($0) }
            }
            if !alreadyCovered, let bestOption = setResult.satisfiedOptions.first {
                missing.formUnion(bestOption.filter { !selectedQueryIds.contains($0) })
            }
        }

        return missing
    }

    private func satisfiesDCQL(_ query: CredentialQuery, picked: Set<ClaimQuery>) -> Bool {
        let requested = Set(query.claims ?? [])
        guard let claimSets = query.claimSets, !claimSets.isEmpty else {
            return requested.isEmpty || requested.allSatisfy { picked.contains($0) }
        }

        let pickedIds = Set(picked.compactMap(\.id))
        return claimSets.contains { set in
            set.allSatisfy { pickedIds.contains($0) }
        }
    }

    private func labelForQueryId(_ queryId: String) -> String {
        matchableQueries.first(where: { $0.id == queryId }).map { queryTitle($0) } ?? queryId
    }

    func queryTitle(_ query: CredentialQuery) -> String {
        query.id.isEmpty ? "Requested information" : query.id
    }
}
