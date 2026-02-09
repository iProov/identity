import SwiftUI
import identity

// MARK: - Display Properties Helpers

extension DisplayProperties {
    
    /// Parses hex color string to SwiftUI Color with fallback.
    /// LIMITATION: Only supports #RRGGBB and #AARRGGBB formats.
    /// Invalid hex strings silently fall back to the provided default.
    func backgroundColor(fallback: Color = Color(.secondarySystemBackground)) -> Color {
        guard let hex = self.backgroundColor else { return fallback }
        return Color(hex: hex) ?? fallback
    }
    
    /// Parses text color with automatic contrast consideration.
    /// LIMITATION: Does not perform WCAG contrast ratio calculation.
    /// Relies on issuer providing accessible color combinations.
    func textColor(fallback: Color = .primary) -> Color {
        guard let hex = self.textColor else { return fallback }
        return Color(hex: hex) ?? fallback
    }
    
    /// Returns a valid URL for the logo, or nil if missing/malformed.
    var logoURL: URL? {
        guard let urlString = self.logoUrl, !urlString.isEmpty else { return nil }
        return URL(string: urlString)
    }
    
    /// Provides accessible description for VoiceOver.
    var accessibilityDescription: String {
        [name, description_].compactMap { $0 }.joined(separator: ". ")
    }
}

// MARK: - Logo Image View

/// Async logo loader with placeholder and error states.
/// LIMITATION: No disk caching - relies on URLSession's default cache.
/// Consider implementing NSCache for memory caching in production if
/// credentials are frequently displayed.
struct IssuerLogoView: View {
    let url: URL?
    let altText: String?
    let size: CGFloat
    let tintColor: Color
    
    init(url: URL?, altText: String? = nil, size: CGFloat = 40, tintColor: Color = .secondary) {
        self.url = url
        self.altText = altText
        self.size = size
        self.tintColor = tintColor
    }
    
    var body: some View {
        Group {
            if let url = url {
                AsyncImage(url: url, transaction: Transaction(animation: .easeIn(duration: 0.2))) { phase in
                    switch phase {
                    case .success(let image):
                        image
                            .resizable()
                            .aspectRatio(contentMode: .fit)
                    case .failure:
                        // LIMITATION: No retry mechanism for failed loads.
                        // User must dismiss and re-open sheet to retry.
                        fallbackIcon
                    case .empty:
                        ProgressView()
                            .scaleEffect(0.7)
                    @unknown default:
                        fallbackIcon
                    }
                }
            } else {
                fallbackIcon
            }
        }
        .frame(width: size, height: size)
        .accessibilityLabel(altText ?? "Logo")
    }
    
    private var fallbackIcon: some View {
        Image(systemName: "building.2.fill")
            .resizable()
            .aspectRatio(contentMode: .fit)
            .padding(size * 0.2)
            .foregroundStyle(tintColor)
    }
}

// MARK: - Issuer Header

struct IssuerHeaderView: View {
    let display: DisplayProperties?
    
    var body: some View {
        HStack(spacing: 12) {
            IssuerLogoView(
                url: display?.logoURL,
                altText: display?.logoAltText,
                size: 48
            )
            .background(Color(.tertiarySystemBackground))
            .clipShape(RoundedRectangle(cornerRadius: 8))
            
            VStack(alignment: .leading, spacing: 2) {
                Text(display?.name ?? "Unknown Issuer")
                    .font(.headline)
                    .foregroundStyle(.primary)
                
                if let description = display?.description_, !description.isEmpty {
                    Text(description)
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                        .lineLimit(2)
                }
            }
            
            Spacer(minLength: 0)
        }
        .accessibilityElement(children: .combine)
        .accessibilityLabel(display?.accessibilityDescription ?? "Issuer")
    }
}

// MARK: - Credential Card

/// Displays a single credential offer with issuer-specified styling.
/// LIMITATION: Background images (if added to spec) are not supported.
/// Only solid colors from backgroundColor property are rendered.
struct CredentialOfferCard: View {
    let item: CredentialOfferSheetState.Item
    let isDisabled: Bool
    let onToggle: () -> Void
    
    private var background: Color {
        item.display?.backgroundColor() ?? Color(.secondarySystemBackground)
    }
    
    private var textColor: Color {
        item.display?.textColor() ?? .primary
    }
    
