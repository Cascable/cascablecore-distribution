//
//  CBLCorePluginEntryPoint.h
//  CascableCore
//
//  Created by Daniel Kennett (Cascable) on 2021-01-11.
//  Copyright © 2021 Cascable AB. All rights reserved.
//

@import Foundation;
#import <CascableCore/CBLConstants.h>
#import <CascableCore/CBLCameraDiscovery.h>
#import <CascableCore/CBLCameraManualDiscovery.h>

/** The plugin info dictionary Info.plist key.  */
static NSString * _Nonnull const CBLCorePluginInfoDictionaryKey = @"CBLCorePluginInfo";

/** The Info.plist plugin info dictionary key for the plugin's entrypoint @objc class name. */
static NSString * _Nonnull const CBLCorePluginEntryPointClassNameKey = @"CBLCorePluginEntryPointClassName";

/** The Info.plist plugin info dictionary key for the plugin's display name. */
static NSString * _Nonnull const CBLCorePluginDisplayNameKey = @"CBLCorePluginDisplayName";

@class CBLCameraDescriptor;
@protocol CBLCorePluginEntryPoint;
@protocol CBLCorePluginRegistration;
@protocol CBLCoreCameraDiscoveryProvider;
@protocol CBLCoreCameraDiscoveryProviderDelegate;

/**
 This set of interfaces describes the runtime aspects of the CascableCore plugin API. CascableCore plugins must
 be implemented as dynamically-linked frameworks embedded in the app that also uses CascableCore. In addition,
 the following dictionary must be added to the plugin framework's Info.plist file with the `CBLCorePluginInfo` key:
 
 - CBLCorePluginDisplayName: A string describing the plugin's name.
 - CBLCorePluginEntryPointClassName: The name of the Objective-C class (or @objc Swift class) to be used as the
                                     entry point for the plugin. This class must implement the CBLCorePluginEntryPoint
                                     protocol.
 
 Your plugin framework must also have a valid value for `CFBundleIdentifier`.
 
 For example:
 
 CFBundleIdentifier: "se.cascable.my-cool-plugin",
 CBLCorePluginInfo: {
     CBLCorePluginDisplayName: "My Cool Plugin",
     CBLCorePluginEntryPointClassName: "MyCoolPluginEntryPointClass"
 }
 
 When done correctly, CascableCore will discover your plugin at runtime, instantiate an instance of your entry point
 class, and call the `registerPlugin:` method on it. In this method, you register your plugin with CascableCore.
 
 Note: While the API definitions are in Objective-C, it's perfectly possible (and supported) to use Swift to
 write your plugins. To ensure your entry point class' name matches the one in your Info.plist, make sure you
 explicitly name your class in the Objective-C runtime using the @objc attribute. For example:
 
 ```
 @objc(MyCoolPluginEntryPointClass) class MyCoolPluginEntryPointClass: NSObject, PluginEntryPoint {
     @objc func register(with pluginRegistration: PluginRegistration) {
         // Register plugin
     }
 }
 ```
 
 The plugin flow is as follows:
 
 - CascableCore creates an instance of the plugin's entry point class, which conforms to the CBLCorePluginEntryPoint
   protocol, and calls the registerPlugin: method on it.
 
 - Within the registerPlugin: method, the plugin registers provider objects with CascableCore using the
   CBLCorePluginRegistration object provided as parameter.
 
 - When appropriate, the provider objects will then be used. For example, when the client of CascableCore asks it to
   start searching for cameras, registered CBLCoreCameraDiscoveryProvider objects will be asked to search for cameras.
 
 It's important to note that CascableCore's plugin API is very much a "we'll call you" one. Your plugin will be
 discovered and used when appropriate — plugins shouldn't attempt to actively call into CascableCore.
 
 You can debug whether your plugin is being discovered correctly by using the CascableCore discovery class from your
 app (which guarantees that plugins will be loaded). Immediately after calling a plugin's entry point, CascableCore
 will output information about the registration to the console. For instance:
 
 > Registered plugin My Cool Plugin (se.cascable.my-cool-plugin)
 */

#pragma mark - Protocols Implemented By Plugin

/// This protocol defines the protocol expected by CascableCore when loading your plugin via the information
/// found in the plugin's Info.plist keys.
NS_SWIFT_NAME(PluginEntryPoint)
@protocol CBLCorePluginEntryPoint <NSObject>

/// The identifier of the plugin.
@property (class, nonatomic, readonly, copy, nonnull) NSString *pluginIdentifier;

/// The camera family provider by the plugin.
@property (class, nonatomic, readonly) CBLCameraFamily providedCameraFamily;

/// Called by CascableCore exactly once during your plugin's lifecycle. Use the passed objects to register
/// your plugin with CascableCore — if not done, your plugin will never be invoked.
///
/// Registered objects will be strongly retained by CascableCore.
///
/// @param pluginRegistration The interop object with which to register your plugin with CascableCore.
-(void)registerPlugin:(id <CBLCorePluginRegistration> _Nonnull)pluginRegistration NS_SWIFT_NAME(register(with:));

@end

/// Implement the CBLCoreCameraDiscoveryProvider protocol in order to provide custom cameras and camera discovery
/// to CascableCore. You can then register your camera provider with CascableCore in the plugin entrypoint.
NS_SWIFT_NAME(CameraDiscoveryProvider)
@protocol CBLCoreCameraDiscoveryProvider <NSObject>

