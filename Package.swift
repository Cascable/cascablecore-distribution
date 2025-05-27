// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "CascableCore",
    platforms: [.macOS(.v11), .iOS(.v14), .macCatalyst(.v15), .visionOS("1.1")],
    products: [.library(name: "CascableCore", targets: ["CascableCore", "StopKit"])],
    dependencies: [],
    targets: [
        .binaryTarget(name: "CascableCore", path: "CascableCore.xcframework"),
        .binaryTarget(name: "StopKit", path: "StopKit.xcframework")
    ]
)
