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
    
    var body: some View {
        VStack(spacing: 20) {
            Spacer()

            Image(systemName: "exclamationmark.triangle.fill")
                .font(.system(size: 60))
                .foregroundColor(.red)
            
            Text("Oops! Something went wrong.")
                .font(.title)
                .multilineTextAlignment(.center)
                .bold()
            
            Text(reason)
                .font(.body)
                .foregroundColor(.gray)
                .multilineTextAlignment(.center)
                .padding(.horizontal)
            
            Spacer()
        }
        .padding()
    }
}
