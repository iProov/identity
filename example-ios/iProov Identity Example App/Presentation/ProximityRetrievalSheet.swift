import SwiftUI
import identity

struct ProximityRetrievalSheet: View {
    @StateObject private var viewModel: ProximityRetrievalViewModel
    let onDismiss: () -> Void
    let onCompleted: (ProximityRetrievalResponse) -> Void

    init(
        uri: String,
        onDismiss: @escaping () -> Void,
        onCompleted: @escaping (ProximityRetrievalResponse) -> Void
    ) {
        _viewModel = StateObject(
            wrappedValue: ProximityRetrievalViewModel(uri: uri)
        )
        self.onDismiss = onDismiss
        self.onCompleted = onCompleted
    }

    var body: some View {
        NavigationStack {
            Group {
                if case .completed(let response) = viewModel.state {
                    completedView(response)
                } else {
                    progressView
                }
            }
            .navigationTitle("Proximity Verification")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .cancellationAction) {
                    if viewModel.isInProgress {
                        Button("Cancel") {
                            viewModel.cancel()
                            onDismiss()
                        }
                    }
                }
            }
        }
        .interactiveDismissDisabled(viewModel.isInProgress)
        .onAppear {
            viewModel.start()
        }
    }

    // MARK: - Progress View

    private var progressView: some View {
        VStack(spacing: 24) {
            Spacer()

            statusIcon
                .font(.system(size: 48))
                .symbolRenderingMode(.hierarchical)

            Text(viewModel.title)
                .font(.title3.weight(.semibold))

            if let subtitle = viewModel.subtitle {
                Text(subtitle)
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .multilineTextAlignment(.center)
                    .padding(.horizontal, 32)
            }

            if viewModel.isInProgress {
                ProgressView()
                    .controlSize(.large)
            }

            Spacer()

            if case .error = viewModel.state {
                Button("Close") {
                    onDismiss()
                }
                .buttonStyle(.bordered)
                .controlSize(.large)
                .padding(.horizontal)
                .padding(.bottom)
            }
        }
    }

    // MARK: - Completed View

    private func completedView(_ response: ProximityRetrievalResponse) -> some View {
        ScrollView {
            VStack(spacing: 16) {
                // Success header
                VStack(spacing: 8) {
                    Image(systemName: "checkmark.shield.fill")
                        .font(.system(size: 44))
                        .foregroundStyle(.green)

                    Text("Verified")
                        .font(.title2.weight(.bold))

                    Text("\(response.documents.count) document\(response.documents.count == 1 ? "" : "s") received")
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }
                .padding(.top, 20)
                .padding(.bottom, 8)

                // Document cards
                ForEach(Array(response.documents.enumerated()), id: \.offset) { _, doc in
                    documentCard(doc)
                }

                // Done button
                Button("Done") {
                    onCompleted(response)
                }
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
                .padding(.top, 8)
            }
            .padding(.horizontal)
            .padding(.bottom, 24)
        }
    }

    private func documentCard(_ doc: ReceivedMDocCredential) -> some View {
        VStack(alignment: .leading, spacing: 0) {
            // Card header
            HStack {
                Image(systemName: iconForDocType(doc.docType))
                    .font(.title3)
                    .foregroundStyle(.white)
                    .frame(width: 36, height: 36)
                    .background(Color.accentColor.gradient)
                    .clipShape(RoundedRectangle(cornerRadius: 8))

                VStack(alignment: .leading, spacing: 2) {
                    Text(displayNameForDocType(doc.docType))
                        .font(.headline)
                    HStack(spacing: 4) {
                        if let country = doc.issuerCountry {
                            Text(flagEmoji(for: country))
                            Text(country)
                        }
                        Text("·")
                            .foregroundStyle(.tertiary)
                        Text(doc.deviceAuthType == .signature ? "ECDSA" : "MAC")
                            .font(.caption.weight(.medium))
                            .padding(.horizontal, 6)
                            .padding(.vertical, 2)
                            .background(Color.green.opacity(0.15))
                            .foregroundStyle(.green)
                            .clipShape(Capsule())
                    }
                    .font(.caption)
                    .foregroundStyle(.secondary)
                }

                Spacer()
            }
            .padding()

            Divider()

            // Claims
            let allClaims = extractClaims(from: doc)

            // Portrait at top if present
            if let portraitData = doc.getClaimDataValue(namespace: "org.iso.18013.5.1", name: "portrait"),
               let uiImage = UIImage(data: portraitData as Data) {
                HStack {
                    Spacer()
                    Image(uiImage: uiImage)
                        .resizable()
                        .aspectRatio(contentMode: .fill)
                        .frame(width: 100, height: 130)
                        .clipShape(RoundedRectangle(cornerRadius: 8))
                    Spacer()
                }
                .padding(.vertical, 12)

                Divider()
            }

            // Text claims
            VStack(spacing: 0) {
                let textClaims = allClaims.filter { $0.key != "portrait" }
                ForEach(Array(textClaims.enumerated()), id: \.offset) { index, claim in
                    HStack {
                        Text(formatClaimName(claim.key))
                            .font(.subheadline)
                            .foregroundStyle(.secondary)
                            .frame(width: 120, alignment: .leading)

                        Spacer()

                        Text(formatClaimValue(claim.value))
                            .font(.subheadline.weight(.medium))
                            .multilineTextAlignment(.trailing)
                    }
                    .padding(.horizontal)
                    .padding(.vertical, 10)

                    if index < textClaims.count - 1 {
                        Divider()
                            .padding(.leading)
                    }
                }
            }

            // Validity footer
            if let from = doc.validFrom, let until = doc.validUntil {
                Divider()
                HStack {
                    Image(systemName: "calendar.badge.checkmark")
                        .foregroundStyle(.secondary)
                    Text("Valid: \(formatDate(from)) – \(formatDate(until))")
                        .font(.caption)
                        .foregroundStyle(.secondary)
                }
                .padding()
            }
        }
        .background(Color(.secondarySystemGroupedBackground))
        .clipShape(RoundedRectangle(cornerRadius: 12))
    }

    // MARK: - Status Icon

    @ViewBuilder
    private var statusIcon: some View {
        switch viewModel.state {
        case .idle, .decoding:
            Image(systemName: "qrcode")
                .foregroundStyle(.blue)
        case .connecting:
            Image(systemName: "antenna.radiowaves.left.and.right")
                .foregroundStyle(.blue)
        case .sendingRequest:
            Image(systemName: "arrow.up.circle")
                .foregroundStyle(.blue)
        case .waitingForResponse:
            Image(systemName: "hourglass")
                .foregroundStyle(.orange)
        case .processingResponse:
            Image(systemName: "checkmark.shield")
                .foregroundStyle(.blue)
        case .completed:
            Image(systemName: "checkmark.circle.fill")
                .foregroundStyle(.green)
        case .error:
            Image(systemName: "exclamationmark.triangle.fill")
                .foregroundStyle(.red)
        }
    }

    // MARK: - Helpers

    private struct ClaimEntry {
        let key: String
        let value: Any?
    }

    private func extractClaims(from doc: ReceivedMDocCredential) -> [ClaimEntry] {
        var claims: [ClaimEntry] = []
        for (_, namespaceClaims) in doc.nameSpaces {
            for (key, value) in namespaceClaims {
                claims.append(ClaimEntry(key: key, value: value))
            }
        }
        return claims
    }

    private func formatClaimValue(_ value: Any?) -> String {
        switch value {
        case let str as String:
            return str
        case let num as NSNumber:
            return num.stringValue
        case let bool as Bool:
            return bool ? "Yes" : "No"
        case is Data:
            return "[binary data]"
        case let list as [Any?]:
            return list.compactMap { formatClaimValue($0) }.joined(separator: ", ")
        case nil:
            return "\u{2014}"
        default:
            return String(describing: value!)
        }
    }

    private func formatDate(_ isoDate: String) -> String {
        if let range = isoDate.range(of: "T") {
            return String(isoDate[isoDate.startIndex..<range.lowerBound])
        }
        return isoDate
    }

    // displayNameForDocType / iconForDocType / formatClaimName are shared helpers in
    // DisplayHelpers.swift.

    private func flagEmoji(for countryCode: String) -> String {
        let base: UInt32 = 127397
        return countryCode.uppercased().unicodeScalars.compactMap {
            UnicodeScalar(base + $0.value).map(String.init)
        }.joined()
    }
}

