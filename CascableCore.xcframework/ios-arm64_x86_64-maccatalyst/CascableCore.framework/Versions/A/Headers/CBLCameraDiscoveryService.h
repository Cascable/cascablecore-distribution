//
//  CBLCameraDiscoveryService.h
//  Cascable
//
//  Created by Daniel Kennett on 29/06/14.
//  Copyright (c) 2014 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CascableCore/CBLConstants.h>

@protocol CBLCameraDiscoveryService;

/** Possible camera transport values. */
typedef NS_ENUM(NSInteger, CBLCameraTransport) {
    /** The camera is communicating via a TCP/IP network, either using WiFi or Ethernet. */
    CBLCameraTransportNetwork = 0,
    /** The camera is communicating via USB. */
    CBLCameraTransportUSB = 1
} NS_SWIFT_NAME(CameraTransport);

/** The discovery service's delegate protocol. Typically, this should not be interfered with. */
NS_SWIFT_NAME(CameraDiscoveryServiceDelegate)
@protocol CBLCameraDiscoveryServiceDelegate <NSObject>

/**
 Called when the service thinks it should be removed from any list of available devices.

 @param service The service the sent the message.
 */
-(void)serviceShouldBeForciblyRemoved:(nonnull id <CBLCameraDiscoveryService>)service;

@end

/**
 The block callback signature when a service has completed or failed resolving.

 @param service The service that completed or failed resolving.
 @param error If the operation failed, an error object describing the operation.
 */
typedef void (^CBLCameraDiscoveryServiceResolveCallback)(id <CBLCameraDiscoveryService> _Nonnull service, NSError * _Nullable error) NS_SWIFT_NAME(CameraDiscoveryServiceResolveCallback);

/**
 The block callback signature when a service has completed or failed resolving metadata.

 @param service The service that completed or failed resolving.
 @param error If the operation failed, an error object describing the operation.
 */
typedef void (^CBLCameraDiscoveryMetadataResolveCallback)(id <CBLCameraDiscoveryService> _Nonnull service, NSError * _Nullable error) NS_SWIFT_NAME(CameraDiscoveryMetadataResolveCallback);

/** A camera discovery service represents a camera that has been found on the network, but has not been connected to. A meta-camera, if you will. */
NS_SWIFT_NAME(CameraDiscoveryService)
@protocol CBLCameraDiscoveryService <NSObject>

/// ------- Service Resolving

/**
 Attempt to resolve the service enough to be able to connect to the camera.

 @param block The block to be called when resolution fails or succeeds.
 @param blockQueue The queue on which to trigger the callback block.
 */
-(void)resolveService:(nonnull CBLCameraDiscoveryServiceResolveCallback)block queue:(nonnull dispatch_queue_t)blockQueue;

/**
 Attempt to resolve the service enough to be able to query camera metadata.

 @param block The block to be called when resolution fails or succeeds.
 @param blockQueue The queue on which to trigger the callback block.
 */
-(void)resolveMetadata:(nonnull CBLCameraDiscoveryMetadataResolveCallback)block queue:(nonnull dispatch_queue_t)blockQueue;

/** Inform the service that it should be forcibly removed from available device lists. */
-(void)forceRemoval;

/** Returns `true` if the service has been resolved enough to attempt a connection to the camera, otherwise `false`. */
@property (nonatomic, readonly) BOOL serviceHasBeenResolved;

/** Returns `true` if the service has been resolved enough for metadata such as model name to be available, otherwise `false`. */
@property (nonatomic, readonly) BOOL metadataHasBeenResolved;

/** Returns the service's transport. */
@property (nonatomic, readonly) CBLCameraTransport transport;

/// ------- Properties

/** The service's delegate. */
@property (nullable, nonatomic, readwrite, weak) id <CBLCameraDiscoveryServiceDelegate> delegate;

/** Returns the client name used when connecting to the camera. */
@property (nonnull, nonatomic, readonly, copy) NSString *clientName;

/** Returns the service's camera model name, if available. */
@property (nullable, nonatomic, readonly, copy) NSString *model;

/**  Returns the service's camera manufacturer, if available. */
@property (nullable, nonatomic, readonly, copy) NSString *manufacturer;

/**  Returns a unique identifier for the service's camera, if available. */
@property (nullable, nonatomic, readonly, copy) NSString *cameraId;

/**  Returns the service's camera serial number, if available. */
@property (nullable, nonatomic, readonly, copy) NSString *serialNumber;

/** Returns the IPv4 address of the service, if available. */
@property (nullable, nonatomic, readonly, copy) NSString *ipv4Address;

/** Returns the service's dynamic host name, if available. */
@property (nullable, nonatomic, readonly, copy) NSString *hostName;

/** Returns the port on which the service can be connected to, or `0` if not available. */
@property (nonatomic, readonly) NSInteger port;

@end
