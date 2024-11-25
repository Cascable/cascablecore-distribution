//
//  CBLFileSystemItem.h
//  CascableCore
//
//  Created by Daniel Kennett on 17/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
#import <CascableCore/CBLConstants.h>
#import <CascableCore/CBLFileSystemFolderItem.h>
#import <CascableCore/CBLFileStorage.h>

@protocol CBLFileSystemFolderItem;
@protocol CBLFileStorage;
@protocol CBLVideoMetadata;

/** File streaming instructions. */
typedef NS_ENUM(NSUInteger, CBLFileStreamInstruction) {
    /** Inform CascableCore to continue the streaming operation. */
    CBLFileStreamInstructionContinue,
    /** Inform CascableCore to cancel the streaming operation. This will trigger the operation's completion handler. */
    CBLFileStreamInstructionCancel
} NS_SWIFT_NAME(FileStreamInstruction);

/**
 The callback block preflight signature for fetching image previews. This will be called just before an image preview
 is about to be fetched.

 This can be useful when implementing (example) a scrolling list of thumbnails — if the user is scrolling quickly,
 you can cancel requests for thumbnails that are no longer onscreen.

 @param item The filesystem item the preview will be fetched for.
 @return Return `YES` to continue to fetch the preview, otherwise `NO` to cancel.
 */
typedef BOOL (^CBLPreviewImagePreflight)(id <CBLFileSystemItem> _Nonnull  item) NS_SWIFT_NAME(PreviewImagePreflight);

/**
 The callback block signature for a completed or failed image previews.

 @param item The filesystem item the preview is for.
 @param error If the operation failed, an error object that describes the failure.
 @param imageData If the operation succeeded, JPEG data for the preview.
 */
typedef void (^CBLPreviewImageDelivery)(id <CBLFileSystemItem> _Nonnull item,  NSError * _Nullable error,  NSData * _Nullable imageData) NS_SWIFT_NAME(PreviewImageDelivery);

/**
 The callback block preflight signature for fetching image EXIF metadata. This will be called just before the metadata
 is about to be fetched.

 This can be useful when implementing (example) a scrolling list of images — if the user is scrolling quickly,
 you can cancel metadata requests for images that are no longer onscreen.

 @param item The filesystem item the metadata will be fetched for.
 @return Return `YES` to continue to fetch the metadata, otherwise `NO` to cancel.
 */
typedef BOOL (^CBLEXIFPreflight)(id <CBLFileSystemItem> _Nonnull  item) NS_SWIFT_NAME(EXIFPreflight);

/**
 The callback block signature for a completed or failed image metadata requests.

 @param item The filesystem item the metadata is for.
 @param error If the operation failed, an error object that describes the failure.
 @param imageMetadata If the operation succeeded, ImageIO-compatible metadata.
 */
typedef void (^CBLEXIFDelivery)(id <CBLFileSystemItem> _Nonnull item,  NSError * _Nullable error,  NSDictionary <NSString *, id> * _Nullable imageMetadata) NS_SWIFT_NAME(EXIFDelivery);

/**
 The callback block preflight signature for fetching video metadata. This will be called just before the metadata
 is about to be fetched.

 This can be useful when implementing (example) a scrolling list of thumbnails — if the user is scrolling quickly,
 you can cancel metadata requests for images that are no longer onscreen.

 @param item The filesystem item the metadata will be fetched for.
 @return Return `YES` to continue to fetch the metadata, otherwise `NO` to cancel.
 */
typedef BOOL (^CBLVideoMetadataPreflight)(id <CBLFileSystemItem> _Nonnull  item) NS_SWIFT_NAME(VideoMetadataPreflight);

/**
 The callback block signature for a completed or failed video metadata requests.

 @param item The filesystem item the metadata is for.
 @param error If the operation failed, an error object that describes the failure.
 @param videoMetadata If the operation succeeded, the metadata.
 */
typedef void (^CBLVideoMetadataDelivery)(id <CBLFileSystemItem> _Nonnull item, NSError * _Nullable error, id <CBLVideoMetadata> _Nullable videoMetadata) NS_SWIFT_NAME(VideoMetadataDelivery);

/**
 The callback block preflight signature for streaming files from the camera. This will be called just before the stream
 is about to begin.

 @param item The filesystem item that will be streamed.
 @return Return any object to use as a "context" for the operation, including `nil`. This object will be passed to chunk
         delivery callbacks. For example, you may want to set up a file handle or data storage object here for chunks
         to be written to later.
 */
typedef _Nullable id (^CBLFileStreamPreflight)(id <CBLFileSystemItem> _Nonnull item) NS_SWIFT_NAME(FileStreamPreflight);

