## CascableCore Distribution

This repository contains distribution builds of the CascableCore framework from version 10.0 for use with the Swift Package Manager (SPM).

Despite the name of the distribution method, the framework is fully compatible with Objective-C. If you're using CascableCore with Swift, we recommend doing so via the [CascableCoreSwift](https://github.com/cascable/cascablecore-swift) package, which contains some great Swift-y additions to CascableCore.

For older releases of the framwork, see the [CascableCore Binaries](https://github.com/Cascable/cascablecore-binaries) repo.

### Resources

- For more information on the CascableCore product, including getting a trial license, see the [Cascable Developer Portal](https://developer.cascable.se/).

- The best starting point for working with the SDK is by seeing CascableCore in action by checking out the [CascableCore Demo Projects](https://github.com/Cascable/cascablecore-demo) repository. You'll need a trial license for it to do anything useful!

- Next, our [Getting Started With CascableCore](https://github.com/Cascable/cascablecore-demo/blob/master/Getting%20Started%20With%20CascableCore.md) document contains discussion about the CascableCore APIs and concepts in the order in which you're likely to encounter them. These APIs and concepts are equally important for both Objective-C and Swift developers.

- API reference documentation for CascableCore can be found [here](https://cascable.github.io).

### Preparing Your App for CascableCore

To add CascableCore to your project, simply it as you would any other SPM module. If you're using [CascableCoreSwift](https://github.com/cascable/cascablecore-swift), it will bring CascableCore in as a dependency for you.

Once the SDK(s) are added, a few more steps must be done to comply with App Store and sandboxing policies. Most of this work is done in your app's `Info.plist` file.

#### Info.plist: App Transport Security

If your app is limited by App Transport Security, you need to allow CascableCore to talk to the cameras on your local network.

On iOS 10 and macOS 10.12 and above, set `NSAllowsLocalNetworking` to `YES` in your `Info.plist` App Transport Security settings.

```
<key>NSAppTransportSecurity</key>
<dict>
    <key>NSAllowsLocalNetworking</key>
    <true/>
</dict>
```

On iOS 9 and macOS 10.11 or lower, you need to disable App Transport Security entirely, by setting `NSAllowsArbitraryLoads` to `YES`. If you do this, you may need to describe why to Apple in order to pass App Review. A paragraph similar to this may suffice:

> App Transport Security has been disabled for this app on iOS 9 and lower. This is because the app needs to communicate with cameras discovered on the local network, and App Transport Security  provides no way to whitelist the local network or IP address ranges on iOS 9 or lower.

If you support iOS 10/macOS 10.12 and lower you can set both `NSAllowsLocalNetworking` to `YES` _and_ `NSAllowsArbitraryLoads` to `YES` to disable App Transport Security on older OS versions, but use the more secure local networking exemption on newer OS versions. For more information on this, see [this thread on the Apple Developer Forums](https://forums.developer.apple.com/thread/6767).

CascableCore makes no attempt to communicate with the outside world via the Internet, so no domain-specific App Transport Security exemptions are needed.

Apple's documentation for App Transport Security can be found [here](https://developer.apple.com/documentation/bundleresources/information_property_list/nsapptransportsecurity).

#### Info.plist: Local Network Usage Description

iOS 14 requires that permission is obtained from the user in order to use the local network. To do so, a usage description must be defined in your `Info.plist` via the `NSLocalNetworkUsageDescription` key.

```
<key>NSLocalNetworkUsageDescription</key>
<string>MyCoolApp needs access to the local network in order to communicate with cameras over WiFi.</string>
```

You can find Apple's documentation on this [here](https://developer.apple.com/news/?id=0oi77447).

#### Info.plist: Bonjour Services

If your app is to work with cameras discovered using Bonjour (Canon EOS cameras in "EOS Utility" mode and some Nikon cameras), you should declare that you're resolving the PTP Bonjour service using the `NSBonjourServices` key. For example:

```
<key>NSBonjourServices</key>
<array>
    <string>_ptp._tcp</string>
</array>
```

You can find Apple's documentation on this [here](https://developer.apple.com/news/?id=0oi77447).

#### Entitlement: com.apple.developer.networking.multicast

If your app is to work with cameras discovered using SSDP (Canon cameras in "Smartphone" mode, some Sony cameras, and most Panasonic cameras), your app will need the `com.apple.developer.networking.multicast` entitlement.

This entitlement must be applied for manually from Apple using [this form](https://developer.apple.com/contact/request/networking-multicast). When explaining the need for this entitlement, language like this is appropriate: 

> In some cases, we need to be able to send UDP SSDP discovery broadcasts in order for cameras to be able to discover _us_ and allow a connection. We also perform SSDP searches, and connect to various camera Bonjour services. 

Apple's documentation for this entitlement can be found [here](https://developer.apple.com/documentation/bundleresources/entitlements/com_apple_developer_networking_multicast).

