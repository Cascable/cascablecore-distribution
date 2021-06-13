//
//  CBLImageManipulationHelpers.h
//  CascableCore
//
//  Created by Daniel Kennett on 2017-01-18.
//  Copyright © 2017 Cascable AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CascableCore/CBLExifHelpers.h>

/** Helper class for working with image data. */
NS_SWIFT_NAME(ImageManipulationHelpers)
@interface CBLImageManipulationHelpers : NSObject

/**
 Rotates an image to orient it based on the given EXIF rotation value.

 @param sourceData The source image data.
 @param rotation The EXIF rotation to apply to the image data.
 @return The rotated image, or `nil` if the given data wasn't a valid image or an error occurred.
 */
+(nullable NSData *)imageDataByRotatingImageData:(nonnull NSData *)sourceData forRotation:(CBLExifRotation)rotation;

/**
 Crop the given thumbnail image based on the given metadata.

 Embedded thumbnails tend to be of a fixed size no matter the size and aspect ratio of the original image. This
 can result in black bars being encoded into the thumbnail image. This image will attempt to derive and perform
 a sensible crop based on the passed ImageIO metadata.

 @param thumbnail The thumbnail image to crop.
 @param metadata The metadata to derive the crop factor from.
 @return The cropped image.
 */
+(PLATFORM_IMAGE * _Nonnull)cropMetadatalessThumbnail:(nonnull CGImageRef)thumbnail basedOnMetadata:(nullable NSDictionary *)metadata;

/**
 Crop the given thumbnail image to the given aspect ratio.

 @param image The image to crop.
 @param ratio The aspect ratio to crop to.
 @return The cropped image.
 */
+(PLATFORM_IMAGE * _Nonnull)cropMetadatalessThumbnail:(nonnull CGImageRef)image toPreRotationRatio:(CGFloat)ratio;

@end
