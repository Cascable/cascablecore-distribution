//
//  CBLCameraQRDecoding.h
//  CascableCore
//
//  Created by Daniel Kennett on 2018-03-15.
//  Copyright © 2018 Cascable AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CascableCore/CBLConstants.h>

/** The CBLCameraWiFiDetails class is a small metadata class that contains WiFi SSID/password data. */
NS_SWIFT_NAME(CameraWiFiDetails) @interface CBLCameraWiFiDetails: NSObject

/** The type of camera hosting the network. */
@property (nonatomic, readonly) CBLCameraFamily cameraType;

/** The network's SSID. */
@property (nonatomic, readonly, nonnull) NSString *ssid;

/** The network's password. */
@property (nonatomic, readonly, nonnull) NSString *password;

@end

/** The CBLCameraQRDecoding class contains logic for decoding the QR codes cameras present for connection into WiFi SSID/password data. */
NS_SWIFT_NAME(CameraQRDecoding) @interface CBLCameraQRDecoding: NSObject

/** The shared QR decoding object. */
@property (nonatomic, readonly, class, nonnull) CBLCameraQRDecoding *sharedInstance NS_SWIFT_NAME(shared);

/**
 Attempt to decode the given QR code string into WiFi connection details.

 @param qrCode The string that was encoded in a camera's QR image.
 @return Returns a `CBLCameraWiFiDetails` object if decoding was successful, otherwise `nil`.
 */
-(CBLCameraWiFiDetails * _Nullable)decodeQRCode:(NSString * _Nonnull)qrCode NS_SWIFT_NAME(decode(qrCode:));

@end
