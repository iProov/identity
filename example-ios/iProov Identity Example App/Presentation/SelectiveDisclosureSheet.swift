//
//  SelectiveDisclosureSheet.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 28/01/2025.
//

import Foundation
import identity
import SwiftUI

struct SelectiveDisclosureSheet: View {
    
    @ObservedObject var viewModel: SelectiveDisclosureViewModel
    let dismissSheet: () -> Void
    @State var path = NavigationPath()
    
    init(loginRequest: RespondableLoginRequest, dismissSheet: @escaping () -> Void ) {
        self.viewModel = SelectiveDisclosureViewModel(loginRequest:loginRequest)
        self.dismissSheet = dismissSheet
    }

    var body: some View{
        NavigationStack(path: $path){
            VStack(alignment: .leading){
                HeaderView(relyingPartyName: viewModel.loginRequest.relyingParty.name)
                
                if viewModel.isLoading {
                    ProgressView()
                } else {
                    List{
                        RequiredClaimsSection(
                            viewModel: viewModel,
                            onAddClaim: { path.append($0) }
                        )
                        
                        OptionalClaimsSection(viewModel: viewModel)
                        
                        ReverificationsSection(reverifications: viewModel.loginRequest.reverifications)
                        
                    }
                    .safeAreaInset(edge: VerticalEdge.bottom) {
                        ShareButton(
                            canShare: viewModel.canShare,
                            hasReverifications: !viewModel.loginRequest.reverifications.isEmpty,
                            action: shareInformation
                        )
                    }
                    .background(.background.secondary)
                }
            }
            .background(.background.secondary)
            .navigationDestination(for: CredentialType.self) { type in
                view(for: type)
            }
        }
        .onAppear {
            viewModel.load()
        }
        .background(.background.secondary)
    }

    private func shareInformation() {
        Task {
            do {
                let response = try await viewModel.loginRequest.accept(claims: viewModel.claimsToShare.values.sorted())
                print(String(describing:response))
            } catch let exception {
                print("Failed to share information \(exception.localizedDescription)")
            }
        }
    }

    @ViewBuilder
    private func view(for type: CredentialType?) -> some View {
      switch type {
      case .Document:
          AddDocumentView(path: $path, loginRequest: nil) {
              path.removeLast()
              viewModel.load()
          }
      case .Phone:
          AddPhoneView() {
              path.removeLast()
              viewModel.load()
          }
      case .Email:
          AddEmailView(path: $path) {
              path.removeLast()
              viewModel.load()
          }
      default:
        EmptyView()
      }
    }
}

// MARK: - Subviews

private struct HeaderView: View {
    let relyingPartyName: String
    
    var body: some View {
        VStack(alignment: .leading) {
            Text("Incoming Share Request")
                .font(.title)
                .padding()
                .padding(.top)
            
            Text("\(relyingPartyName) has requested the following information from you")
                .font(.body)
                .padding(.horizontal)
        }
    }
}

private struct RequiredClaimsSection: View {
    @ObservedObject var viewModel: SelectiveDisclosureViewModel
    let onAddClaim: (CredentialType) -> Void
    
    var body: some View {
        Section {
            ForEach(viewModel.loginRequest.claims.filter { $0.isEssential }) { requestedClaim in
                ClaimView(
                    viewModel: viewModel,
                    claim: requestedClaim
                )
            }
            
            ForEach(viewModel.requiredClaimsNotBeingShared) { type in
                if let credentialType = type.source {
                    Label(String(describing: credentialType), systemImage: "plus")
                        .onTapGesture { onAddClaim(credentialType) }
                }
            }
        } header: {
            Text("Required Fields")
        } footer: {
            if !viewModel.canShare {
                Text("All required fields must be provided before you can share.")
                    .foregroundStyle(.red)
            }
        }
    }
}

private struct OptionalClaimsSection: View {
    @ObservedObject var viewModel: SelectiveDisclosureViewModel
    
    var body: some View {
        let optionalClaims = viewModel.loginRequest.claims.filter { !$0.isEssential }
        if !optionalClaims.isEmpty {
            Section {
                ForEach(optionalClaims) { requestedClaim in
                    ClaimView(
                        viewModel: viewModel,
                        claim: requestedClaim
                    )
                }
            } header: {
                Text("Optional claims")
            }
        }
    }
}

private struct ReverificationsSection: View {
    let reverifications: [ReverificationRequest]
    
    var body: some View {
        if !reverifications.isEmpty {
            Section {
                ForEach(reverifications) { reverification in
                    Text(String(describing: reverification))
                }
            } header: {
                Text("Reverifications")
            }
        }
    }
}

private struct ShareButton: View {
    let canShare: Bool
    let hasReverifications: Bool
    let action: () -> Void
    
    var body: some View {
        Button(hasReverifications ? "Perform reverifications" : "Share information", action: action)
            .controlSize(.large)
            .buttonStyle(.borderedProminent)
            .disabled(!canShare)
    }
}

private struct ClaimView: View {
    @ObservedObject var viewModel: SelectiveDisclosureViewModel
    let claim: RequestedClaim
    
    private var isSharing: Binding<Bool> {
        Binding(
            get: { viewModel.claimsToShare[claim.name] != nil },
            set: { isSharing in
                if isSharing {
                    viewModel.claimsToShare[claim.name] = viewModel.claimsInWallet[claim.name]
                } else {
                    viewModel.claimsToShare.removeValue(forKey: claim.name)
                }
            }
        )
    }
    
    private var isInWallet: Bool { viewModel.claimsInWallet[claim.name] != nil }
    private var icon: String { isInWallet ? "checkmark.circle.fill" : "exclamationmark.circle.fill" }
    private var iconColor: Color { isInWallet ? .green : .red }
    
    var body: some View {
        Toggle(isOn: isSharing) {
            Label(claim.displayName ?? claim.name, systemImage: icon)
                .labelStyle(CustomLabelStyle(iconColor: iconColor, titleColor: .black))
        }
        .disabled(!isInWallet)
    }
    
    struct CustomLabelStyle: LabelStyle {
        let iconColor: Color
        let titleColor: Color
        
        func makeBody(configuration: Configuration) -> some View {
            HStack {
                configuration.icon
                    .foregroundColor(iconColor)
                
                configuration.title
                    .foregroundColor(titleColor)
                    .padding(.leading, 10)
                    .lineLimit(1)
            }
        }
    }
}

// MARK: - Extensions

extension RequestedClaim: Identifiable {}

extension ReverificationRequest: Identifiable {}