/**
 The callback block signature for data chunk delivery when streaming files from the camera. This will be called multiple
 times in sequence once an operation starts.

 IMPORTANT: In some circumstances, this delivery block may be invoked with an empty/zero-length chunk of data. Make
 sure your code handles this case properly. Such a delivery should not be treated as an error, and you should return
 the desired instruction.

 @param item The filesystem item being streamed.
 @param chunk The chunk of file data delivered from the camera.
 @param context The context object returned from the streaming preflight block.
 @return Return `CBLFileStreamInstructionContinue` to continue the operation and get more chunks, or
         `CBLFileStreamInstructionCancel` to cancel the operation.
 */
typedef CBLFileStreamInstruction (^CBLFileStreamChunkDelivery)(id <CBLFileSystemItem> _Nonnull item, NSData * _Nonnull chunk, id _Nullable context) NS_SWIFT_NAME(FileStreamChunkDelivery);

/**
 The callback block signature that will be called when a file streaming operation completes for fails.

 @param item The filesystem item being streamed.
 @param error If the operation failed (including being cancelled), an error describing the failure.
 @param context The context object returned from the streaming preflight block.
 */
typedef void (^CBLFileStreamCompletion)(id <CBLFileSystemItem> _Nonnull item, NSError * _Nullable error, id _Nullable context) NS_SWIFT_NAME(FileStreamCompletion);

/** Describes the type of rating a particular filesystem item takes when changing the rating. */
typedef NS_ENUM(NSInteger, CBLFileSystemItemMutableRatingType) {
    /** The item is not able to have its rating mutated. */
    CBLFileSystemItemMutableRatingTypeNone,
    /** The item's rating takes an ITPC-standard rating in the range 0...5. */
    CBLFileSystemItemMutableRatingTypeIPTC,
    /** The items's rating is effectively boolean (or "starred") in the range 0...1. */
    CBLFileSystemItemMutableRatingTypeBoolean
} NS_SWIFT_NAME(FileSystemItemMutableRatingType);

/** An object containing video-specific metadata. */
NS_SWIFT_NAME(VideoMetadata)
@protocol CBLVideoMetadata <NSObject>

/** The frame size of the video, in pixels. Will be `CGSizeZero` if unknown. */
@property (nonatomic, readonly) CGSize frameSize;

/** The frame rate of the video. Will be `0.0` if unknown. */
@property (nonatomic, readonly) double frameRate;

/** The duration of the video, in seconds. Will be `0.0` if unknown. */
@property (nonatomic, readonly) NSTimeInterval duration;

/**
 The codec of the video, if known. This value is a "FourCC" code, compatible with the `FourCharCode` and
 `CMVideoCodecType` types in CoreMedia. See `CMFormatDescription.h` for possible values.

 Will be `0x0` if unknown.
 */
@property (nonatomic, readonly) uint32_t codec;

@end

/** A filesystem item represents a file or folder on the camera's storage. */
NS_SWIFT_NAME(FileSystemItem)
@protocol CBLFileSystemItem <NSObject>

/** 
 Returns `YES` if the item's metadata has been loaded, otherwise `NO`. 
 
 If metadata hasn't been loaded, many properties will return `nil` or zero values.
 */
@property (nonatomic, readonly) BOOL metadataLoaded;

/** Returns the name of the file. */
@property (nonatomic, readonly, copy, nullable) NSString *name;

/** Returns the size of the file, or zero for directories or items whose metadata hasn't been loaded. */
@property (nonatomic, readonly) NSUInteger size;

/** Returns the internal handle to the file. */
@property (nonatomic, readonly, nullable) id handle;

/** Returns `YES` if the file is protected (i.e., cannot be deleted), otherwise `NO`. */
@property (nonatomic, readonly) BOOL isProtected;

/** Returns the creation date of the file, or `nil` for items whose metadata hasn't been loaded. */
@property (nonatomic, readonly, copy, nullable) NSDate *dateCreated;

/** The item's rating. Follows the IPTC StarRating spec (0 = no rating, otherwise 1-5 stars). */
@property (nonatomic, readonly) NSInteger rating;

/** 
 The item's rating mutation type. Folders and unsupported files will return `CBLFileSystemItemMutableRatingTypeNone`,
 as will items without loaded metadata (i.e., `-metadataLoaded` returns `NO`), and items on a camera that doesn't
 support mutating an item's rating via remote control at all.
 */
@property (nonatomic, readonly) CBLFileSystemItemMutableRatingType ratingMutationType;