/// Start the discovery process in the given mode. If the mode given doesn't apply to your situation (i.e., the mode
/// is `CBLCameraDiscoveryModeUSBOnly` and you only support network comms), you shouldn't do anything.
///
/// When searching, the `visibleCameras` property should be updated as cameras appear or disappear, after which
/// discovery messages should be delivered to the delegate, if present. Clients are encouraged to perform searches
/// in the background, but messages to the delegate must be performed on the main queue/thread.
///
/// @param discoveryMode The mode in which to perform the search.
/// @param clientName The client name to use when connecting/pairing to cameras.
-(void)startDiscoveryInMode:(CBLCameraDiscoveryMode)discoveryMode clientName:(NSString * _Nonnull)clientName NS_SWIFT_NAME(startDiscovery(in:clientName:));

/// Stop discovery and clean up any resources used by the discovery process. May be called without a preceding
/// call to `-startDiscoveryInMode:clientName:`.
-(void)stopDiscovery;

/// Returns an array of the currently visible cameras.
@property (nonatomic, readonly, copy, nonnull) NSArray <id <CBLCamera>> *visibleCameras;

/// CascableCore will set the delegate as appropriate. Messages delivered to this delegate should
/// be done so on the main thread/queue.
@property (nonatomic, readwrite, weak, nullable) id <CBLCoreCameraDiscoveryProviderDelegate> delegate;

/// Returns a unique identifier for the provider. Can be the plugin's bundle ID if it only has one provider.
@property (nonatomic, readonly, copy, nonnull) NSString *providerIdentifier;

@end

/// Implement the CBLCoreCameraManualDiscoveryProvider protocol in order to provide direct connections to your
/// cameras via CascableCore based on user input (i.e., "connect to the camera at 192.168.1.46"). You can then
/// register your manual discovery provider with CascableCore in the plugin entrypoint.
NS_SWIFT_NAME(CameraManualDiscoveryProvider)
@protocol CBLCoreCameraManualDiscoveryProvider <NSObject>

/// Attempt to discover a camera at the given descriptor.
///
/// Your plugin should make a good effort to ensure that there is indeed a camera matching your plugin's camera family
/// at the given descriptor, and error out if that's not the case. However, if this isn't possible to determine (or
/// doing so is tricky without affecting camera state), it's alright to return a camera object that will generate a
/// connection error when the user attempts to actually connect to the camera.
///
/// @param descriptor The descriptor that describes where the camera is.
/// @param clientName The client name to display on the camera, if appropriate.
/// @param completionQueue The queue on which to call the completion handler.
/// @param completionHandler The completion handler to be called on `completionQueue` when the operation succeeds or fails.
-(void)attemptToDiscoverCameraWithDescriptor:(CBLCameraDescriptor * _Nonnull)descriptor
                                  clientName:(NSString * _Nonnull)clientName
                             completionQueue:(dispatch_queue_t _Nonnull)completionQueue
                           completionHandler:(CBLCameraCreationOperationCallback _Nonnull)completionHandler;

/// Returns the camera family this provider can connect to.
@property (nonatomic, readonly) CBLCameraFamily providerCameraFamily;

/// Returns a unique identifier for the provider. Can be the plugin's bundle ID if it only has one provider.
@property (nonatomic, readonly, copy, nonnull) NSString *providerIdentifier;

@end

#pragma mark - Protocols Implemented By CascableCore

/// Methods to register your plugin with CascableCore.
NS_SWIFT_NAME(PluginRegistration)
@protocol CBLCorePluginRegistration <NSObject>

/// Register your camera discovery provider with CascableCore. This method must be called at most once per plugin.
///
/// @param discoveryProvider The discovery provider to register.
-(void)registerDiscoveryProvider:(id <CBLCoreCameraDiscoveryProvider> _Nonnull)discoveryProvider NS_SWIFT_NAME(register(discoveryProvider:));

/// Register your manual discovery provider with CascableCore. This method must be called at most once per plugin.
///
/// @param manualDiscoveryProvider The manual discovery provider provider to register.
-(void)registerManualDiscoveryProvider:(id <CBLCoreCameraManualDiscoveryProvider> _Nonnull)manualDiscoveryProvider
    NS_SWIFT_NAME(register(manualDiscoveryProvider:));

@end

/// Methods to deliver camera discovery changes to CascableCore.
NS_SWIFT_NAME(CameraDiscoveryProviderDelegate)
@protocol CBLCoreCameraDiscoveryProviderDelegate <NSObject>

/// Inform CascableCore that a new camera has been discovered.
///
/// This method must be called on the main queue/thread.
///
/// @param provider The provider that has discovered the new camera.
/// @param camera The camera that has been discovered.
-(void)cameraDiscoveryProvider:(id <CBLCoreCameraDiscoveryProvider> _Nonnull)provider didDiscover:(id <CBLCamera> _Nonnull)camera;

/// Inform CascableCore that a previously-visible camera is no longer available.
///
/// This method must be called on the main queue/thread.
///
/// @param provider The provider that has lost sight of the camera.
/// @param camera The camera that is no longer available.
-(void)cameraDiscoveryProvider:(id <CBLCoreCameraDiscoveryProvider> _Nonnull)provider didLoseSightOf:(id <CBLCamera> _Nonnull)camera;

@end
