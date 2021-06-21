//
//  CBLExifHelpers.h
//  CascableCore
//
//  Created by Daniel Kennett on 2017-01-18.
//  Copyright © 2017 Cascable AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CascableCore/CBLCameraLiveViewFrame.h>

/** EXIF rotation constants. */
typedef NS_ENUM(NSInteger, CBLExifRotation) {
    /** The image has an unknown rotation. */
    CBLExifRotationUnknown = 0,
    /** The image is landscape. */
    CBLExifRotationLandscape = 1,
    /** The image is rotated 180°. */
    CBLExifRotationLandscapeUpsideDown = 3,
    /** The image is "portrait right" (i.e., the camera was rotated clockwise). */
    CBLExifRotationPortraitRight = 6,
    /** The image is "portrait right" (i.e., the camera was rotated anticlockwise). */
    CBLExifRotationPortraitLeft = 8
} NS_SWIFT_NAME(ExifRotation);

/** Helpers for working with EXIF values. */
NS_SWIFT_NAME(ExifHelpers)
@interface CBLExifHelpers : NSObject

/**
 Returns a camera live view orientation value from the given EXIF rotation value.

 @param rotation The EXIF rotation value.
 @return The live view frame orientation for the given EXIF value.
 */
+(CBLCameraLiveViewFrameOrientation)universalOrientationFromExifRotation:(CBLExifRotation)rotation;

/**
  Returns an EXIF rotation value from the given camera live view orientation value.

 @param orientation The live view orientation value.
 @return The EXIF rotation for the given live view orientation value.
 */
+(CBLExifRotation)exifRotationFromUniversalOrientation:(CBLCameraLiveViewFrameOrientation)orientation;

/**
 Returns a date object for the given EXIF date string.

 @param dateString The EXIF date string.
 @return A date object, or `nil` if the date string is invalid.
 */
+(NSDate * _Nullable)dateFromExifDateString:(NSString * _Nonnull)dateString;

@end
