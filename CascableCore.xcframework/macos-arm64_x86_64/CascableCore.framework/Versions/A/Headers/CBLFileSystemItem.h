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

typedef NS_ENUM(NSUInteger, CBLFileStreamInstruction) {
    CBLFileStreamInstructionContinue,
    CBLFileStreamInstructionCancel
} NS_SWIFT_NAME(FileStreamInstruction);

typedef BOOL (^CBLPreviewImagePreflight)(id <CBLFileSystemItem> _Nonnull  item) NS_SWIFT_NAME(PreviewImagePreflight);
typedef void (^CBLPreviewImageDelivery)(id <CBLFileSystemItem> _Nonnull item,  NSError * _Nullable error,  NSData * _Nullable imageData) NS_SWIFT_NAME(PreviewImageDelivery);

typedef BOOL (^CBLEXIFPreflight)(id <CBLFileSystemItem> _Nonnull  item) NS_SWIFT_NAME(EXIFPreflight);
typedef void (^CBLEXIFDelivery)(id <CBLFileSystemItem> _Nonnull item,  NSError * _Nullable error,  NSDictionary <NSString *, id> * _Nullable imageMetadata) NS_SWIFT_NAME(EXIFDelivery);

typedef _Nullable id (^CBLFileStreamPreflight)(id <CBLFileSystemItem> _Nonnull item) NS_SWIFT_NAME(FileStreamPreflight);
typedef CBLFileStreamInstruction (^CBLFileStreamChunkDelivery)(id <CBLFileSystemItem> _Nonnull item, NSData * _Nonnull chunk, id _Nullable context) NS_SWIFT_NAME(FileStreamChunkDelivery);
typedef void (^CBLFileStreamCompletion)(id <CBLFileSystemItem> _Nonnull item, NSError * _Nullable error, id _Nullable context) NS_SWIFT_NAME(FileStreamCompletion);

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

 @param complete Block to be called exactly once after the last data chunk has been delivered (if any).
 If the stream failed or was cancelled, the `error` parameter will be non-nil and you should delete
 anything written to disk as the file won't be complete. The `context` parameter of this block will
 contain the value returned in the `preflight` block.
 */
-(void)streamItemWithPreflightBlock:(nonnull CBLFileStreamPreflight)preflight
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

 @param deliveryQueue The queue on which to execute the delivery block.

 @param complete Block to be called exactly once after the last data chunk has been delivered (if any).
 If the stream failed or was cancelled, the `error` parameter will be non-nil and you should delete
 anything written to disk as the file won't be complete. The `context` parameter of this block will
 contain the value returned in the `preflight` block.

 @param completeQueue The queue on which to execute the completion block.
 */
-(void)streamItemWithPreflightBlock:(nonnull CBLFileStreamPreflight)preflight
                     preflightQueue:(nonnull dispatch_queue_t)preflightQueue
                 chunkDeliveryBlock:(nonnull CBLFileStreamChunkDelivery)chunkDelivery
                      deliveryQueue:(nonnull dispatch_queue_t)deliveryQueue
                      completeBlock:(nonnull CBLFileStreamCompletion)complete
                      completeQueue:(nonnull dispatch_queue_t)completeQueue;

@end
