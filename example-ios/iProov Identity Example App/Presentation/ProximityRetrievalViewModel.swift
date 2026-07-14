import Foundation
import identity

enum RetrievalEngagementSource {
    case qr(uri: String)
    case nfc
}

@MainActor
class ProximityRetrievalViewModel: ObservableObject {
    enum State {
        case idle
        case decoding
        case requestingTag
        case connecting
        case sendingRequest
        case waitingForResponse
        case processingResponse
        case completed(ProximityRetrievalResponse)
        case error(String)
    }

    @Published var state: State = .idle

    private let source: RetrievalEngagementSource
    private let wallet = WalletFactory.shared.instance!
    private var session: ProximityRetrievalSession?
    private var collectTask: Task<Void, Never>?

    init(source: RetrievalEngagementSource) {
        self.source = source
    }

    var title: String {
        switch state {
        case .idle: return "Preparing..."
        case .decoding: return "Decoding QR Code"
        case .requestingTag: return "Ready to Tap"
        case .connecting: return "Connecting"
        case .sendingRequest: return "Sending Request"
        case .waitingForResponse: return "Waiting for Response"
        case .processingResponse: return "Verifying Response"
        case .completed(let response):
            let count = response.documents.count
            return "\(count) Document\(count == 1 ? "" : "s") Received"
        case .error: return "Error"
        }
    }

    var subtitle: String? {
        switch state {
        case .requestingTag:
            return "Hold your phone near the holder's device."
        case .connecting:
            return "Establishing BLE connection with the holder's device..."
        case .waitingForResponse:
            return "The holder is reviewing your request..."
        case .completed(let response):
            let docTypes = response.documents.map { $0.docType }
            return docTypes.joined(separator: "\n")
        case .error(let message):
            return message
        default:
            return nil
        }
    }

    var isInProgress: Bool {
        switch state {
        case .idle, .decoding, .requestingTag, .connecting, .sendingRequest, .waitingForResponse, .processingResponse:
            return true
        case .completed, .error:
            return false
        }
    }

    func start() {
        do {
            let requestedDocuments = [
                DocumentRequest(
                    docType: "org.iso.18013.5.1.mDL",
                    itemsToRequest: [
                        "org.iso.18013.5.1": [
                            ClaimToRequest(name: "family_name", intentToRetain: false),
                            ClaimToRequest(name: "given_name", intentToRetain: false),
                            ClaimToRequest(name: "portrait", intentToRetain: false),
                        ]
                    ]
                )
            ]
            
            switch source {
            case .qr(let uri):
                session = try wallet.startProximityRetrieval(
                    uri: uri,
                    requestedDocuments: requestedDocuments,
                    createSigningData: nil,
                    config: ProximityConfig()
                )
            case .nfc:
                session = try wallet.startProximityRetrieval(
                    options: NfcRetrievalOptions(dialogMessage: "Hold near holder's device"),
                    requestedDocuments: requestedDocuments,
                    createSigningData: nil,
                    config: ProximityConfig()
                )
            }
            
            collectTask = Task {
                guard let session else { return }
                
                session.events.collect(
                    onEach: { event in
                        Task { @MainActor in
                            switch event {
                            case is ProximityRetrievalEvent.EngagementQrDecoding:
                                self.state = .decoding
                            case is ProximityRetrievalEvent.EngagementNfcRequestingTag:
                                self.state = .requestingTag
                            case is ProximityRetrievalEvent.EngagementNfcCompleted:
                                self.state = .connecting
                            case is ProximityRetrievalEvent.Connecting:
                                self.state = .connecting
                            case is ProximityRetrievalEvent.SendingRequest:
                                self.state = .sendingRequest
                            case is ProximityRetrievalEvent.WaitingForResponse:
                                self.state = .waitingForResponse
                            case is ProximityRetrievalEvent.ProcessingResponse:
                                self.state = .processingResponse
                            case let completed as ProximityRetrievalEvent.Completed:
                                self.state = .completed(completed.response)
                            case let error as ProximityRetrievalEvent.Error:
                                self.state = .error(error.message)
                            default:
                                break
                            }
                        }
                    },
                    onError: { error in
                        Task { @MainActor in
                            self.state = .error(error.localizedDescription)
                        }
                    })
            }
        } catch {
            state = .error(error.localizedDescription)
        }
    }

    func cancel() {
        collectTask?.cancel()
        let sessionToClose = session
        session = nil
        Task {
            try? await sessionToClose?.close()
        }
    }
}
