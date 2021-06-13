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
+(NSArray <NSString *> * _Nullable)allInterfaces;

/** Returns the interface most likely to be used for camera communication. */
+(NSString * _Nullable)suggestedInterfaceForCameraCommunication;

/** Returns the interface for accessing the given IP. 
 
 @param ip The IP address to access.
 */
+(NSString * _Nullable)interfaceForAccessingIPAddress:(NSString * _Nonnull)ip;

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

/** Returns the SSID of the interface, if that interface is a Wi-Fi interface with a connected SSID.
 
  @param interface The interface (e.g. `en0`) for which to find the SSID.
 */
+(NSString * _Nullable)ssidOfInterface:(NSString * _Nonnull)interface API_DEPRECATED("WiFi SSID cannot be reliably accessed from iOS.", ios(4.1, 9.0));

@end
