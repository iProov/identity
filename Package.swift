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
            checksum: "959f266d9daad2df53593b91a32072706ad05f6e89919e7b4aa3a69f2c4b4621"
        )
    ]
)
