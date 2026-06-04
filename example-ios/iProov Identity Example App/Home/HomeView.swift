//
//  HomeView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 19/12/2024.
//

import SwiftUI
import identity

enum OpenIdUrlRoute {
    case credentialOffer
    case presentation
    case proximityRetrieval
}

enum OpenIdSchemeSupport {
    static let credentialOfferSchemes: Set<String> = ["openid-credential-offer", "haip-vci"]
    static let presentationSchemes: Set<String> = ["openid4vp", "eudi-openid4vp", "haip-vp", "haip-vc"]

    static func route(for url: URL) -> OpenIdUrlRoute? {
        route(forScheme: url.scheme)
    }

    static func route(forScheme scheme: String?) -> OpenIdUrlRoute? {
        let normalized = scheme?.lowercased() ?? ""

        if normalized == "mdoc" {
            return .proximityRetrieval
        }

        if credentialOfferSchemes.contains(normalized) {
            return .credentialOffer
        }

        if presentationSchemes.contains(normalized) {
            return .presentation
        }

        return nil
    }
}

struct HomeView: View {
    @StateObject private var viewModel: HomeViewModel
    @State private var pendingPresentationUri: String? = nil
    @State private var pendingCredentialOfferUri: String? = nil

    init(wallet: Wallet) {
        _viewModel = StateObject(wrappedValue: HomeViewModel(wallet: wallet))
    }

    var body: some View {
        NavigationStack {
            content
                .navigationTitle("iProov Identity")
                .background(Color(.systemGroupedBackground))
        }
        .onAppear {
            viewModel.load()
        }
        .onOpenURL { url in
            handleOpenURL(url)
        }
    }

    private func handleOpenURL(_ url: URL) {
        switch OpenIdSchemeSupport.route(for: url) {
        case .credentialOffer:
            pendingCredentialOfferUri = url.absoluteString
        case .presentation:
            pendingPresentationUri = url.absoluteString
        case .proximityRetrieval:
            pendingPresentationUri = url.absoluteString
        case nil:
            return
        }
    }

    @ViewBuilder
    private var content: some View {
        switch viewModel.state {
        case .loading:
            LoadingContent()

        case .notRegistered:
            NotRegisteredContent(onRegister: {
                Task { await viewModel.register() }
            })

        case .registered:
            RegisteredView(
                deleteWallet: { Task { await viewModel.deleteWallet() } },
                pendingPresentationUri: $pendingPresentationUri,
                pendingCredentialOfferUri: $pendingCredentialOfferUri
            )

        case .error(let message):
            ErrorContent(reason: message, onRetry: viewModel.retry)
        }
    }
}

// MARK: - Loading State

private struct LoadingContent: View {
    var body: some View {
        VStack(spacing: 16) {
            ProgressView()
                .controlSize(.large)
            Text("Loading...")
                .font(.subheadline)
                .foregroundStyle(.secondary)
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity)
    }
}

// MARK: - Not Registered State

private struct NotRegisteredContent: View {
    let onRegister: () -> Void

    var body: some View {
        VStack(spacing: 24) {
            Spacer()

            Image(systemName: "wallet.pass")
                .font(.system(size: 64))
                .foregroundStyle(.tint)
                .symbolRenderingMode(.hierarchical)

            VStack(spacing: 8) {
                Text("Welcome to iProov Identity")
                    .font(.title2.weight(.semibold))

                Text("Register your wallet to start adding credentials and verifying your identity.")
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .multilineTextAlignment(.center)
                    .padding(.horizontal, 32)
            }

            Spacer()

            Button(action: onRegister) {
                Text("Register Wallet")
                    .frame(maxWidth: .infinity)
            }
            .buttonStyle(.borderedProminent)
            .controlSize(.large)
            .padding(.horizontal)
            .padding(.bottom)
        }
    }
}
