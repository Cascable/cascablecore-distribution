//
//  CBLCameraInitiatedTransfer.h
//  CascableCore
//
//  Created by Daniel Kennett on 2022-02-15.
//  Copyright © 2022 Cascable AB. All rights reserved.
//

#import <CascableCore/CBLPlatformDefines.h>
#import <CascableCore/CBLConstants.h>

/// Representations of an image.
typedef NS_OPTIONS(NSInteger, CBLCameraInitiatedTransferRepresentation) {
    /// A reduced size/quality preview representation of the image, usually in JPEG or HEIC format.
    CBLCameraInitiatedTransferRepresentationPreview = 1 << 0,
    /// The original image file.
    CBLCameraInitiatedTransferRepresentationOriginal = 1 << 1
} NS_SWIFT_NAME(CameraInitiatedTransferRepresentation);

/// States that a camera-initiated transfer can be in.
typedef NS_ENUM(NSInteger, CBLCameraInitiatedTransferState) {
    /// The transfer has not yet started.
    CBLCameraInitiatedTransferStateNotStarted,
    /// The transfer is in progress.
    CBLCameraInitiatedTransferStateInProgress,
    /// The transfer has completed.
    CBLCameraInitiatedTransferStateComplete,
} NS_SWIFT_NAME(CameraInitiatedTransferState);

@protocol CBLCameraInitiatedTransferResult;

/// The block callback signature for handling the result of a request to execute a camera-initiated transfer, containing
/// either the result of the transfer, or an error describing the failure.
typedef void (^CBLCameraInitiatedTransferCompletionHandler)(id <CBLCameraInitiatedTransferResult> _Nullable, NSError * _Nullable)
    NS_SWIFT_NAME(CameraInitiatedTransferCompletionHandler);

/// A camera-initiated transfer is a request from a camera to transfer an image file (or at least, a representation of
/// one such as a preview) to the connected host. This typically happens soon after a shot is taken, and can allow the
/// previewing and transferring of images even if the camera currently doesn't allow access to its storage.
///
/// Camera-initiated transfers can be time-sensitive as the camera moves on to newer images or flushes buffers — they
/// should be dealt with expediently.
///
/// In some cases, the camera-initiated transfer to the host may be the _only_ destination for an image. Commonly
/// referred to as "tethered shooting" (or at least a variant of it), the camera might not attempt (or not be able to)
/// save the image to its own storage. If this is the case, not correctly handling a camera-initiated transfer will
/// case data loss. Check the `-isOnlyDestinationForImage` property — if that returns `YES`, not transferring and
/// saving the original representation of the image will cause it to be lost.
NS_SWIFT_NAME(CameraInitiatedTransferRequest) @protocol CBLCameraInitiatedTransferRequest <NSObject>

/// Returns `YES` if the transfer request is still valid, otherwise `NO`. Transfers will time out after some amount
/// of time.
@property (nonatomic, readonly) BOOL isValid;

/// Returns `YES` if not executing this camera-initiated transfer may cause data loss. For example, a camera
/// set to only save images to the connected host would set this to `YES`.
@property (nonatomic, readonly) BOOL isOnlyDestinationForImage;

/// Returns `YES` if not executing this camera-initiated transfer will "clog up" the camera's transfer buffer. This
/// can return `YES` independently of the `isOnlyDestinationForImage` property. Not executing transfers that have this
/// property set will stop delivery of further transfers.
@property (nonatomic, readonly) BOOL executionRequiredToClearBuffer;

/// Returns the source image's file name, if available. Not guaranteed to exactly match the name on the camera's storage.
/// This value may not be available until the transfer completes (or at all) — see `CBLCameraInitiatedTransferResult`.
@property (nonatomic, readonly, copy, nullable) NSString *fileNameHint;

/// Returns the date and time at which the request was produced. CascableCore will attempt to match this value
/// to the underlying image's EXIF timestamp, if available. Otherwise, this will be the date and time at which
/// the request was received from the camera.
///
/// @note Since EXIF doesn't tend to have the concept of timezones, dates from this property will also adhere to
///       that "standard" in that they'll be expressed in the GMT+0 timezone. I.e., an image produced at 14:00 local
///       time in California will actually be expressed at 14:00 GMT. When dealing with these values (or showing them
///       to the user), make sure you account for this - when using date formatters, this as simple as explicitly
///       setting the formatter's timezone to GMT+0.
@property (nonatomic, readonly, copy, nonnull) NSDate *dateProduced;

/// Returns an option set of the representations available for this transfer.
///
/// Common combinations are preview-only, or preview and original.
@property (nonatomic, readonly) CBLCameraInitiatedTransferRepresentation availableRepresentations;

/// Returns `YES` if the receiver can provide the given representation, otherwise `NO`.
-(BOOL)canProvideRepresentation:(CBLCameraInitiatedTransferRepresentation)representation;

