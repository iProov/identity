//
//  HomeViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 16/01/2025.
//

import Foundation
import identity

struct HomeViewLoaded {
    let isRegistered: Bool
    let credentials: [identity.Credential]
    
}

class HomeViewModel: ObservableObject{
    enum State : Equatable {
        case loading
        case notRegistered
        case registered
        case error(String)
    }

    @Published var state: State = State.loading
    let wallet: identity.Wallet
    
    init(wallet: Wallet) {
        self.wallet = wallet
    }
    
    func load(){self.state = getInitialSate()}
    
    func getInitialSate() -> State {
        if (!wallet.isRegistered) {return State.notRegistered}
        
        return State.registered
    }
    
    func register() async {
        await MainActor.run{state = State.loading}
        
        do {
            try self.wallet.destroy()
            try await self.wallet.register()
            await MainActor.run{self.state = .registered}
        }
        catch let exception {
            await MainActor.run{self.state = .error(exception.localizedDescription)}
        }
    }
    
    func deleteWallet() async {
        await MainActor.run{state = State.loading}
        
        do {
            try await self.wallet.delete()
            await MainActor.run{self.state = getInitialSate()}
        }
        catch  {
            print("Failed to delete / revoke wallet \(error.localizedDescription)")
            print("Destroying wallet instead")
            do {
                try self.wallet.destroy()
                await MainActor.run{self.state = getInitialSate()}
            }
            catch let destroyException {
                await MainActor.run{self.state = .error(destroyException.localizedDescription)}
            }
        
        }
    }
    
}