    var body: some View {
        Button(action: onToggle) {
            HStack(alignment: .center, spacing: 12) {
                // Credential logo (smaller, inline)
                IssuerLogoView(
                    url: item.display?.logoURL,
                    altText: item.display?.logoAltText,
                    size: 36,
                    tintColor: textColor.opacity(0.6)
                )
                
                VStack(alignment: .leading, spacing: 4) {
                    Text(item.display?.name ?? "Credential")
                        .font(.body.weight(.medium))
                        .foregroundStyle(textColor)
                    
                    if let description = item.display?.description_, !description.isEmpty {
                        Text(description)
                            .font(.caption)
                            .foregroundStyle(textColor.opacity(0.8))
                            .lineLimit(2)
                    }
                    
                    // Format badge - useful for technical users
                    Text(item.descriptor.format.uppercased())
                        .font(.caption2.weight(.medium))
                        .foregroundStyle(textColor.opacity(0.6))
                        .padding(.horizontal, 6)
                        .padding(.vertical, 2)
                        .background(textColor.opacity(0.1))
                        .clipShape(Capsule())
                }
                
                Spacer(minLength: 0)
                
                Image(systemName: item.isSelected ? "checkmark.circle.fill" : "circle")
                    .font(.title2)
                    .foregroundStyle(item.isSelected ? Color.accentColor : textColor.opacity(0.4))
                    .symbolRenderingMode(.hierarchical)
            }
            .padding(12)
            .background(background.opacity(item.isSelected ? 1.0 : 0.6))
            .clipShape(RoundedRectangle(cornerRadius: 12))
            .overlay(
                RoundedRectangle(cornerRadius: 12)
                    .strokeBorder(
                        item.isSelected ? Color.accentColor : Color.clear,
                        lineWidth: 2
                    )
            )
        }
        .buttonStyle(.plain)
        .disabled(isDisabled)
        .opacity(isDisabled ? 0.6 : 1.0)
        .accessibilityLabel(item.display?.name ?? "Credential")
        .accessibilityHint(item.isSelected ? "Selected. Double tap to deselect." : "Double tap to select.")
        .accessibilityAddTraits(item.isSelected ? .isSelected : [])
    }
}

// MARK: - Status Views

struct IssuanceSuccessView: View {
    let summary: IssuanceSummary
    
    private var added: [CredentialMetadata] {
        return summary.credentialsAdded
    }

    private var errors: [(CredentialMetadata, OID4VCICredentialError)] {
        return summary.errors.compactMap { key, value in
            return (key, value)
        }
    }
    
    var body: some View {
        VStack(alignment: .leading, spacing: 20) {
            // Success header
            HStack(spacing: 12) {
                Image(systemName: added.isEmpty ? "exclamationmark.triangle.fill" : "checkmark.seal.fill")
                    .font(.largeTitle)
                    .foregroundStyle(added.isEmpty ? .orange : .green)
                    .symbolRenderingMode(.hierarchical)
                
                VStack(alignment: .leading, spacing: 2) {
                    Text(added.isEmpty ? "Issuance Incomplete" : "Credentials Added")
                        .font(.headline)
                    Text("\(added.count) credential\(added.count == 1 ? "" : "s") added")
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }
            }
            
            if !added.isEmpty {
                VStack(alignment: .leading, spacing: 8) {
                    ForEach(added, id: \.uuid) { metadata in
                        IssuedCredentialRow(metadata: metadata)
                    }
                }
            }
            
            if !errors.isEmpty {
                VStack(alignment: .leading, spacing: 8) {
                    Label("Failed to issue", systemImage: "xmark.circle.fill")
                        .font(.subheadline.weight(.medium))
                        .foregroundStyle(.red)
                    
                    ForEach(errors, id: \.0.uuid) { metadata, error in
                        ErrorRow(metadata: metadata, error: error)
                    }
                }
                .padding(12)
                .background(Color.red.opacity(0.08))
                .clipShape(RoundedRectangle(cornerRadius: 10))
            }
            
            if added.isEmpty && errors.isEmpty {
                ContentUnavailableView(
                    "No Credentials Issued",
                    systemImage: "doc.badge.ellipsis",
                    description: Text("The issuer did not provide any credentials.")
                )
            }
        }
    }
}

