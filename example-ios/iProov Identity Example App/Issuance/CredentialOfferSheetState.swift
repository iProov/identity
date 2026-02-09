import Foundation
import identity

struct CredentialOfferSheetState: Identifiable {
    struct Item: Identifiable {
        let id = UUID()
        let descriptor: CredentialDescriptor
        let display: DisplayProperties?
        var isSelected: Bool
    }

    enum Status: Equatable {
        case idle
        case submitting
        case completed(summary: IssuanceSummary)
        case failed(message: String)
        case transactionCodeRequired(challenge: TransactionCodeChallenge)

        static func == (lhs: Status, rhs: Status) -> Bool {
            switch (lhs, rhs) {
            case (.idle, .idle), (.submitting, .submitting):
                return true
            case (.completed(let l), .completed(let r)):
                return l === r
            case (.failed(let l), .failed(let r)):
                return l == r
            case (.transactionCodeRequired(let l), .transactionCodeRequired(let r)):
                return l === r
            default:
                return false
            }
        }
    }

    let id = UUID()
    let offer: RespondableCredentialOffer
    let issuerDisplay: DisplayProperties?
    var items: [Item]
    var status: Status = .idle

    init(offer: RespondableCredentialOffer) {
        self.offer = offer
        self.issuerDisplay = offer.issuer.bestDisplay
        let descriptors = offer.credentials
        self.items = descriptors.map { descriptor in
            Item(descriptor: descriptor, display: descriptor.bestDisplay, isSelected: true)
        }
    }

    var selectedDescriptors: [CredentialDescriptor] {
        items.filter { $0.isSelected }.map(\.descriptor)
    }

    var canConfirm: Bool {
        !selectedDescriptors.isEmpty && status != .submitting
    }

    mutating func toggleSelection(id: UUID) {
        guard let index = items.firstIndex(where: { $0.id == id }) else { return }
        items[index].isSelected.toggle()
    }
}
