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
            url: "https://github.com/iProov/identity/releases/download/0.4.0/identity.xcframework.zip",
            checksum: "b0364a31eb38e540cf9aa5e14b877d4754e519ebe2f529112585afc65dad95cf"
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
