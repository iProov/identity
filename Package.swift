// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "Identity",
    platforms: [.iOS(.v16)],
    products: [
        .library(name: "Identity", targets: ["identity"])
    ],
    targets: [
        .binaryTarget(
            name: "identity",
            url: "https://github.com/iProov/identity/releases/download/0.3.6/identity.xcframework.zip",
            checksum: "ee629dc7c2755223a4b336f6f8725a31ff2e62c8f522a3ac9eac3766d0c17012"
        )
    ]
)
