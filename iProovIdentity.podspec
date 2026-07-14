Pod::Spec.new do |s|
  s.name             = 'iProovIdentity'
  s.version          = '0.4.1'
  s.summary          = 'iProov Identity SDK — digital identity wallet (OID4VCI / OID4VP, ISO/IEC 18013-5).'
  s.description      = <<-DESC
    The iProov Identity SDK provides a digital identity wallet: OID4VCI credential
    issuance, OID4VP presentation, the Digital Credentials API, and ISO/IEC 18013-5
    proximity (BLE) presentation and reading. Consumers `import identity`.
  DESC
  s.homepage         = 'https://github.com/iProov/identity'
  s.license          = { :type => 'Commercial', :file => 'LICENSE.md' }
  s.author           = { 'iProov' => 'support@iproov.com' }

  s.platform         = :ios, '16.0'
  s.swift_version    = '5.9'

  # Same release artifact as the SwiftPM binaryTarget — CocoaPods downloads and unzips it.
  # The zip must contain `identity.xcframework` at its root (see buildXCFramework in
  # identity/build.gradle.kts).
  s.source = {
    :http => 'https://github.com/iProov/identity/releases/download/0.4.1/identity.xcframework.zip'
  }
  s.vendored_frameworks = 'identity.xcframework'

  # Runtime dependencies — mirror the `cocoapods { }` block in identity/build.gradle.kts.
  s.dependency 'iProov'
  s.dependency 'JOSESwift', '3.0.0'
end
