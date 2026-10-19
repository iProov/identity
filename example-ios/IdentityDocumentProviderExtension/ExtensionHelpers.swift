//
//  ExtensionHelpers.swift
//  iProov Identity Example App
//
//  Created by Owen Woodward on 27/08/2026.
//


import Foundation

enum ExtensionHelpers {


    // MARK: Display names

    /// Minimal ISO 18013-5 element labels. A real implementation should localise these and
    /// cover org.iso.23220 / EUDI PID namespaces too.

    static func displayName(for element: String) -> String {
        switch element {
        case "family_name":         return "Family name"
        case "given_name":          return "Given name"
        case "birth_date":          return "Date of birth"
        case "issue_date":          return "Issue date"
        case "expiry_date":         return "Expiry date"
        case "issuing_country":     return "Issuing country"
        case "issuing_authority":   return "Issuing authority"
        case "document_number":     return "Document number"
        case "portrait":            return "Photo"
        case "driving_privileges":  return "Driving privileges"
        case "sex":                 return "Sex"
        case "resident_address":    return "Address"
        case "resident_city":       return "City"
        case "resident_state":      return "State"
        case "resident_postal_code": return "Postcode"
        case "resident_country":    return "Country"
        case let e where e.hasPrefix("age_over_"):
            return "Age over \(e.dropFirst("age_over_".count))"
        default:
            return element.replacingOccurrences(of: "_", with: " ").capitalized
        }
    }

    static func documentDisplayName(_ docType: String) -> String {
        switch docType {
        case "org.iso.18013.5.1.mDL":   return "Driving licence"
        case "eu.europa.ec.eudi.pid.1": return "Personal ID"
        case "org.iso.23220.photoid.1": return "Photo ID"
        default:                        return docType
        }
    }
}
