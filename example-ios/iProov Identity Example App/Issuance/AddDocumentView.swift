//
//  AddDocumentView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 31/01/2025.
//

import SwiftUI
import identity
import MRZScanner

// MARK: - Main View

struct AddDocumentView: View {
    @StateObject private var viewModel: AddDocumentViewModel
    @Binding var path: NavigationPath
    @State private var isScanningMrz = false
    
    init(path: Binding<NavigationPath>, loginRequest: LoginRequest?, completion: @escaping () -> Void) {
        _path = path
        _viewModel = StateObject(wrappedValue: AddDocumentViewModel(loginRequest: loginRequest, completion: completion))
    }
    
    var body: some View {
        ScrollView {
            VStack(spacing: 24) {
                DocumentScanHeader()
                
                ScanStepsView()
                
                SecurityInfoView()
            }
            .padding()
        }
        .safeAreaInset(edge: .bottom) {
            ActionButtonsView(
                isLoading: viewModel.isLoading,
                onStartScanning: { isScanningMrz = true },
                onScanCredentialOffer: { viewModel.isScanningCredentialOffer = true },
                onAddDemo: viewModel.addDemoDocument
            )
        }
        .navigationTitle("Add Document")
        .navigationBarTitleDisplayMode(.large)
        .navigationBarBackButtonHidden(viewModel.isLoading)
        .sheet(isPresented: $isScanningMrz) {
            MrzCaptureView { result in
                isScanningMrz = false
                viewModel.readDocument(from: result.result)
            }
        }
        .sheet(isPresented: $viewModel.isScanningCredentialOffer) {
            ScanQrCodeSheet(
                dismiss: { viewModel.isScanningCredentialOffer = false },
                onQrScanned: viewModel.handleCredentialOfferQrCode
            )
        }
        .alert(item: $viewModel.failure) { error in
            Alert(
                title: Text(error.title),
                message: Text(error.message),
                dismissButton: .default(Text("OK"))
            )
        }
        .sheet(item: $viewModel.offerSheet) { sheet in
            CredentialOfferSheet(
                state: sheet,
                onToggleSelection: viewModel.toggleCredentialSelection,
                onConfirm: viewModel.confirmCredentialSelection,
                onSubmitTransactionCode: viewModel.submitTransactionCode,
                onDismiss: viewModel.dismissOfferSheet
            )
        }
        .interactiveDismissDisabled(viewModel.isLoading)
    }
}

// MARK: - Header

/// Visual header explaining the document addition process.
/// LIMITATION: Static illustration - no dynamic document type detection.
private struct DocumentScanHeader: View {
    var body: some View {
        VStack(spacing: 16) {
            // Document illustration
            ZStack {
                RoundedRectangle(cornerRadius: 12)
                    .fill(Color(.tertiarySystemBackground))
                    .frame(width: 120, height: 80)
                
                Image(systemName: "doc.text.viewfinder")
                    .font(.system(size: 36))
                    .foregroundStyle(.tint)
                    .symbolRenderingMode(.hierarchical)
            }
            .accessibilityHidden(true)
            
            Text("Scan your identity document to add it securely to your wallet.")
                .font(.subheadline)
                .foregroundStyle(.secondary)
                .multilineTextAlignment(.center)
                .fixedSize(horizontal: false, vertical: true)
        }
        .frame(maxWidth: .infinity)
        .padding(.vertical, 8)
    }
}

// MARK: - Scan Steps

/// Displays the sequential steps for document scanning.
/// LIMITATION: Step order is fixed - does not adapt to document types
/// that may not require NFC (e.g., some national IDs).
private struct ScanStepsView: View {
    var body: some View {
        VStack(alignment: .leading, spacing: 0) {
            SectionHeader(title: "How it works")
            
            VStack(spacing: 0) {
                ScanStepRow(
                    step: 1,
                    icon: "camera.viewfinder",
                    title: "Scan MRZ",
                    description: "Point your camera at the Machine Readable Zone on your document",
                    isLast: false
                )
                
                ScanStepRow(
                    step: 2,
                    icon: "wave.3.right",
                    title: "Read NFC Chip",
                    description: "Hold your device against the document to read its secure chip",
                    isLast: false
                )
                
                ScanStepRow(
                    step: 3,
                    icon: "checkmark.shield",
                    title: "Verify & Add",
                    description: "Review the credential and add it to your wallet",
                    isLast: true
                )
            }
            .background(Color(.secondarySystemBackground))
            .clipShape(RoundedRectangle(cornerRadius: 12))
        }
    }
}

private struct SectionHeader: View {
    let title: String
    
    var body: some View {
        Text(title)
            .font(.subheadline.weight(.semibold))
            .foregroundStyle(.secondary)
            .textCase(.uppercase)
            .padding(.horizontal, 4)
            .padding(.bottom, 8)
    }
}

/// Individual step row with connector line to next step.
private struct ScanStepRow: View {
    let step: Int
    let icon: String
    let title: String
    let description: String
    let isLast: Bool
    
