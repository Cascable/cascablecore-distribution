//
//  CBLCameraLiveViewFrame.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
@import CoreGraphics;
@import CoreMedia;
#import <CascableCore/CBLPlatformDefines.h>
#import <CascableCore/CBLCameraLiveViewAFArea.h>

/**
 Defines the orientation of the image of the live view frame. If rotating the image,
 the focal points etc should be rotated too.
 */
typedef NS_ENUM(NSUInteger, CBLCameraLiveViewFrameOrientation) {
    /** The image is "normal" landscape - no translation is required. */
    CBLCameraLiveViewFrameOrientationLandscape = 0,
    /** The camera is rotated 90° to the right. */
    CBLCameraLiveViewFrameOrientationPortraitRight = 1,
    /** The camera is rotated 90° to the left. */
    CBLCameraLiveViewFrameOrientationPortraitLeft = 2,
    /** The camera is rotated 180°. */
    CBLCameraLiveViewFrameOrientationLandscapeUpsideDown = 4
} NS_SWIFT_NAME(LiveViewFrameOrientation);

/**
 Defines the format of the pixel data of a live view frame.
 */
typedef NS_ENUM(NSUInteger, CBLCameraLiveViewFramePixelFormat) {
    /** The live view frame's pixel data is a fully-formed JPEG image. */
    CBLCameraLiveViewFramePixelFormatJPEG = 0,
    /* The live view frame's pixel data is a pixel buffer. */
    CBLCameraLiveViewFramePixelFormatRawPixelBuffer = 1
} NS_SWIFT_NAME(LiveViewFramePixelFormat);

/** Represents a single frame of a streaming live view image, along with any associated metadata. */
NS_SWIFT_NAME(LiveViewFrame)
@protocol CBLCameraLiveViewFrame <NSObject, NSCopying>

/** Returns the date and time at which this frame was generated. */
@property (nonatomic, copy, nonnull, readonly) NSDate *dateProduced;

/** Returns an array of numbers representing the brigtness plane of the image's histogram, or `nil` if not available. */
@property (nonatomic, copy, nullable, readonly) NSArray *brightnessHistogramPlane;

/** Returns an array of numbers representing the red plane of the image's histogram, or `nil` if not available. */
@property (nonatomic, copy, nullable, readonly) NSArray *redHistogramPlane;

/** Returns an array of numbers representing the green plane of the image's histogram, or `nil` if not available. */
@property (nonatomic, copy, nullable, readonly) NSArray *greenHistogramPlane;

/** Returns an array of numbers representing the blue plane of the image's histogram, or `nil` if not available. */
@property (nonatomic, copy, nullable, readonly) NSArray *blueHistogramPlane;

/** Returns the logical orientation of the frame. */
@property (nonatomic, readonly) CBLCameraLiveViewFrameOrientation orientation;

/**
 Returns the angle as detected by the camera's gyros, if available.
 0.0 is perfectly level in the "normal" landscape orientation. Range is 0-359.9°.
 */
@property (nonatomic, readonly) CGFloat rollAngle;

/**
 Returns the raw image data for the frame. See the `rawPixelFormat` and `rawPixelFormatDescription` properties
 for detailed information on the pixel format.

 It may be necessary to crop this image to avoid black bars. See `rawImageCropRect`.

 @note While the pixel format is usually stable once a live view stream starts, some cameras can change pixel formats
 mid-stream. It's important to be able to handle this if you're working directly with the various rawPixel… properties.
 */
@property (nonatomic, strong, nonnull, readonly) NSData *rawPixelData;

/**
 Returns the broad pixel format of the data in the `rawPixelData` property. If the value is a raw pixel buffer, see
 the `rawPixelFormatDescription` for additional details.

 @note While this is usually stable once a live view stream starts, some cameras can change pixel formats
 mid-stream. It's important to be able to handle this if you're working directly with the various rawPixel… properties.
 */
@property (nonatomic, readonly) CBLCameraLiveViewFramePixelFormat rawPixelFormat;

/** Returns the detailed pixel format of the data in the `rawPixelData` property.  */
@property (nonatomic, readonly, nonnull) __attribute__((NSObject)) CMFormatDescriptionRef rawPixelFormatDescription;

/** Returns the size of the image contained in the `rawPixelData` property, in pixels. */
@property (nonatomic, readonly) CGSize rawPixelSize;

/** Returns the rectangle with which to crop the image contained in `rawPixelData` to avoid black bars. */
@property (nonatomic, readonly) CGRect rawPixelCropRect;

/**
 Returns an NSImage or UIImage for this live view frame. Any required pixel format conversion and cropping will be
 applied for you. Due to this, the pixel size of this image may be different to the value of `rawPixelSize`.
 */
@property (nonatomic, strong, nullable, readonly) PLATFORM_IMAGE *image;

/** Returns the aspect in which the live view coordinate system is mapped.
 All geometric values returns by this class are relative to this property. */
@property (nonatomic, readonly) CGSize aspect;

/** Returns the areas defining the frame's focusing rectangles, or an empty array if no focusing rectangles are available. */
@property (nonatomic, copy, nullable, readonly) NSArray <id <CBLCameraLiveViewAFArea>> *afAreas;

/** Returns the rect defining the zoom preview rectangle (that is, a preview of the part of the image that will be seen if live view is zoomed in),
 or `CGRectZero` if this isn't available. */
@property (nonatomic, readonly) CGRect zoomPreviewRect;

/** Returns the smallest crop size supported by the live view stream, or `CGRectZero` if not available. */
@property (nonatomic, readonly) CGSize minimumCropSize;

/** Defines rect of this frame's image relative to the aspect. When zoomed out, this will typically be the a rectangle the same size as the frame's
 aspect with a zero origin. When zoomed in, this defines a subrect inside that aspect that defines where the zoomed-in image is compared to the whole frame. */
@property (nonatomic, readonly) CGRect imageFrameInAspect;

/** Returns `YES` if the live view frame is "zoomed in" (that is, the `imageFrameInAspect` property is smaller than `aspect`. */
@property (nonatomic, readonly) BOOL isZoomedIn;

/** Translates the given rect inside the receiver's aspect to a rect inside the target container. Useful for
 translating live view rects into views, for example.

 @param liveViewRect The rect inside the receiver's aspect.
 @param targetContainer The rect defining the bounds of the target container.
 @return The rect representing `liveViewRect` inside `targetContainer`.
 */
-(CGRect)translateSubRectOfAspect:(CGRect)liveViewRect toSubRectOfRect:(CGRect)targetContainer
    NS_SWIFT_NAME(translateSubRectOfAspect(_:toSubRectOf:));

/** Translates the given point inside the receiver's aspect to a point inside the target container. Useful for
 translating live view points into views, for example.

 @param liveViewPoint The pont inside the receiver's aspect.
 @param targetContainer The rect defining the bounds of the target container.
 @return The point representing `liveViewPoint` inside `targetContainer`.
 */
-(CGPoint)translatePointInAspect:(CGPoint)liveViewPoint toPointInRect:(CGRect)targetContainer
    NS_SWIFT_NAME(translatePointInAspect(_:toPointIn:));

/** Translates the given point inside the given rect into a point inside the receiver's aspect. Useful for
 translating a point in a view into the live view aspect, for example.

 @param point The pont to translate.
 @param container The rect defining the bounds of the container containing `point`.
 @return The point representing `point` inside the receiver's aspect.
 */
-(CGPoint)pointInAspectTranslatedFromPoint:(CGPoint)point inRect:(CGRect)container
    NS_SWIFT_NAME(pointInAspectTranslated(from:in:));

@end
