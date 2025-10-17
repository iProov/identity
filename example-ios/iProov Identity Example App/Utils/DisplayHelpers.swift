import Foundation
import SwiftUI
import identity

enum DisplaySelector {

    static func select(from displays: [DisplayProperties]) -> DisplayProperties? {
        guard !displays.isEmpty else { return nil }
        let locale = Locale.current
        let identifier = locale.identifier.lowercased()
        let language = locale.languageCode?.lowercased()

        var fallback: DisplayProperties? = displays.first

        for display in displays {
            guard let localeCode = display.locale?.lowercased() else { continue }
            if localeCode == identifier { return display }
            if let language, localeCode.hasPrefix(language) { fallback = display }
        }

        return fallback
    }

    static func select(from map: NSDictionary?) -> DisplayProperties? {
        guard let map else { return nil }

        var localeMap: [String: DisplayProperties] = [:]
        map.forEach { key, value in
            guard let localeKey = (key as? String)?.lowercased(),
                  let display = value as? DisplayProperties else { return }
            localeMap[localeKey] = display
        }

        return select(from: localeMap)
    }

    static func select(from map: [String: DisplayProperties]) -> DisplayProperties? {
        guard !map.isEmpty else { return nil }

        let locale = Locale.current
        let identifier = locale.identifier.lowercased()
        if let exact = map[identifier] { return exact }

        if let language = locale.languageCode?.lowercased() {
            if let match = map.first(where: { $0.key.hasPrefix(language) }) {
                return match.value
            }
        }

        if let global = map[""] { return global }

        return map.values.first
    }
}

extension CredentialMetadata {
    var bestDisplay: DisplayProperties? {
        DisplaySelector.select(from: display)
    }
}

extension CredentialDescriptor {
    var bestDisplay: DisplayProperties? {
        if let map = display as? [String: DisplayProperties] {
            return DisplaySelector.select(from: map.mapKeys { $0.lowercased() })
        }
        return DisplaySelector.select(from: display as NSDictionary)
    }
}

extension CredentialIssuer {
    var bestDisplay: DisplayProperties? {
        guard let display else { return nil}
        
        let displaysEasy = display.map{ (key: AnyHashable, value: DisplayProperties) in
                value
        }
        
        return DisplaySelector.select(from: displaysEasy)
    }
}

extension Dictionary {
    fileprivate func mapKeys<T>(_ transform: (Key) -> T) -> [T: Value] where T: Hashable {
        reduce(into: [:]) { result, element in
            result[transform(element.key)] = element.value
        }
    }
}

extension DisplayProperties {
    var backgroundSwiftColor: Color? {
        guard let hex = backgroundColor, let color = Color(hex: hex) else { return nil }
        return color
    }

    var textSwiftColor: Color? {
        guard let hex = textColor, let color = Color(hex: hex) else { return nil }
        return color
    }
}

extension Color {
    init?(hex: String) {
        var normalized = hex.trimmingCharacters(in: CharacterSet.alphanumerics.inverted)
        if normalized.count == 3 {
            normalized = normalized.reduce("") { acc, char in acc + String(repeating: char, count: 2) }
        }

        guard normalized.count == 6,
              let int = Int(normalized, radix: 16) else { return nil }

        let red = Double((int >> 16) & 0xFF) / 255.0
        let green = Double((int >> 8) & 0xFF) / 255.0
        let blue = Double(int & 0xFF) / 255.0

        self.init(red: red, green: green, blue: blue)
    }
}
