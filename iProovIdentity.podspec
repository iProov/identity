Pod::Spec.new do |s|
  s.name             = 'iProovIdentity'
  s.version          = '0.5.1'
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

  # CocoaPods downloads the XCFramework together with the native Swift overlay.
  # Both `iProovIdentity.xcframework` and `Sources/identity` are at the archive root
  # (see buildXCFramework in identity/build.gradle.kts).
  s.source = {
    :http => 'https://github.com/iProov/identity/releases/download/0.5.1/iProovIdentity.pod.zip'
  }
  s.vendored_frameworks = 'iProovIdentity.xcframework'
  s.source_files = 'Sources/identity/*.swift'
  s.module_name = 'identity'

  # The xcframework ships an arm64 simulator slice only (no x86_64), matching the
  # KMP iosSimulatorArm64 target. Exclude x86_64 for the simulator so `pod lib lint`
  # and consumer builds resolve the slice on Apple Silicon.
  s.pod_target_xcconfig  = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'x86_64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'x86_64' }

  # Runtime dependencies — mirror the `cocoapods { }` block in identity/build.gradle.kts.
  s.dependency 'iProov'
  s.dependency 'JOSESwift', '3.0.0'
end
