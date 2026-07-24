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
            url:
                "https://github.com/iProov/identity/releases/download/0.5.0/iProovIdentity.xcframework.zip",
            checksum: "55f5e9f95be205efb36fa751eb9ca0d2fd79b92c96e5edbfba1fa4f11020b468"
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
