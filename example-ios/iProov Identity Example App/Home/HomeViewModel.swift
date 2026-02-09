//
//  HomeViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 16/01/2025.
//

import Foundation
import identity

@MainActor
class HomeViewModel: ObservableObject {
    enum State: Equatable {
        case loading
        case notRegistered
        case registered
        case error(String)
    }

    @Published private(set) var state: State = .loading

    let wallet: Wallet

    init(wallet: Wallet) {
        self.wallet = wallet
    }

    func load() {
        state = checkRegistrationState()
    }

    func register() async {
        state = .loading

        do {
            try await wallet.destroy()
            try await wallet.register()
            state = .registered
        } catch {
            state = .error(error.localizedDescription)
        }
    }

    func deleteWallet() async {
        state = .loading

        do {
            try await wallet.delete()
            state = checkRegistrationState()
        } catch {
            // If delete fails (e.g., network error), fall back to local destroy
            print("Failed to delete wallet: \(error.localizedDescription)")
            print("Destroying wallet locally instead")
            do {
                try await wallet.destroy()
                state = checkRegistrationState()
            } catch {
                state = .error(error.localizedDescription)
            }
        }
    }

    /// Retry loading after an error.
    func retry() {
        load()
    }

    private func checkRegistrationState() -> State {
        do {
            return try wallet.isRegistered() ? .registered : .notRegistered
        } catch {
            return .error(error.localizedDescription)
        }
    }
}