/**
 Attempt to update the item's rating to the given value. See the `-ratingMutationType` property for valid values. Values
 will be clamped to the allowable range.

 Due to the caveats mentioned below, it's highly recommended that you observe the `-rating` property for changes to
 an item's rating rather than rely on the completion handler of this method.

 @note: Updating the rating of an image may change the rating of other, releated images (such as the other side of
        a RAW+JPEG pair).

 @note: The completion handler of this method indicates whether the command was accepted by the camera and didn't
        immediately fail. Some cameras will accept the command but still not update the rating in some instances -
        we've observed this happening on Canon cameras when trying to apply a rating to images shot with a different
        camera model, for example.
 */
-(void)updateRatingTo:(NSInteger)newRating completionHandler:(nonnull CBLErrorableOperationCallback)completionHandler NS_SWIFT_NAME(updateRating(to:completionHandler:));

/** Returns the parent item of this file, or `nil` if the receiver represents the root directory. */
@property (nonatomic, readonly, weak, nullable) id <CBLFileSystemFolderItem> parent;

/** Returns the storage device on which this file is placed. */
@property (nonatomic, readonly, weak, nullable) id <CBLFileStorage> storage;

/** Returns `YES` if the file is a known image type, else `NO`. */
@property (nonatomic, readonly) BOOL isKnownImageType;

/** Returns `YES` if the file is a know video type, else `NO`. */
@property (nonatomic, readonly) BOOL isKnownVideoType;

/** Permanently removes the file from the device. */
-(void)removeFromDevice:(nonnull CBLErrorableOperationCallback)block NS_SWIFT_NAME(removeFromDevice(_:));

/** Returns `YES` if removing this item could have side effects — for example, removing one image from a RAW+JPEG pair will also remove the other. */
@property (nonatomic, readonly) BOOL removalRemovesPairedItems;

/**
 Loads the metadata for the receiver if it hasn't already been loaded. 
 
 If metadata has already been loaded, the callback block will be immediately called with no error.

 @param block The block to trigger after loading completes or fails. Will be called on the main queue.
 */
-(void)loadMetadata:(nonnull CBLErrorableOperationCallback)block;

/** Fetch the thumbnail of the given file system item.
 
 @param preflight A block that will be called when the thumbnail is about to be fetched. Return `YES` to allow the 
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the thumbnail has successfully been fetched, or an error occurred. 
 */
-(void)fetchThumbnailWithPreflightBlock:(nonnull CBLPreviewImagePreflight)preflight
                 thumbnailDeliveryBlock:(nonnull CBLPreviewImageDelivery)delivery;

/** Fetch the thumbnail of the given file system item.

 @param preflight A block that will be called when the thumbnail is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the thumbnail has successfully been fetched, or an error occurred.
 @param deliveryQueue The queue on which the delivery block will be called.
 */
-(void)fetchThumbnailWithPreflightBlock:(nonnull CBLPreviewImagePreflight)preflight
                 thumbnailDeliveryBlock:(nonnull CBLPreviewImageDelivery)delivery
                          deliveryQueue:(nonnull dispatch_queue_t)deliveryQueue;

/** Fetch image metadata (EXIF, IPTC, etc) for the given file system item. Only works with known image types.

 The returned metadata is in the form of an ImageIO-compatible dictionary. See `CGImageProperties.h` for details.

 @param preflight A block that will be called when the metadata is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the metadata has successfully been fetched, or an error occurred.
 */
-(void)fetchEXIFMetadataWithPreflightBlock:(nonnull CBLEXIFPreflight)preflight
                     metadataDeliveryBlock:(nonnull CBLEXIFDelivery)delivery;

/** Fetch image metadata (EXIF, IPTC, etc) for the given file system item. Only works with known image types.

 The returned metadata is in the form of an ImageIO-compatible dictionary. See `CGImageProperties.h` for details.

 @param preflight A block that will be called when the metadata is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the metadata has successfully been fetched, or an error occurred.
 @param deliveryQueue The queue on which the delivery block will be called.
 */
-(void)fetchEXIFMetadataWithPreflightBlock:(nonnull CBLEXIFPreflight)preflight
                     metadataDeliveryBlock:(nonnull CBLEXIFDelivery)delivery
                             deliveryQueue:(nonnull dispatch_queue_t)deliveryQueue;

/**
 Fetch video metadata for the given file system item. Only works with known video types.

 @param preflight A block that will be called when the metadata is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the metadata has successfully been fetched, or an error occurred.
 */
-(void)fetchVideoMetadataWithPreflightBlock:(nonnull CBLVideoMetadataPreflight)preflight
                      metadataDeliveryBlock:(nonnull CBLVideoMetadataDelivery)delivery;

/**
 Fetch video metadata for the given file system item. Only works with known video types.

 @param preflight A block that will be called when the metadata is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the metadata has successfully been fetched, or an error occurred.
 @param deliveryQueue The queue on which the delivery block will be called.
 */