/// Returns a predicted file size for the given representation, or `0` if the representation isn't available
/// or its size is currently unknown.
///
/// @note It's very rare that a preview representation's size will be known at this stage.
///
/// @warning You must only pass a single representation to this method, otherwise `0` will be returned.
-(NSInteger)predictedFileSizeForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
    NS_SWIFT_NAME(predictedFileSize(for:));

/// Returns the file type UTI for the given representation, or `nil` if the representation isn't available or if the
/// format of the requested representation is unknown before loading.
///
/// @warning You must only pass a single representation to this method, otherwise `nil` will be returned.
///
/// @note This method may fall back to returning `kUTTypeData` if the original representation is in a RAW image format
/// not recognised by the operating system.
-(NSString * _Nullable)predictedUTIForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
    NS_SWIFT_NAME(predictedUTI(for:));

/// Returns the state of the transfer. A camera-initiated transfer can only be performed once.
@property (nonatomic, readonly) CBLCameraInitiatedTransferState transferState;

/// Returns the progress of the transfer, if available. While this property is marked `nonnull` for binding purposes,
/// the values in the returned progress object are only meaningful when the transfer is in progress.
///
/// Not all cameras provide progress information — in these cases, the progress will remain indeterminate.
@property (nonatomic, readonly, strong, nonnull) NSProgress *transferProgress;

/// Execute the camera-initiated transfer if it's still valid.
///
/// If possible, CascableCore will optimise the transfer to reduce the amount of data transferred (and therefore time
/// needed). For example, if a camera-initiated transfer request has both the preview and original representations
/// available, CascableCore may perform a partial transfer if only the preview representation is requested. This is
/// particularly useful if, for example, you want to show previews of RAW images.
///
/// @warning A camera-initiated transfer can only be performed once.
///
/// @param representations The representations to transfer from the camera. Must be present in the
///                        `availableRepresentations` property.
/// @param completionHandler The completion handler, to be called on the main queue, when the transfer succeeds or fails.
-(void)executeTransferForRepresentations:(CBLCameraInitiatedTransferRepresentation)representations
                       completionHandler:(CBLCameraInitiatedTransferCompletionHandler _Nonnull)completionHandler
    NS_SWIFT_NAME(executeTransfer(for:completionHandler:));

/// Execute the camera-initiated transfer if it's still valid.
///
/// If possible, CascableCore will optimise the transfer to reduce the amount of data transferred (and therefore time
/// needed). For example, if a camera-initiated transfer request has both the preview and original representations
/// available, CascableCore may perform a partial transfer if only the preview representation is requested. This is
/// particularly useful if, for example, you want to show previews of RAW images.
///
/// @warning A camera-initiated transfer can only be performed once.
///
/// @param representations The representations to transfer from the camera. Must be present in the
///                        `availableRepresentations` property.
/// @param completionQueue The queue on which to deliver the completion handler.
/// @param completionHandler The completion handler to be calle when the transfer succeeds or fails.
-(void)executeTransferForRepresentations:(CBLCameraInitiatedTransferRepresentation)representations
                         completionQueue:(dispatch_queue_t _Nonnull)completionQueue
                       completionHandler:(CBLCameraInitiatedTransferCompletionHandler _Nonnull)completionHandler
    NS_SWIFT_NAME(executeTransfer(for:completionQueue:completionHandler:));

@end

/// The result of a camera-initiated transfer.
///
/// Result objects are stored entirely locally, and as such are not under the time pressure that the intial camera-
/// initiated transfer object is. However, they can be fairly resource heavy (especially when the transfer is of a
/// RAW image) so it's recommended that they are dealt with reasonably quickly.
///
/// How this object manages its resources is an implementation detail, and any buffers of cache files it creates will
/// be cleaned up when the object is deallocated. To take ownership of the transfer result, use the appropriate methods
/// to extract representations into RAM or to disk.
NS_SWIFT_NAME(CameraInitiatedTransferResult) @protocol CBLCameraInitiatedTransferResult <NSObject>

/// The representations available in this transfer result.
@property (nonatomic, readonly) CBLCameraInitiatedTransferRepresentation availableRepresentations;

/// Returns `YES` if the receiver can provide the given representation, otherwise `NO`.
-(BOOL)containsRepresentation:(CBLCameraInitiatedTransferRepresentation)representation;

/// Returns `YES` if not saving the contents of this result may cause data loss. For example, a camera
/// set to only save images to the connected host would set this to `YES`.
@property (nonatomic, readonly) BOOL isOnlyDestinationForImage;

/// A file name hint for the original representation of the image, if available.
@property (nonatomic, readonly, copy, nullable) NSString *fileNameHint;

/// Returns the date and time at which the request was produced. CascableCore will attempt to match this value to
/// the underlying image's EXIF timestamp, if available. Otherwise, this will be the date and time at which the
/// request was received from the camera.
///
/// @note Since EXIF doesn't tend to have the concept of timezones, dates from this property will also adhere to
///       that "standard" in that they'll be expressed in the GMT+0 timezone. I.e., an image produced at 14:00 local
///       time in California will actually be expressed at 14:00 GMT. When dealing with these values (or showing them
///       to the user), make sure you account for this - when using date formatters, this as simple as explicitly
///       setting the formatter's timezone to GMT+0.
@property (nonatomic, readonly, copy, nonnull) NSDate *dateProduced;

