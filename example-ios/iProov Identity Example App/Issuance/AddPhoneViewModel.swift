//
//  AddPhoneViewModel.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 04/07/2025.
//

import Foundation
import SwiftUI
import identity

@MainActor
class AddPhoneViewModel: ObservableObject {
    @Published var phoneNumber = ""
    @Published var otp = ""
    @Published var isShowingOtpView = false
    @Published var isLoading = false
    @Published var alert: AlertDialog? = nil
    
    private var challenge: UriCredentialChallenge?
    private let completion: () -> Void
    
    private let wallet = WalletFactory.shared.instance!
    
    init(completion: @escaping () -> Void) {
        self.completion = completion
    }
    
    /// Initiates the process of adding a phone number by sending a request to the wallet.
    func addPhoneNumber() {
        isLoading = true
        
        wallet.addUriCredential(uri: "sms:\(phoneNumber)", completionHandler: {[weak self] challenge, error in
            guard let self = self else { return }
            self.isLoading = false
            
            if let error {
                alert = AlertDialog(title: "Failed to add phone number", message: error.localizedDescription)
                return
            }
            
            isShowingOtpView = true
            if let challenge {
                self.challenge = challenge
            }
        })
    }
    
    /// Confirms the OTP code to complete the phone number addition.
    func confirmOtp() {
        isLoading = true
        
        if let challenge {
            challenge.respond!.withToken(token: otp) {[weak self] _,  error in
                DispatchQueue.main.async {
                    guard let self = self else { return }
                    self.isLoading = false
                    self.otp = ""
                    
                    if let error {
                        self.alert = AlertDialog(title: "Failed to confirm OTP", message: error.localizedDescription)
                    }
                    else {
                        self.alert = AlertDialog(title: "Successful", message: "Phone number has been added successfully.")
                        self.completion()
                    }
                }
            }
        } else {
            wallet.verifyUriCredential(uri: "sms:\(phoneNumber)", token: otp) { [weak self] error in
                DispatchQueue.main.async {
                    guard let self = self else { return }
                    self.isLoading = false
                    self.otp = ""
                    
                    if let error {
                        self.alert = AlertDialog(title: "Failed to confirm OTP", message: error.localizedDescription)
                    }
                    else {
                        self.alert = AlertDialog(title: "Successful", message: "Phone number has been added successfully.")
                        self.completion()
                    }
                }
                
            }
        }
    }
    
    /// Resets the OTP state when the confirmation view is cancelled.
    func cancelOtp() {
        otp = ""
        challenge = nil
    }
}
