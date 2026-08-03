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
                "https://github.com/iProov/identity/releases/download/0.5.1/iProovIdentity.xcframework.zip",
            checksum: "75e223a5fc9630086ab4b28e152d316d9a943577d1623530389ce5f204b65f66"
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