-(void)fetchVideoMetadataWithPreflightBlock:(nonnull CBLVideoMetadataPreflight)preflight
                      metadataDeliveryBlock:(nonnull CBLVideoMetadataDelivery)delivery
                              deliveryQueue:(nonnull dispatch_queue_t)deliveryQueue;

/** Fetch a preview of the given file system item.

 @param preflight A block that will be called when the preview is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the preview has successfully been fetched, or an error occurred.
 */
-(void)fetchPreviewWithPreflightBlock:(nonnull CBLPreviewImagePreflight)preflight
                 previewDeliveryBlock:(nonnull CBLPreviewImageDelivery)delivery;

/** Fetch a preview of the given file system item.

 @param preflight A block that will be called when the preview is about to be fetched. Return `YES` to allow the
 operation to continue, or `NO` to cancel.
 @param delivery The block that will be called when the preview has successfully been fetched, or an error occurred.
 @param deliveryQueue The queue on which the delivery block will be called.
 */
-(void)fetchPreviewWithPreflightBlock:(nonnull CBLPreviewImagePreflight)preflight
                 previewDeliveryBlock:(nonnull CBLPreviewImageDelivery)delivery
                        deliveryQueue:(nonnull dispatch_queue_t)deliveryQueue;

/**
 Stream a file from the device.

 File streaming takes place in a series of block callbacks — one to allow you to set up any state
 required to receive the file data, then a series of delivery callbacks containing chunks of the file,
 then a completion callback to allow post-stream cleanup.

 @warning The callback blocks will be executed on the main queue.

 @param preflight Block to be called exactly once before the stream is started. The value returned
 here will be passed as the `context` parameter of the `chunkDelivery` and `complete` blocks.

 @param chunkDelivery This block will be called zero or more times in succession to deliver the file's
 data. The `context` parameter of this block will contain the value returned in the `preflight` block.
 In some circumstances, this block may be invoked with an empty/zero-length chunk of data. Make sure
 your code handles this case properly. Such a delivery should not be treated as an error, and you
 should return the desired instruction as normal.

 @param complete Block to be called exactly once after the last data chunk has been delivered (if any).
 If the stream failed or was cancelled, the `error` parameter will be non-nil and you should delete
 anything written to disk as the file won't be complete. The `context` parameter of this block will
 contain the value returned in the `preflight` block.

 @returns Returns a progress object that can be use to track the progress of the transfer.
 */
-(NSProgress * _Nonnull)streamItemWithPreflightBlock:(nonnull CBLFileStreamPreflight)preflight
                                  chunkDeliveryBlock:(nonnull CBLFileStreamChunkDelivery)chunkDelivery
                                       completeBlock:(nonnull CBLFileStreamCompletion)complete;

/**
 Stream a file from the device.

 File streaming takes place in a series of block callbacks — one to allow you to set up any state
 required to receive the file data, then a series of delivery callbacks containing chunks of the file,
 then a completion callback to allow post-stream cleanup.

 @param preflight Block to be called exactly once before the stream is started. The value returned
 here will be passed as the `context` parameter of the `chunkDelivery` and `complete` blocks.

 @param preflightQueue The queue on which to execute the preflight block.

 @param chunkDelivery This block will be called zero or more times in succession to deliver the file's
 data. The `context` parameter of this block will contain the value returned in the `preflight` block.
 In some circumstances, this block may be invoked with an empty/zero-length chunk of data. Make sure
 your code handles this case properly. Such a delivery should not be treated as an error, and you
 should return the desired instruction as normal.

 @param deliveryQueue The queue on which to execute the delivery block.

 @param complete Block to be called exactly once after the last data chunk has been delivered (if any).
 If the stream failed or was cancelled, the `error` parameter will be non-nil and you should delete
 anything written to disk as the file won't be complete. The `context` parameter of this block will
 contain the value returned in the `preflight` block.

 @param completeQueue The queue on which to execute the completion block.

 @returns Returns a progress object that can be use to track the progress of the transfer.
 */
-(NSProgress * _Nonnull)streamItemWithPreflightBlock:(nonnull CBLFileStreamPreflight)preflight
                                      preflightQueue:(nonnull dispatch_queue_t)preflightQueue
                                  chunkDeliveryBlock:(nonnull CBLFileStreamChunkDelivery)chunkDelivery
                                       deliveryQueue:(nonnull dispatch_queue_t)deliveryQueue
                                       completeBlock:(nonnull CBLFileStreamCompletion)complete
                                       completeQueue:(nonnull dispatch_queue_t)completeQueue;

@end
