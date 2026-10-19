// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "Identity",
    platforms: [
        .iOS(.v16)
    ],
    products: [
        .library(name: "identity", targets: ["identity"])
    ],
    dependencies: [
        .package(url: "https://github.com/iproov/ios", from: "13.1.0"),
        .package(url: "https://github.com/airsidemobile/JOSESwift.git", from: "3.0.0"),
    ],
    targets: [
        .binaryTarget(
            name: "iProovIdentityBinary",
            url: "https://github.com/iProov/identity/releases/download/0.6.0/iProovIdentity.xcframework.zip",
            checksum: "b140b68530db0c8001df41f583fb68fe3d0da3770642a9108910bf1f6dfbd9b4"
        ),
        .target(
            name: "identity",
            dependencies: [
                "iProovIdentityBinary",
                .product(name: "iProov", package: "ios"),
                .product(name: "JOSESwift", package: "JOSESwift"),
            ],
            path: "Sources/identity"
        ),
    ]
)
