//
//  CBLCameraManualDiscovery.h
//  CascableCore
//
//  Created by Daniel Kennett (Cascable) on 2021-02-08.
//  Copyright © 2021 Cascable AB. All rights reserved.
//

@import Foundation;
#import <CascableCore/CBLConstants.h>

@protocol CBLCamera;

/// Camera location identifiers for performing manual camera lookups.
typedef NS_ENUM(NSInteger, CBLCameraLocation) {
    /// The camera is located at a known IP address.
    CBLCameraLocationSpecifiedIPAddress = 0,
    /// The camera is located at the gateway of a network interface.
    CBLCameraLocationGateway = 1
} NS_SWIFT_NAME(CameraLocation);


/// A camera descriptor is a manual (usually user-entered) description of where a camera can be found.
NS_SWIFT_NAME(CameraDescriptor)
@interface CBLCameraDescriptor: NSObject

/// Creates a camera descriptor for a camera located at a network interface's gateway. Typically, this describes
/// cameras that create their own WiFi networks. The gateway will be auto-calulated, usually settling on the default
/// Wi-Fi interface.
///
/// @param family The camera family.
+(CBLCameraDescriptor * _Nonnull)descriptorForCameraFamilyAtSuggestedGateway:(CBLCameraFamily)family
    NS_SWIFT_NAME(descriptor(atSuggestedGatewayFor:));

/// Creates a camera descriptor for a camera located at a specified network interface's gateway. Typically, this
/// describes cameras that create their own WiFi networks.
///
/// @param family The camera family.
/// @param interface The interface on which the camera resides. Pass `nil` to auto-calculate this.
+(CBLCameraDescriptor * _Nonnull)descriptorForCameraFamily:(CBLCameraFamily)family
                                      atGatewayOfInterface:(NSString * _Nullable)interface
    NS_SWIFT_NAME(descriptor(for:atGatewayOf:));

/// Creates a camera descriptor for a camera with a known IP address.
///
/// @param family The camera family.
/// @param address The IPv4 address at which the camera resides.
+(CBLCameraDescriptor * _Nonnull)descriptorForCameraFamily:(CBLCameraFamily)family
                                               atIPAddress:(NSString * _Nonnull)address
    NS_SWIFT_NAME(descriptor(for:at:));

/// The family of the target camera.
@property (nonatomic, readonly) CBLCameraFamily cameraFamily;

/// The location of the target camera.
@property (nonatomic, readonly) CBLCameraLocation cameraLocation;

/// The IP address of the target camera. Required if `connectionLocation` is `specifiedIPAddress`.
@property (nonatomic, readonly, nullable, copy) NSString *ipv4Address;

/// The network interface on which the target camera can be found if `connectionLocation` is `gateway`.
/// If `nil`, the most sensible interface will be used (usually that of the WiFi interface).
@property (nonatomic, readonly, nullable, copy) NSString *networkInterface;

@end

/// The callback block signature that is called when a manual camera lookup succeeds or fails.
///
/// @param camera The camera that was created, if the operation was successful.
/// @param error An error, if the operation failed.
typedef void (^CBLCameraCreationOperationCallback)(id <CBLCamera> _Nullable camera, NSError * _Nullable error) NS_SWIFT_NAME(CameraCreationOperationCallback);

/// Use the `CBLCameraManualDiscovery` object when you need to connect to a camera in situations where using
/// automatic discovery protocols is neither available or desired. Typically, this is paired with user interface
/// asking the user for the IP address and manufacturer of their camera.
///
/// Note that manual discovery is _entirely_ separate from the automatic discovery provided by `CBLCameraDiscovery`.
NS_SWIFT_NAME(CameraManualDiscovery)
@protocol CBLCameraManualDiscovery <NSObject>

/// Returns the camera families the receiver is able to connect to.
@property (nonatomic, readonly, nonnull, copy) NSArray <NSNumber *> *supportedCameraFamilies;

/// Attempt to discover a camera at the given descriptor.
///
/// @param descriptor The descriptor to attempt to resolve.
/// @param completionQueue The queue on which to call the completion handler.
/// @param completionHandler The completion handler to be called when discovery succeeds or fails.
-(void)attemptToDiscoverCamera:(CBLCameraDescriptor * _Nonnull)descriptor
               completionQueue:(dispatch_queue_t _Nonnull)completionQueue
             completionHandler:(CBLCameraCreationOperationCallback _Nonnull)completionHandler
    NS_SWIFT_NAME(attemptToDiscoverCamera(at:completionQueue:completionHandler:));

/// Attempt to discover a camera at the given descriptor.
///
/// @param descriptor The descriptor to attempt to resolve.
/// @param completionHandler The completion handler to be called on the main queue when discovery succeeds or fails.
-(void)attemptToDiscoverCamera:(CBLCameraDescriptor * _Nonnull)descriptor
             completionHandler:(CBLCameraCreationOperationCallback _Nonnull)completionHandler
    NS_SWIFT_NAME(attemptToDiscoverCamera(at:completionHandler:));

@end
