//
//  CBLNetworkConfigurationHelper.h
//  CascableCore
//
//  Created by Daniel Kennett on 29/02/16.
//  Copyright © 2016 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Helper class for working with the local device's network configuration. */
NS_SWIFT_NAME(NetworkConfigurationHelper)
@interface CBLNetworkConfigurationHelper : NSObject

/** Returns all of the active network interfaces for the machine. */
+(NSArray <NSString *> * _Nonnull)allInterfaces;

/** Returns the interface most likely to be used for camera communication. */
+(NSString * _Nullable)suggestedInterfaceForCameraCommunication;

/** Returns the interface for accessing the given IP.

 Equivalent to calling `+[CBLNetworkConfigurationHelper interfaceForAccessingIPAddress:ip requiringLocalMatch:NO]`.

 @param ip The IP address to access.
 */
+(NSString * _Nullable)interfaceForAccessingIPAddress:(NSString * _Nonnull)ip;

/** Returns the interface for accessing the given IP, optionally requiring a local network match is found.

 @param ip The IP address to access.
 @param mustBeSameSubnet Pass `YES` to require that the returned interface directly matches against the given IP
                         address, otherwise `NO`. If `YES` is passed and no local match is found, `nil` wil be
                         returned. Otherwise, the default internet-accessing interface will be returned (which may
                         still be `nil`.
 */
+(NSString * _Nullable)interfaceForAccessingIPAddress:(NSString * _Nonnull)ip requiringLocalMatch:(BOOL)mustBeSameSubnet;

/** Returns the gateway/router address for the given interface. For self-hosting cameras, this is where you'll connect.
 
 @param interface The interface (e.g. `en0`) for which to find the gateway address.
 */
+(NSString * _Nullable)ipAddressOfGatewayForInterface:(NSString * _Nonnull)interface;

/** Returns the local host's IP address on the given interface.
 
  @param interface The interface (e.g. `en0`) for which to find the IP address.
 */
+(NSString * _Nullable)ipAddressOfInterface:(NSString * _Nonnull)interface;

/** Returns the IPv4 address from the given address data.
 
  @param addressData The address data from which to find the IPv4 address.
 */
+(NSString * _Nullable)ipv4AddressFromNetServiceData:(NSData * _Nonnull)addressData;

@end
