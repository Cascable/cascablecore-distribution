//
//  CBLCameraShotPreviewDelivery.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/05/16.
//  Copyright © 2016 Daniel Kennett. All rights reserved.
//

#import <CascableCore/CBLPlatformDefines.h>

/**
 The block callback signature when the shot preview delivery object has completed loading the image preview.

 @param sourceData If the operation succeeded, the raw image JPEG data.
 @param preview If the operation succeeded, the preview as an `NSImage` or `UIImage` object.
 @param error If the operation failed, an error object describing the operation.
 */
typedef void (^CBLCameraShotPreviewDeliveryCallback)(NSData * _Nullable sourceData, PLATFORM_IMAGE * _Nullable preview, NSError * _Nullable error) NS_SWIFT_NAME(ShotPreviewDeliveryCallback);

/** When a new shot preview is available, the camera will provide an `id <CBLCameraShotPreviewDelivery>` object. */
NS_SWIFT_NAME(ShotPreviewDelivery)
@protocol CBLCameraShotPreviewDelivery <NSObject>

/** Returns `YES` if the preview is still valid, otherwise `NO`. Previews will time out after some amount of time. */
@property (readonly) BOOL isValid;

/** Returns the source image's file name, if available. Not guaranteed to exactly match. This property may only become valid after `fetchShotPreview:` successfully completes. */
@property (readonly, copy, nullable) NSString *fileNameHint;

/** Returns `YES` if the preview is currently being loaded. */
@property (readonly) BOOL requestInProgress;

/** Returns the progress of the request. May be indeterminate, and state will change during the fetch operation. */
@property (readonly, nonatomic, strong, nonnull) NSProgress *requestProgress;

/**
 If the receiver is a preview of an image that's currently residing in local storage, the location of that image
 is provided here.

 The value of this property is often `nil`, but CascableCore may choose to store image data on disk in cases where
 the source data is very large. The image data will be deleted from disk when this object is deallocated.

 This property may only become valid after `fetchShotPreview:` successfully completes.

 **Note:** The image file is owned by shot preview object. If you wish to use it yourself, copy the file to a
           location owned by your app.
 */
@property (readonly, copy, nullable) NSURL *originalBackingImageUrl;

/**
 Fetch the preview from the camera if it's still valid.
 
 @param callback The callback block to be executed with the results of the fetch. This will be called on the main thread.
 */
-(void)fetchShotPreview:(nonnull CBLCameraShotPreviewDeliveryCallback)callback;

@end
