//
//  AppSettings.swift
//  iProov Identity Example App
//

import Foundation

class AppSettings: ObservableObject {
    static let shared = AppSettings()

    private let defaults = UserDefaults.standard
    private static let preferAuthorizationCodeKey = "preferAuthorizationCode"

    @Published var preferAuthorizationCode: Bool {
        didSet {
            defaults.set(preferAuthorizationCode, forKey: Self.preferAuthorizationCodeKey)
        }
    }

    private init() {
        self.preferAuthorizationCode = defaults.bool(forKey: Self.preferAuthorizationCodeKey)
    }
}
