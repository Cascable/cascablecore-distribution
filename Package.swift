// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "CascableCore",
    platforms: [.macOS(.v10_13), .iOS(.v11)],
    products: [.library(name: "CascableCore", targets: ["CascableCore", "StopKit"])],
    dependencies: [],
    targets: [
        .binaryTarget(name: "CascableCore", path: "CascableCore.xcframework"),
        .binaryTarget(name: "StopKit", path: "StopKit.xcframework")
    ]
)
