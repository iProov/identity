//
//  HomeView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 19/12/2024.
//

import SwiftUI
import identity

struct HomeView: View {
    @StateObject private var viewModel: HomeViewModel

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
            RegisteredView(deleteWallet: {
                Task { await viewModel.deleteWallet() }
            })

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