private struct IssuedCredentialRow: View {
    let metadata: CredentialMetadata
    
    var body: some View {
        HStack(spacing: 10) {
            Image(systemName: "checkmark.circle.fill")
                .foregroundStyle(.green)
            
            VStack(alignment: .leading, spacing: 2) {
                Text(metadata.bestDisplay?.name ?? "Credential")
                    .font(.subheadline.weight(.medium))
                Text(metadata.issuer.name)
                    .font(.caption)
                    .foregroundStyle(.secondary)
            }
            
            Spacer()
        }
        .padding(.vertical, 4)
    }
}

private struct ErrorRow: View {
    let metadata: CredentialMetadata
    let error: OID4VCICredentialError
    
    var body: some View {
        VStack(alignment: .leading, spacing: 4) {
            Text(metadata.bestDisplay?.name ?? "Credential")
                .font(.subheadline.weight(.medium))
            
            Text(error.error)
                .font(.caption.weight(.medium))
                .foregroundStyle(.red)
            
            if !error.description_.isEmpty {
                Text(error.description_)
                    .font(.caption)
                    .foregroundStyle(.secondary)
            }
        }
    }
}

struct StatusMessageView: View {
    let title: String
    let message: String
    let icon: String
    let iconColor: Color
    
    var body: some View {
        VStack(spacing: 16) {
            Image(systemName: icon)
                .font(.system(size: 48))
                .foregroundStyle(iconColor)
                .symbolRenderingMode(.hierarchical)
            
            VStack(spacing: 8) {
                Text(title)
                    .font(.headline)
                    .multilineTextAlignment(.center)
                
                Text(message)
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .multilineTextAlignment(.center)
            }
        }
        .frame(maxWidth: .infinity)
        .padding(.vertical, 24)
    }
}

// MARK: - Main Sheet View

struct CredentialOfferSheet: View {
    let state: CredentialOfferSheetState
    let onToggleSelection: (UUID) -> Void
    let onConfirm: () -> Void
    let onSubmitTransactionCode: (String) -> Void
    let onDismiss: () -> Void
    
    var body: some View {
        NavigationStack {
            VStack(spacing: 0) {
                sheetContent
            }
            .navigationTitle("Add Credentials")
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .cancellationAction) {
                    if state.status != .submitting {
                        Button("Cancel", action: onDismiss)
                    }
                }
            }
            .interactiveDismissDisabled(state.status == .submitting)
        }
        .presentationDetents([.medium, .large])
        .presentationDragIndicator(.visible)
    }
    
    @ViewBuilder
    private var sheetContent: some View {
        switch state.status {
        case .completed(let summary):
            completedContent(summary: summary)
            
        case .failed(let message):
            failedContent(message: message)
            
        case .transactionCodeRequired(let challenge):
            transactionCodeContent(challenge: challenge)
            
        case .idle, .submitting:
            selectionContent
        }
    }
    
    private var selectionContent: some View {
        VStack(spacing: 0) {
            ScrollView {
                VStack(alignment: .leading, spacing: 20) {
                    // Issuer info section
                    IssuerHeaderView(display: state.issuerDisplay)
                        .padding(.horizontal)
                        .padding(.top, 8)
                    
                    Divider()
                        .padding(.horizontal)
                    
                    // Selection instructions
                    Text("Select credentials to add to your wallet")
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                        .padding(.horizontal)
                    
                    // Credential list
                    VStack(spacing: 10) {
                        ForEach(state.items) { item in
                            CredentialOfferCard(
                                item: item,
                                isDisabled: state.status == .submitting,
                                onToggle: { onToggleSelection(item.id) }
                            )
                        }
                    }
                    .padding(.horizontal)
                }
                .padding(.bottom, 16)
            }
            
            // Bottom action bar
            actionBar
        }
    }
    
    private var actionBar: some View {
        VStack(spacing: 12) {
            Divider()
            
            if state.status == .submitting {
                HStack(spacing: 8) {
                    ProgressView()
                    Text("Adding credentials…")
                        .font(.subheadline)
                        .foregroundStyle(.secondary)
                }
                .frame(height: 44)
            } else {
                Button(action: onConfirm) {
                    Text("Add \(state.selectedDescriptors.count) Credential\(state.selectedDescriptors.count == 1 ? "" : "s")")
                        .frame(maxWidth: .infinity)
                }
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
                .disabled(!state.canConfirm)
            }
        }
        .padding(.horizontal)
        .padding(.bottom, 8)
        .background(Color(.systemBackground))
    }
    
    private func completedContent(summary: IssuanceSummary) -> some View {
        VStack {
            ScrollView {
                IssuanceSuccessView(summary: summary)
                    .padding()
            }
            
            Divider()
            
            Button("Done", action: onDismiss)
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
                .frame(maxWidth: .infinity)
                .padding()
        }
    }
    
    private func failedContent(message: String) -> some View {
        VStack {
            Spacer()
            
            StatusMessageView(
                title: "Unable to Add Credentials",
                message: message,
                icon: "xmark.circle.fill",
                iconColor: .red
            )
            .padding()
            
            Spacer()
            
            Divider()
            
            Button("Close", action: onDismiss)
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
                .frame(maxWidth: .infinity)
                .padding()
        }
    }
    
    private func transactionCodeContent(challenge: TransactionCodeChallenge) -> some View {
        TransactionCodeInputView(
            challenge: challenge,
            onSubmit: onSubmitTransactionCode,
            onCancel: onDismiss
        )
    }
}

