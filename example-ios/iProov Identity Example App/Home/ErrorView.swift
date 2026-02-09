//
//  ErrorView.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 16/01/2025.
//

import Foundation
import SwiftUI

struct ErrorContent: View {
    let reason: String
    var onRetry: (() -> Void)? = nil

    var body: some View {
        VStack(spacing: 24) {
            Spacer()

            Image(systemName: "exclamationmark.triangle.fill")
                .font(.system(size: 56))
                .foregroundStyle(.red)
                .symbolRenderingMode(.hierarchical)

            VStack(spacing: 8) {
                Text("Something went wrong")
                    .font(.title2.weight(.semibold))

                Text(reason)
                    .font(.subheadline)
                    .foregroundStyle(.secondary)
                    .multilineTextAlignment(.center)
                    .padding(.horizontal, 32)
            }

            Spacer()

            if let onRetry {
                Button(action: onRetry) {
                    Label("Try Again", systemImage: "arrow.clockwise")
                        .frame(maxWidth: .infinity)
                }
                .buttonStyle(.borderedProminent)
                .controlSize(.large)
                .padding(.horizontal)
                .padding(.bottom)
            }
        }
    }
}