    var body: some View {
        HStack(alignment: .top, spacing: 14) {
            // Step indicator with connector
            VStack(spacing: 0) {
                ZStack {
                    Circle()
                        .fill(Color.accentColor.opacity(0.15))
                        .frame(width: 40, height: 40)
                    
                    Image(systemName: icon)
                        .font(.system(size: 16, weight: .semibold))
                        .foregroundStyle(.tint)
                }
                
                if !isLast {
                    Rectangle()
                        .fill(Color.accentColor.opacity(0.3))
                        .frame(width: 2)
                        .frame(maxHeight: .infinity)
                }
            }
            .frame(width: 40)
            
            // Content
            VStack(alignment: .leading, spacing: 4) {
                Text(title)
                    .font(.body.weight(.medium))
                
                Text(description)
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .fixedSize(horizontal: false, vertical: true)
            }
            .padding(.bottom, isLast ? 0 : 20)
            
            Spacer(minLength: 0)
        }
        .padding(.horizontal, 16)
        .padding(.top, 16)
        .padding(.bottom, isLast ? 16 : 0)
        .accessibilityElement(children: .combine)
        .accessibilityLabel("Step \(step): \(title). \(description)")
    }
}

// MARK: - Security Info

/// Displays security and privacy information about the scanning process.
/// Important for user trust in biometric/identity applications.
private struct SecurityInfoView: View {
    var body: some View {
        VStack(alignment: .leading, spacing: 12) {
            SectionHeader(title: "Security")
            
            VStack(spacing: 10) {
                SecurityFeatureRow(
                    icon: "lock.shield.fill",
                    text: "Document data is encrypted and stored securely on your device"
                )
                
                SecurityFeatureRow(
                    icon: "antenna.radiowaves.left.and.right.slash",
                    text: "NFC reading requires physical proximity to your document"
                )
                
                SecurityFeatureRow(
                    icon: "eye.slash.fill",
                    text: "Your biometric data never leaves your device"
                )
            }
            .padding(16)
            .background(Color(.secondarySystemBackground))
            .clipShape(RoundedRectangle(cornerRadius: 12))
        }
    }
}

private struct SecurityFeatureRow: View {
    let icon: String
    let text: String
    
    var body: some View {
        HStack(alignment: .top, spacing: 12) {
            Image(systemName: icon)
                .font(.body)
                .foregroundStyle(.green)
                .frame(width: 24)
            
            Text(text)
                .font(.subheadline)
                .foregroundStyle(.secondary)
                .fixedSize(horizontal: false, vertical: true)
            
            Spacer(minLength: 0)
        }
        .accessibilityElement(children: .combine)
    }
}

// MARK: - Action Buttons

/// Bottom action bar with primary scan action, credential offer scan, and demo option.
/// LIMITATION: Demo button visibility should ideally be controlled
/// by build configuration (DEBUG only) but is shown for development.
private struct ActionButtonsView: View {
    let isLoading: Bool
    let onStartScanning: () -> Void
    let onScanCredentialOffer: () -> Void
    let onAddDemo: () -> Void

    var body: some View {
        VStack(spacing: 12) {
            Divider()

            if isLoading {
                LoadingStateView()
            } else {
                VStack(spacing: 12) {
                    Button(action: onStartScanning) {
                        Label("Start Scanning Document", systemImage: "document.viewfinder")
                            .frame(maxWidth: .infinity)
                    }
                    .buttonStyle(.borderedProminent)
                    .controlSize(.large)

                    Button(action: onScanCredentialOffer) {
                        Label("Scan Credential Offer", systemImage: "qrcode.viewfinder")
                            .frame(maxWidth: .infinity)
                    }
                    .buttonStyle(.bordered)
                    .controlSize(.large)

                    #if DEBUG
                    // LIMITATION: Demo document only available in debug builds.
                    // Remove or gate this for production releases.
                    Button(action: onAddDemo) {
                        Text("Add Demo Document")
                            .font(.subheadline)
                    }
                    .buttonStyle(.plain)
                    .foregroundStyle(.secondary)
                    #endif
                }
            }
        }
        .padding(.horizontal)
        .padding(.bottom, 8)
        .background(Color(.systemBackground))
    }
}

/// Loading state shown during document processing.
/// Provides user feedback during NFC reading which can take several seconds.
private struct LoadingStateView: View {
    @State private var dots = ""
    
    var body: some View {
        VStack(spacing: 12) {
            HStack(spacing: 12) {
                ProgressView()
                    .controlSize(.regular)
                
                Text("Processing document\(dots)")
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .frame(width: 160, alignment: .leading)
            }
            .frame(height: 50)
            
            Text("Keep your document in place")
                .font(.caption)
                .foregroundStyle(.tertiary)
        }
        .frame(maxWidth: .infinity)
        .onAppear {
            animateDots()
        }
    }
    
    /// Animates loading dots for visual feedback during long operations.
    /// LIMITATION: Simple timer-based animation - could use smoother
    /// animation approach for more polished feel.
    private func animateDots() {
        Timer.scheduledTimer(withTimeInterval: 0.5, repeats: true) { timer in
            if dots.count >= 3 {
                dots = ""
            } else {
                dots += "."
            }
        }
    }
}

// MARK: - Preview

#Preview("Add Document") {
    NavigationStack {
        AddDocumentView(
            path: .constant(NavigationPath()),
            loginRequest: nil,
            completion: {}
        )
    }
}

#Preview("Loading State") {
    NavigationStack {
        AddDocumentView(
            path: .constant(NavigationPath()),
            loginRequest: nil,
            completion: {}
        )
    }
}
