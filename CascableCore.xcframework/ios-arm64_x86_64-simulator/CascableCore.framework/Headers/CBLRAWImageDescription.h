//
//  CBLCR2ImageDescription.h
//  CR2 Preview Extractor
//
//  Created by Daniel Kennett on 17/05/16.
//  Copyright © 2016 Cascable. All rights reserved.
//

@import Foundation;
@import CoreGraphics;

/// Helper class for parsing RAW image headers.
NS_SWIFT_NAME(RAWImageDescription)
@interface CBLRAWImageDescription : NSObject

/**
 Returns an array of image description objects contained in the given RAW data.

 @param headers An `NSData` instance containing at least the headers of a RAW image.
 @return Returns an array of `CBLRAWImageDescription` objects representing the information contained in the 
 given RAW image headers, or `nil` if parsing failed.
 */
+(nullable NSArray <CBLRAWImageDescription *> *)imageDescriptionsInRAWHeaders:(nullable NSData *)headers;

/**
 Returns the metadata contained within a RAW EXIF blob.

 @param metadata An `NSData` instance containing an EXIF blob.
 @return Returns an EXIF metadata dictionary appropriate for use with ImageIO, or `nil` if parsing failed.
 */
+(nullable NSDictionary <NSString *, id> *)metadataInEXIFHeader:(nullable NSData *)metadata;

/**
 Returns the metadata contained within a JPEG header.

 @param jpegData A fragment of JPEG image, starting from the beginning of the file.
 @return Returns an EXIF metadata dictionary appropriate for use with ImageIO, or `nil` if parsing failed.
 */
+(nullable NSDictionary <NSString *, id> *)metadataInJPEGHeader:(nullable NSData *)jpegData;

/// Returns `true` if the receiver describes a valid image, otherwise `false`.
@property (nonatomic, readonly) BOOL isValidImage;

/// Returns `true` if the receiver describes a JPEG image, otherwise `false`.
@property (nonatomic, readonly) BOOL isStandardJPEG;

/// Returns `true` if the receiver describes a RAW image, otherwise `false`.
@property (nonatomic, readonly) BOOL isRAWImage;

/// Returns `true` if the receiver describes an entry that only contains image metadata (EXIF, etc).
@property (nonatomic, readonly) BOOL isMetadataOnly;

/// Returns the size of the image the receiver describes, in pixels.
@property (nonatomic, readonly) CGSize imageSize;

/// Returns the range within the source data of the image data the receiver describes.
@property (nonatomic, readonly) NSRange sourceDataRange;

/// Returns orientation of the receiver's image as an EXIF orientation.
@property (nonatomic, readonly) NSUInteger orientation;

/// Returns any additional metadata describing the receiver's image.
@property (nonatomic, readonly, copy, nullable) NSDictionary *additionalMetadata;

@end
