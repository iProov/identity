//
//  DocumentModels.swift
//  iProov Identity Example App
//
//  Created by Owen Woodward on 07/09/2026.
//
import Security
import identity

// MARK: - Request model

/// One document being asked for, with its elements grouped by namespace.
struct RequestedDocument: Identifiable {
    let id = UUID()
    let documentType: String
    /// namespace -> [(element, isRetaining)]
    let namespaces: [(namespace: String, elements: [(name: String, isRetaining: Bool)])]

    var retainsAnything: Bool {
        namespaces.contains { $0.elements.contains(where: \.isRetaining) }
    }
}

/// Per request doc selection for selective disclosure
struct DocSelection: Identifiable {
    let id = UUID()
    let docRequest: DocRequest
    var candidates: [DisclosedDocument]
    var selectedIndex: Int?
    var selectedItems: [String: Set<String>]

    var isReady: Bool { pickedCredential != nil }

    /// Starts with every requested element ticked, and the credential already picked
    init(_ docRequest: DocRequest, candidates: [DisclosedDocument]) {
        self.docRequest = docRequest
        self.candidates = candidates
        self.selectedIndex = candidates.count == 1 ? 0 : nil
        self.selectedItems = docRequest.requestedItems.mapValues { requested in
            Set(requested.map(\.elementIdentifier))
        }
    }

    var pickedCredential: DisclosedDocument? {
        guard let index = selectedIndex, index < candidates.count else { return nil }
        let ticked = selectedItems.filter { !$0.value.isEmpty }
        guard !ticked.isEmpty else { return nil }
        return DisclosedDocument(
            credential: candidates[index].credential,
            metadata: candidates[index].metadata,
            disclosedItems: ticked)
    }

    var itemRows: [ItemRow] {
        docRequest.requestedItems.keys.sorted().flatMap { namespace in
            (docRequest.requestedItems[namespace] ?? []).map { item in
                ItemRow(
                    namespace: namespace,
                    element: item.elementIdentifier,
                    intentToRetain: item.intentToRetain,
                    checked: selectedItems[namespace]?.contains(item.elementIdentifier) ?? false)
            }
        }
    }

    func title(forCandidate index: Int) -> String {
        if let name = candidates[index].metadata.display
            .compactMap(\.name).first(where: { !$0.isEmpty }) {
            return name
        }
        return ExtensionHelpers.documentDisplayName(docRequest.docType)
    }

    func subtitle(forCandidate index: Int) -> String {
        let metadata = candidates[index].metadata
        let added = Date(timeIntervalSince1970: Double(metadata.addedAt) / 1000)
        return "\(metadata.issuer.name) · added \(added.formatted(date: .abbreviated, time: .omitted))"
    }
}

/// Requested element, flattened out from the`requestedItems`
struct ItemRow: Identifiable {
    let namespace: String
    let element: String
    let intentToRetain: Bool
    let checked: Bool
    var id: String { "\(namespace).\(element)" }
}

struct DocumentAlternative: Identifiable {
    let id = UUID()
    let documents: [RequestedDocument]
}

struct PresentmentGroup: Identifiable {
    let id = UUID()
    let isMandatory: Bool
    let alternatives: [DocumentAlternative]
}

enum ResponseError: LocalizedError {
    case missingOrigin, malformedRequest, noMatchingCredential

    var errorDescription: String? {
        switch self {
        case .missingOrigin:
            return "The API supplied no requesting origin."
        case .malformedRequest:
            return "The request payload was not UTF-8 JSON."
        case .noMatchingCredential:
            return "No stored credential matches what this verifier asked for."
        }
    }
}
