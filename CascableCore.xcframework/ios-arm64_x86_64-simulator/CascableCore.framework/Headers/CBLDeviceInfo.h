//
//  CBLDeviceInfo.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;

/** Information about a connected camera. */
NS_SWIFT_NAME(DeviceInfo)
@protocol CBLDeviceInfo <NSObject>

/** Returns the device's manufacturer (for instance, 'Canon'). */
@property (nullable, nonatomic, readonly, copy) NSString *manufacturer;

/** Returns the device's model (for instance, 'EOS M3'). */
@property (nullable, nonatomic, readonly, copy) NSString *model;

/**
 Returns the device's software version (for instance, 'V1.01').
 
 @note This will sometimes differ from the user-visible software version the camera displays in its own UI.
 */
@property (nullable, nonatomic, readonly, copy) NSString *version;

/** Returns the device's serial number. */
@property (nullable, nonatomic, readonly, copy) NSString *serialNumber;

@end
