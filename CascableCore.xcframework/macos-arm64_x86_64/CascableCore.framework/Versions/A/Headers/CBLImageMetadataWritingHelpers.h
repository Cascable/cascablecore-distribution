//
//  CBLImageMetadataWritingHelpers.h
//  CascableCore
//
//  Created by Daniel Kennett on 19/05/16.
//  Copyright © 2016 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Helper class for writing metadata into image files. */
NS_SWIFT_NAME(ImageMetadataWritingHelpers)
@interface CBLImageMetadataWritingHelpers : NSObject

/**
 Writes the given EXIF orientation into the metadata of the given image data. Does not re-compress or otherwise alter image pixel data.

 @param orientation The EXIF orientation.
 @param imageData The image data in which to write the orientation.
 @return Returns the updated image data.
 */
+(nonnull NSData *)writeExifOrientation:(NSUInteger)orientation intoImageData:(nonnull NSData *)imageData;

/**
  Writes the given image metadata properties into the metadata of the given image data. Does not re-compress or otherwise alter image pixel data.

 @param properties An ImageIO-compatible dictionary of properties. See CGImageProperties.h.
 @param imageData The image data in which to write the orientation.
 @return Returns the updated image data.
 */
+(nonnull NSData *)writeProperties:(nonnull NSDictionary *)properties intoImageData:(nonnull NSData *)imageData;

@end
