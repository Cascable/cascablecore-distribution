//
//  CBLHotspotHelpers.h
//  CascableCore
//
//  Copyright © 2025 Cascable AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CascableCore/CBLCameraQRDecoding.h>

/** An object describing a connected-to WiFi network. */
NS_SWIFT_NAME(HotspotConfiguration) __attribute__((swift_attr("@Sendable"))) @protocol CBLHotspotConfiguration <NSObject>

/** The network's SSID. */
@property (nonatomic, readonly, copy, nonnull) NSString *ssid;

/** The network's interface (i.e., `en0`). */
@property (nonatomic, readonly, copy, nonnull) NSString *interface;

/** Signal the the WiFi network should be disconnected. */
-(void)disconnect;

@end

/**
 The block callback signature when an attempt to connect to a WiFi network succeeds of fails.

 @param configuration Upon success, contains an `id <CBLHotspotConfiguration>` object containing information about the network.
 @param error Upon failure, contains an error object detailing the error.
 */
typedef void (^CBLHotspotCompletion)(id <CBLHotspotConfiguration> _Nullable configuration, NSError * _Nullable error) NS_SWIFT_NAME(HotspotCompletion);

/** The `CBLHotspotHelpers` class contains logic for connecting the host device to the given WiFi network. */
NS_SWIFT_NAME(HotspotHelpers) @interface CBLHotspotHelpers: NSObject

/** The shared object. */
@property (nonatomic, readonly, class, nonnull) CBLHotspotHelpers *sharedInstance NS_SWIFT_NAME(shared);

/** Returns `YES` if location permission is required to connect to a WiFi network, otherwise `NO`. */
@property (nonatomic, readonly, class) BOOL requiresLocationPermission;

/**
 Attempt to join the given WiFi network.

 @note Joining a WiFi network can take upwards of 20-30 seconds.

 @param ssid The SSID of the network to join.
 @param password The password of the network to join.
 @param promptForLocation If the current platform requires location permission to connect to a network, pass `YES`
                          to automatically prompt for that permission if needed.
 @param completionHandler The completion handler to call upon success or failure.
 @param completionQueue The queue on which to call the completion handler.
 */
-(void)attemptToJoinWiFiNetwork:(NSString * _Nonnull)ssid
                       password:(NSString * _Nonnull)password
   promptingForLocationIfNeeded:(BOOL)promptForLocation
              completionHandler:(CBLHotspotCompletion _Nonnull)completionHandler
                completionQueue:(dispatch_queue_t _Nonnull)completionQueue
NS_SWIFT_NAME(attemptToJoinWiFiNetwork(_:password:promptingForLocationIfNeeded:completionHandler:completionQueue:));

/**
 Attempt to join the WiFi network described by the given QR code scanning result.  See `id <CBLCameraQRDecoding>` for details.

 @note Joining a WiFi network can take upwards of 20-30 seconds.

 @param networkDetails The details of the network to join.
 @param promptForLocation If the current platform requires location permission to connect to a network, pass `YES`
                          to automatically prompt for that permission if needed.
 @param completionHandler The completion handler to call upon success or failure.
 @param completionQueue The queue on which to call the completion handler.
 */
-(void)attemptToJoinQRCodeNetwork:(CBLCameraWiFiDetails * _Nonnull)networkDetails
     promptingForLocationIfNeeded:(BOOL)promptForLocation
                completionHandler:(CBLHotspotCompletion _Nonnull)completionHandler
                  completionQueue:(dispatch_queue_t _Nonnull)completionQueue
NS_SWIFT_NAME(attemptToJoinQRCodeNetwork(_:promptingForLocationIfNeeded:completionHandler:completionQueue:));

@end
