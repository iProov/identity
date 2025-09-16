//
//  ContentView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 19/12/2024.
//

import SwiftUI
import identity

struct HomeView: View {

    @ObservedObject var viewModel: HomeViewModel
    @State var isShowingSheet: Bool = false
    @State private var isPresentingConfirm: Bool = false
    @State var path: NavigationPath = NavigationPath()

    init(wallet: Wallet) {
        viewModel = HomeViewModel(wallet: wallet)
    }

    var body: some View {
        NavigationStack(path: $path) {
            content
                .navigationBarTitle("iProov Identity")
                .background(.background.secondary)
        }.onAppear {
            viewModel.load()
        }.background(.background.secondary)
    }

    @ViewBuilder
    var content: some View {
        switch viewModel.state {
        case .registered:
            RegisteredView(deleteWallet: { Task { await viewModel.deleteWallet() } })
        case .loading:
            ProgressView().progressViewStyle(.circular)
        case .notRegistered:
            Button("Register") { Task { await viewModel.register() } }
        case .error(let error):
            ErrorContent(reason: error)
        }
    }
}
