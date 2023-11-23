//
//  CBLCameraDiscovery.h
//  SSDPTest
//
//  Created by Daniel Kennett on 10/03/16.
//  Copyright © 2016 Cascable. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CascableCore/CBLCameraDiscoveryService.h>

@class CBLCameraDiscovery;
@protocol CBLCamera;
@protocol CBLCameraManualDiscovery;

/** Options for discovering cameras. */
typedef NS_ENUM(NSInteger, CBLCameraDiscoveryMode) {
    /** Only search for cameras on the network. */
    CBLCameraDiscoveryModeNetworkOnly = 0,
    /** Only search for cameras via USB. */
    CBLCameraDiscoveryModeUSBOnly = 1,
    /** Search for cameras both on the network and via USB. */
    CBLCameraDiscoveryModeNetworkAndUSB = 2
} NS_SWIFT_NAME(CameraDiscoveryMode);

/** Camera discovery delegate methods. */
NS_SWIFT_NAME(CameraDiscoveryDelegate)
@protocol CBLCameraDiscoveryDelegate <NSObject>


/**
 Called when a new camera is discovered.

 @param discovery The `CBLCameraDiscovery` instance that found the camera.
 @param camera The newly found camera.
 */
-(void)discovery:(nonnull CBLCameraDiscovery *)discovery didDiscoverCamera:(nonnull id <CBLCamera>)camera;

/**
 Called when a camera can no longer be seen.

 @param discovery The `CBLCameraDiscovery` instance that lost light of the camera.
 @param camera The camera that can no longer be seen. If you're already connected to this camera, it's normal for the camera to disappear from discovery.
 */
-(void)discovery:(nonnull CBLCameraDiscovery *)discovery didLoseSightOfCamera:(nonnull id <CBLCamera>)camera;

@end

/** If you're running in the iOS Simulator, set this key in NSUserDefaults to the name of your Mac's WiFi interface (Macs with built-in
 Ethernet tend to have it on en1 and Macs without on en0) before calling -beginSearching otherwise detection may not work correctly.
 The value of this constant is the same as its name, and is only valid when running in the Simulator. */
extern NSString * _Nonnull const CBLNetworkConfigurationSimulatorWiFiInterfaceOverride;

/**
 The block callback signature when the discovery object changes the list of available cameras.
 */
typedef void (^CBLCameraDiscoveryAvailableDevicesChangedCallback)(NSArray <id <CBLCamera>> * _Nonnull) NS_SWIFT_NAME(CameraDiscoveryAvailableDevicesChangedCallback);

/** Discovery of supported cameras on the network. */
NS_SWIFT_NAME(CameraDiscovery)
@interface CBLCameraDiscovery : NSObject

/** Returns the shared discovery object. */
+(nonnull CBLCameraDiscovery *)sharedInstance;

/** Returns the manual discovery object, used for discovering cameras based on user input. */
@property (nonatomic, readonly, strong, nonnull) id <CBLCameraManualDiscovery> manualDiscovery;

/** Begin searching for devices. */
-(void)beginSearching;

/** Stop searching for devices. */
-(void)stopSearching;

/**
 Sets the client name, which will be displayed on some models of camera during pairing and connection. This
 should be set before calling -beginSearching, or before using the `manualDiscovery` object.

 Some cameras display the client name in their UIs, for example during pairing. Make sure it's something the
 user recognises — either the name of your app, or the name of their device. Client names should be kept
 short — cameras will truncate long names.

 The default value will be the `CFBundleDisplayName` (or `CFBundleName` if not present) of the main bundle.
 */
@property (nonatomic, readwrite, copy, nonnull) NSString *clientName;

/**
 Sets the discovery mode of the receiver between network only, USB only, or both network and USB.

 Changes to this property will not take effect if the receiver is already searching for devices.

 The default value is `CBLCameraDiscoveryModeNetworkAndUSB`, although USB cameras will only be detected if
 `operatingSystemIsNewEnoughForWiredCameras` returns `YES`.
 */
@property (nonatomic, readwrite) CBLCameraDiscoveryMode discoveryMode;

/** Returns `YES` if the current environment is running an operating system new enough to support wired cameras. */
@property (nonatomic, readonly) BOOL operatingSystemIsNewEnoughForWiredCameras;

/**
 Returns `YES` if the current environment has the authorization to discover wired cameras. If this method returns `NO`,
 You must obtain authorization from the using the `-attemptToObtainWiredCameraAuthorization:` method before cameras
 can be discovered. Until this property returns `YES`, wired cameras may be effectively invisible.
 */
@property (nonatomic, readonly) BOOL hasAuthorizationToDiscoverWiredCameras;

/**
 Attempt to gain authorization to work with wired cameras. Depending on the operating system in use and the
 current authorization status, this may trigger one or more dialog boxes to the user.

 This method is for convenience to control the user experience when onboarding, etc.

 @param completionHandler The completion handler that will be called on the main thread when authorization succeeds or fails.
*/
-(void)attemptToObtainWiredCameraAuthorization:(void (^ _Nonnull)(BOOL success))completionHandler
    NS_SWIFT_NAME(attemptToObtainWiredCameraAuthorization(completionHandler:));

/** Returns the cameras currently available on the network. Can be observed with KVO. */
@property (nonatomic, readonly, copy, nullable) NSArray <id <CBLCamera>> *availableCameras;

/** Add an observer callback to be called when the available devices change.
 
 @param block The observer block to add.
 */
-(void)addDevicesChangedObserver:(nonnull CBLCameraDiscoveryAvailableDevicesChangedCallback)block;

/** Remove a previously added observer callback. 

 @param block The observer block to remove.
 */
-(void)removeDevicesChangedObserver:(nonnull CBLCameraDiscoveryAvailableDevicesChangedCallback)block;

/** Returns the delegate. */
@property (nonatomic, readwrite, weak, nullable) id <CBLCameraDiscoveryDelegate> delegate;

/** Returns an array containing the identifiers of all the loaded plugins. */
@property (nonatomic, readonly, copy, nonnull) NSArray <NSString *> *loadedPluginIdentifiers;

/** Returns an array containing the identifiers of the enabled plugins. By default, all plugins are enabled. */
@property (nonatomic, readonly, copy, nonnull) NSArray <NSString *> *enabledPluginIdentifiers;

/**
 Enable or disable a particular plugin. Changes will take effect the next time `beginSearching` is called.

 Passing an unknown plugin identifier has no effect.

 @param isEnabled Whether the plugin should be enabled or not.
 @param identifier The identifier of the plugin.
 */
-(void)setEnabled:(BOOL)isEnabled forPluginWithIdentifier:(NSString * _Nonnull)identifier
    NS_SWIFT_NAME(setEnabled(_:forPluginWithIdentifier:));

@end
