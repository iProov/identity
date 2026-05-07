//
//  SettingsView.swift
//  iProov Identity Example App
//

import SwiftUI

struct SettingsView: View {
    @ObservedObject private var settings = AppSettings.shared

    var body: some View {
        Form {
            Section {
                Toggle("Prefer Authorization Code Flow", isOn: $settings.preferAuthorizationCode)
            } footer: {
                Text("When enabled, the authorization code flow will be used instead of the pre-authorized code flow when both are available.")
            }
        }
        .navigationTitle("Settings")
    }
}
