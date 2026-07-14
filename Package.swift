// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "Identity",
    platforms: [
        .iOS(.v16)
    ],
    products: [
        .library(name: "identity", targets: ["identityWrapper"])
    ],
    dependencies: [
        .package(url: "https://github.com/iproov/ios", from: "13.1.0"),
        .package(url: "https://github.com/airsidemobile/JOSESwift.git", from: "3.0.0"),
    ],
    targets: [
        .binaryTarget(
            name: "identityBinary",
            url:
                "https://github.com/iProov/identity/releases/download/0.4.1/identity.xcframework.zip",
            checksum: "f7d0e5388fa93f664906589a8ef93ea0f764d8bb094beb35e538ff8f336cf931"
        ),
        .target(
            name: "identityWrapper",
            dependencies: [
                "identityBinary",
                .product(name: "iProov", package: "ios"),
                .product(name: "JOSESwift", package: "JOSESwift"),
            ]
        ),
    ]
)