// MARK: - Transaction Code Input

/// View for entering a transaction code (PIN) during credential issuance.
/// LIMITATION: Does not support biometric authentication as an alternative.
private struct TransactionCodeInputView: View {
    let challenge: TransactionCodeChallenge
    let onSubmit: (String) -> Void
    let onCancel: () -> Void

    @State private var code: String = ""
    @FocusState private var isFocused: Bool

    private var description: String {
        challenge.details.description_ ?? "Enter the transaction code to complete issuance."
    }

    private var expectedLength: Int? {
        challenge.details.length?.intValue
    }

    private var inputMode: String? {
        challenge.details.inputMode?.value
    }

    /// Whether the code meets the expected length (if specified).
    private var isValidLength: Bool {
        guard let length = expectedLength else { return !code.isEmpty }
        return code.count == length
    }

    var body: some View {
        VStack(spacing: 0) {
            ScrollView {
                VStack(spacing: 24) {
                    // Header icon
                    Image(systemName: "lock.shield.fill")
                        .font(.system(size: 48))
                        .foregroundStyle(.orange)
                        .symbolRenderingMode(.hierarchical)
                        .padding(.top, 24)

                    VStack(spacing: 8) {
                        Text("Transaction Code Required")
                            .font(.headline)

                        Text(description)
                            .font(.subheadline)
                            .foregroundStyle(.secondary)
                            .multilineTextAlignment(.center)
                    }
                    .padding(.horizontal)

                    // Code input field
                    VStack(alignment: .leading, spacing: 8) {
                        if inputMode == "numeric" {
                            TextField("Enter code", text: $code)
                                .keyboardType(.numberPad)
                                .textContentType(.oneTimeCode)
                                .font(.title2.monospaced())
                                .multilineTextAlignment(.center)
                                .padding()
                                .background(Color(.secondarySystemBackground))
                                .clipShape(RoundedRectangle(cornerRadius: 12))
                                .focused($isFocused)
                        } else {
                            TextField("Enter code", text: $code)
                                .textContentType(.oneTimeCode)
                                .font(.title2.monospaced())
                                .multilineTextAlignment(.center)
                                .padding()
                                .background(Color(.secondarySystemBackground))
                                .clipShape(RoundedRectangle(cornerRadius: 12))
                                .focused($isFocused)
                        }

                        if let length = expectedLength {
                            Text("\(code.count)/\(length) characters")
                                .font(.caption)
                                .foregroundStyle(.secondary)
                                .frame(maxWidth: .infinity, alignment: .trailing)
                        }
                    }
                    .padding(.horizontal)
                }
            }

            // Bottom action bar
            VStack(spacing: 12) {
                Divider()

                Button(action: { onSubmit(code) }) {
                    Text("Submit")
                        .frame(maxWidth: .infinity)
                }
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
                .disabled(!isValidLength)

                Button("Cancel", action: onCancel)
                    .buttonStyle(.plain)
                    .foregroundStyle(.secondary)
            }
            .padding(.horizontal)
            .padding(.bottom, 8)
            .background(Color(.systemBackground))
        }
        .onAppear {
            isFocused = true
        }
    }
}