/// Returns a suggested file name extension for the given representation or `nil` if the representation isn't available.
///
/// To match camera conventions, extensions will be uppercase ("JPG", "CR3", "ARW", "HEIC", etc).
///
/// @warning You must only pass a single representation to this method, otherwise `nil` will be returned.
///
/// @note This method is guaranteed to return a valid value as long as the representation is available. This can be
///       useful if the `fileNameHint` property is `nil` and you need to write a representation to disk.
-(NSString * _Nullable)suggestedFileNameExtensionForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
    NS_SWIFT_NAME(suggestedFileNameExtension(for:));

/// Returns the type UTI for the given representation, or `nil` if the representation isn't available.
///
/// @warning You must only pass a single representation to this method, otherwise `nil` will be returned.
///
/// @note This method may fall back to returning `kUTTypeData` if the representation is in a RAW image format
/// not recognised by the operating system.
-(NSString * _Nullable)utiForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
    NS_SWIFT_NAME(uti(for:));

/// Returns the file size of a given representation, or `0` if the size is unknown or the representation isn't available.
///
/// @note The file size of the preview representation of a result generated with an original representation may be
///       unknown, since the preview is generated on-demand in this situation.
///
/// @warning You must only pass a single representation to this method, otherwise `0` will be returned.
-(NSInteger)fileSizeForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation;

/// Write the given representation to disk.
///
/// @warning You must only pass a single representation to this method, otherwise an error will be returned.
///
/// @param representation The representation to write.
/// @param destinationUrl The URL at which to write the representation. CascableCore will attempt to create the parent
///                       directory tree if it isn't already present.
/// @param completionHandler The completion handler, called on the main queue, when the operation succeeds or fails.
-(void)writeRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
                     toURL:(NSURL * _Nonnull)destinationUrl
         completionHandler:(nonnull CBLErrorableOperationCallback)completionHandler
    NS_SWIFT_NAME(write(_:to:completionHandler:));

/// Write the given representation to disk.
///
/// @warning You must only pass a single representation to this method, otherwise an error will be returned.
///
/// @param representation The representation to write.
/// @param destinationUrl The URL at which to write the representation. CascableCore will attempt to create the parent
///                       directory tree if it isn't already present.
/// @param completionQueue The queue on which to call the completion handler.
/// @param completionHandler The completion handler to be called when the operation succeeds or fails.
-(void)writeRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
                     toURL:(NSURL * _Nonnull)destinationUrl
           completionQueue:(dispatch_queue_t _Nonnull)completionQueue
         completionHandler:(nonnull CBLErrorableOperationCallback)completionHandler
    NS_SWIFT_NAME(write(_:to:completionQueue:completionHandler:));

/// Retrieve the given representation as an in-memory data object.
///
/// @warning You must only pass a single representation to this method, otherwise an error will be returned.
///
/// @warning This operation may fail if the representation is large enough to risk crashes due to high memory usage.
///          If this happens, the resulting error will have the code `CBLErrorCodeObjectTooLarge`.
///
/// @param representation The representation to retrieve.
/// @param completionHandler The completion handler, called on the main queue, when the operation succeeds or fails.
-(void)generateDataForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
                   completionHandler:(void (^ _Nonnull)(NSData * _Nullable, NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(generateData(for:completionHandler:));

/// Retrieve the given representation as an in-memory data object.
///
/// @warning You must only pass a single representation to this method, otherwise an error will be returned.
///
/// @warning This operation may fail if the representation is large enough to risk crashes due to high memory usage.
///          If this happens, the resulting error will have the code `CBLErrorCodeObjectTooLarge`.
///
/// @param representation The representation to retrieve.
/// @param completionQueue The queue on which to call the completion handler.
/// @param completionHandler The completion handler to be called when the operation succeeds or fails.
-(void)generateDataForRepresentation:(CBLCameraInitiatedTransferRepresentation)representation
                     completionQueue:(dispatch_queue_t _Nonnull)completionQueue
                   completionHandler:(void (^ _Nonnull)(NSData * _Nullable, NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(generateData(for:completionQueue:completionHandler:));

/// Generate an image from the preview representation.
///
/// @note This method requires that the result contains the `CBLCameraInitiatedTransferRepresentationPreview`
///       representation.
///
/// @param completionHandler The completion handler, called on the main queue, when the operation succeeds or fails.
-(void)generatePreviewImage:(void (^ _Nonnull)(PLATFORM_IMAGE * _Nullable, NSError * _Nullable))completionHandler
    NS_SWIFT_NAME(generatePreviewImage(completionHandler:));

@end
