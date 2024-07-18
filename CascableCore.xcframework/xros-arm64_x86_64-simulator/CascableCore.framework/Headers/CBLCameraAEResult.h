//
//  DKEOSCameraAEResult.h
//  Cascable
//
//  Created by Daniel Kennett on 30/07/2013.
//  Copyright (c) 2013 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>
@class CBLShutterSpeedValue;
@class CBLISOValue;
@class CBLApertureValue;

/** This class represents an autoexposure result from a camera. Some or all of these values may be `nil` depending on the camera's autoexposure mode. */
NS_SWIFT_NAME(AEResult)
@interface CBLCameraAEResult : NSObject <NSCopying>

/** Returns `YES` if the result is clipped (i.e., the camera couldn't correctly expose for the scene). 
 Cameras typically flash their autoexposure indicators when this happens. */
@property (nonatomic) BOOL autoExposureClipped;

/** Returns the shutter speed as calculated by the camera's autoexposure, or `nil` if no value was computed. */
@property (nullable, copy, nonatomic) CBLShutterSpeedValue *shutterSpeed;

/** Returns the ISO value as calculated by the camera's autoexposure, or `nil` if no value was computed. */
@property (nullable, copy, nonatomic) CBLISOValue *ISOValue;

/** Returns the aperture value as calculated by the camera's autoexposure, or `nil` if no value was computed. */
@property (nullable, copy, nonatomic) CBLApertureValue *apertureValue;

@end
