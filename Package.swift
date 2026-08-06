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
                "https://github.com/iProov/identity/releases/download/0.5.2/iProovIdentity.xcframework.zip",
            checksum: "58161df5945a50e646db1850903cccedff9e6dd2ea6f45e05d22e5ec67271641"
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
