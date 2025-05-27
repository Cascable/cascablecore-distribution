// swift-tools-version:5.5
import PackageDescription

let package = Package(
    name: "CascableCore",
    platforms: [.macOS(.v11), .iOS(.v14), .macCatalyst(.v15)],
    products: [.library(name: "CascableCore", targets: ["CascableCore", "StopKit"])],
    dependencies: [],
    targets: [
        .binaryTarget(name: "CascableCore", path: "CascableCore.xcframework"),
        .binaryTarget(name: "StopKit", path: "StopKit.xcframework")
    ]
)
