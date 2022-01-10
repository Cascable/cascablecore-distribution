//
//  CBLCamera.h
//  CascableCore
//
//  Created by Daniel Kennett on 12/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
#import <CascableCore/CBLConstants.h>
#import <CascableCore/CBLCameraAEResult.h>
#import <CascableCore/CBLDeviceInfo.h>
#import <CascableCore/CBLCameraLiveViewFrame.h>
#import <CascableCore/CBLCameraDiscoveryService.h>
#import <CascableCore/CBLFileStorage.h>
#import <CascableCore/CBLFocusInfo.h>
#import <CascableCore/CBLCameraShotPreviewDelivery.h>
#import <CascableCore/CBLCameraPropertyAPI.h>

@protocol CBLFileStorage;
@protocol CBLCameraConnectionWarning;
@protocol CBLCameraProperty;

/**
 The block callback signature when camera connection completes or fails.

 @param error The error that occurred, if any.
 @param warnings Any non-fatal connection warnings.
 */
typedef void (^CBLCameraConnectionCompleteBlock)(NSError * _Nullable error, NSArray <id <CBLCameraConnectionWarning>> * _Nullable warnings) NS_SWIFT_NAME(ConnectionCompleteCallback);

/**
 The block callback signature when the connection process needs user intervention (i.e., the user needs to perform an
 action on the camera itself). For details on how this works, see CascableCore's user guides and examples.

 If invoked, this block will usually be called twice — once when the connection attempt is paused due to user
 intervention being required (for example, if the user needs to confirm pairing on the camera), and again when
 the intervention is complete and the connection process is continuing.

 @param shouldDisplayUserInterventionDialog If `YES`, display a dialog to the user informing them they need to
                                            look at the camera and follow its instructions. If `NO`, close your
                                            previously-shown dialog.

 @param cancelConnectionBlock If non-nil (typically when `shouldDisplayUserInterventionDialog` is `YES`), this block
                              can be called to cancel the connection attempt. If non-nil, you can show a "Cancel"
                              button in your dialog and call this block if the user taps it.
 */
typedef void (^CBLCameraConnectionUserInterventionBlock)(BOOL shouldDisplayUserInterventionDialog, _Nullable dispatch_block_t cancelConnectionBlock) NS_SWIFT_NAME(ConnectionUserInterventionCallback);

/**
The block callback signature when a camera has a shot preview to deliver. See `CBLCameraShotPreviewDelivery` for details.
 */
typedef void (^CBLCameraShotPreviewAvailableBlock)(_Nonnull id <CBLCameraShotPreviewDelivery>) NS_SWIFT_NAME(ShotPreviewAvailableCallback);

/** Which advanced features are supported. */
typedef NS_OPTIONS(NSUInteger, CBLCameraSupportedFunctionality) {
    /** The camera supports rendering individual AF points. */
    CBLCameraSupportedFunctionalityAFPoints = 1 << 0,
    /** The camera supports expressing its current orientation through live view. */
    CBLCameraSupportedFunctionalityLiveViewOrientation = 1 << 4,
    /** The camera supports remote control when live view is not active. */
    CBLCameraSupportedFunctionalityRemoteControlWithoutLiveView = 1 << 5,
    /** The camera supports deleting files from its storage. */
    CBLCameraSupportedFunctionalityFileDeletion = 1 << 6,
    /** The camera supports engaging Depth of Field (DoF) preview. */
    CBLCameraSupportedFunctionalityDepthOfFieldPreview = 1 << 7,
    /** The camera supports "half pressing" the shutter to engage autofocus independently of taking a shot. */
    CBLCameraSupportedFunctionalityShutterHalfPress = 1 << 8,
    /** The camera supports updating its date/time. */
    CBLCameraSupportedFunctionalityUpdateClock = 1 << 9,
    /** The camera supports zooming in to its live view image. */
    CBLCameraSupportedFunctionalityZoomableLiveView = 1 << 10,
    /** The camera supports basic remote control when live view is not active. */
    CBLCameraSupportedFunctionalityLimitedRemoteControlWithoutLiveView = 1 << 11,
    /** The camera supports directly controlling the focus motor to move the focus distance. */
    CBLCameraSupportedFunctionalityDirectFocusManipulation = 1 << 12,
    /** The camera supports powering off when disconnecting. */
    CBLCameraSupportedFunctionalityPowerOffOnDisconnect = 1 << 13,
    /** The camera supports exposure control through aperture, shutter speed, ISO, and exposure compensation. */
    CBLCameraSupportedFunctionalityExposureControl = 1 << 14,
    /** The camera supports shot preview callbacks. */
    CBLCameraSupportedFunctionalityShotPreview = 1 << 15,
    /** The camera supports zooming live view via crop rectangles. */
    CBLCameraSupportedFunctionalityCroppableLiveView = 1 << 16,
    /** The camera supports video recording. */
    CBLCameraSupportedFunctionalityVideoRecording = 1 << 17,
    CBLCameraSupportedFunctionalityAll = NSUIntegerMax
} NS_SWIFT_NAME(SupportedFunctionality);

/** Camera connection states. */
typedef NS_ENUM(NSUInteger, CBLCameraConnectionState) {
    /** The camera is not connected. */
    CBLCameraConnectionStateNotConnected = 0,
    /** The camera is in the process of connecting. */
    CBLCameraConnectionStateConnectionInProgress,
    /** The camera is connected, and commands can be issued to it. */
    CBLCameraConnectionStateConnected,
    /** The camera is in the process of disconnecting. */
    CBLCameraConnectionStateDisconnectionInProgress
} NS_SWIFT_NAME(ConnectionState);

/** Bitfield values for camera command categories. Cameras can have zero, one, or multiple available command categories at the same time. */
typedef NS_OPTIONS(NSUInteger, CBLCameraAvailableCommandCategory) {
    /** The camera currently has no available command categories.  */
    CBLCameraAvailableCommandCategoryNone = 0,
    /** If this value is present in the options, the camera can perform stills shooting operations. */
    CBLCameraAvailableCommandCategoryStillsShooting = 1 << 0,
    /** If this value is present in the options, the camera can perform filesystem actions. */
    CBLCameraAvailableCommandCategoryFilesystemAccess = 1 << 1,
    /** If this value is present in the options, the camera can perform video recording operations. */
    CBLCameraAvailableCommandCategoryVideoRecording = 1 << 2
} NS_SWIFT_NAME(AvailableCommandCategory);

/** Non-fatal warning types that can occur during connection. */
typedef NS_ENUM(NSUInteger, CBLCameraConnectionWarningType) {
    /** The camera has lower than expected functionality. Use the `supportedFunctionality` methods to check. */
    CBLCameraConnectionWarningTypeLowerThanExpectedFunctionality,
    /** The camera supports clock sync, but attempting to do so during connection failed. */
    CBLCameraConnectionWarningTypeClockSyncFailed,
    /** The camera doesn't support clock sync. */
    CBLCameraConnectionWarningTypeClockSyncNotSupported
} NS_SWIFT_NAME(ConnectionWarningType);

/** Non-fatal warning categories that can occur during connection. */
typedef NS_ENUM(NSUInteger, CBLCameraConnectionWarningCategory) {
    /** The warning is in the 'remote control' category, affecting shooting functionality. */
    CBLCameraConnectionWarningCategoryRemoteControl,
    /** The warning is in the 'filesystem' category, affecting access to the camera's internal storage. */
    CBLCameraConnectionWarningCategoryFilesystemAccess,
    /** The warning is in the 'misc' category, affecting minor features. */
    CBLCameraConnectionWarningCategoryMisc
} NS_SWIFT_NAME(ConnectionWarningCategory);

/**
 An observer token. Required to unregister an oberver.
 */
typedef NSString CBLCameraObserverToken NS_SWIFT_NAME(ObserverToken);

/** A non-fatal connection warning. */
NS_SWIFT_NAME(ConnectionWarning)
@protocol CBLCameraConnectionWarning <NSObject>

/** The type of the warning. */
@property (nonatomic, readonly) CBLCameraConnectionWarningType type;

/** The category of the warning. */
@property (nonatomic, readonly) CBLCameraConnectionWarningCategory category;

@end

/** Sync the camera's clock to the current system clock, if supported by the camera. */
static NSString * _Nonnull const CBLConnectionFlagSyncCameraClockToSystemClock = @"CBLConnectionFlagSyncCameraClockToSystemClock";

/** Powers off the camera during disconnect, if supported by the camera. Requires `CBLCameraSupportedFunctionalityPowerOffOnDisconnect`. */
static NSString * _Nonnull const CBLDisconnectionFlagPowerOffCamera = @"CBLDisconnectionFlagPowerOffCamera";

@protocol CBLCameraCore, CBLCameraLiveView, CBLCameraProperties, CBLCameraFileSystem, CBLCameraFocusAndShutter, CBLCameraVideoRecording;

/** The catch-all protocol for a camera object in CascableCore. Functionality is broken down into sub-protocols:

 - `CBLCameraCore` for core functionality, such as connection/disconnection, supported functionality, etc.
 - `CBLCameraLiveView` for operations involving live view streaming.
 - `CBLCameraFocusAndShutter` for operations involving shooting images.
 - `CBLCameraProperties` for operations involving getting and setting camera settings/properties.
 - `CBLCameraFileSystem` for operations involving accessing the camera's file system.
 - `CBLCameraVideoRecording` for operations involving video recording.

 */
NS_SWIFT_NAME(Camera)
@protocol CBLCamera <NSObject, CBLCameraCore, CBLCameraLiveView, CBLCameraProperties, CBLCameraFileSystem, CBLCameraFocusAndShutter, CBLCameraVideoRecording>
@end

/** Camera connection, disconnection and status methods. */
NS_SWIFT_NAME(CameraCore)
@protocol CBLCameraCore <NSObject>

/** Returns the camera's "friendly" identifier, typically the serial number. */
@property (nonatomic, readonly, strong, nullable) NSString *friendlyIdentifier;

/** Returns `YES` if the instance is connected to a physical camera, otherwise `NO`.

 The `connectionState` property returns more fine-grained detail about the camera's state.
 The value of this property is equivalent to `(connectionState == CBLCameraConnectionStateConnected)`.
 */
@property (nonatomic, readonly) BOOL connected;

/** Returns an object representing information about the device. Will be `nil` if not connected. */
@property (nonatomic, readonly, strong, nullable) id <CBLDeviceInfo> deviceInfo;

/** Returns the `CBLCameraDiscoveryService` used to connect this camera. */
@property (nonatomic, readonly, strong, nonnull) id <CBLCameraDiscoveryService> service;

/** Returns the `CBLCameraFamily` for this camera. */
@property (nonatomic, readonly) CBLCameraFamily cameraFamily;

/** Returns the `CBLCameraTransport` for this camera. */
@property (nonatomic, readonly) CBLCameraTransport cameraTransport;

/** Returns the friendly, user-set name of the camera, if available. May be `nil` until the camera is connected. */
@property (nonatomic, readonly, copy, nullable) NSString *friendlyDisplayName;

/** Returns the connection state of the camera. */
@property (nonatomic, readonly) CBLCameraConnectionState connectionState;

/** Returns `YES` if the disconnection that just happens was expected or not.

 This property is only valid inside a triggered observation of the `connectionState` property
 or within the callback block of `disconnectFromDevice:callbackQueue:`.
 */
@property (nonatomic, readonly) BOOL disconnectionWasExpected;

/** Returns any warnings that occurred during connection to the camera. */
@property (nonatomic, readonly, copy, nullable) NSArray <id <CBLCameraConnectionWarning>> *connectionWarnings;

/**
 Attempt to connect to the device with the given flags.

 The passed block is called when a session is established or if the connection or session
 setup failed. If the `error` parameter of the callback is `nil`, connection and session setup was
 successful.
 
 In some cases, the connection will complete successfully enough to be useable, but with
 some warnings. A notable example is when connecting to a very new model of camera, 
 some advanced functionality may not be available yet. If there are warnings, these will
 contained in the `warnings` parameter of the callback block. These warnings should be
 presented to the user *if* they fall in a category your application uses.

 In some circumstances, the connection process is stalled by the camera asking the
 user to perform some steps on the device's screen. If this happens, the callback block
 `userInterventionCallback` will be called with the parameter `YES` to indicate that the
 caller should present UI to the user telling them to look at the camera, then again with
 `NO` to indicate to the caller that this is no longer needed.

 @note The callback blocks will be called on the main queue.

 @param flags The connection flags for this session. Can be `nil`.
 @param callback The callback to be called when the connection succeeds or fails.
 @param userInterventionCallback The callback to be invoked
 */
-(void)connectWithFlags:(nullable NSDictionary <NSString *, id> *)flags
     completionCallback:(nonnull CBLCameraConnectionCompleteBlock)callback
userInterventionCallback:(nonnull CBLCameraConnectionUserInterventionBlock)userInterventionCallback
NS_SWIFT_NAME(connect(flags:completionCallback:userInterventionCallback:));


/**
 Attempt to connect to the device with the given client name.

 Equivalent to calling `-connectWithFlags:completionCallback:userInterventionCallback:` with a `nil` `flags` parameter.

 See the documentation for `-connectWithFlags:completionCallback:userInterventionCallback:` for details.

 @param callback The callback to be called when the connection succeeds or fails.
 @param userInterventionCallback The callback to be invoked
 */
-(void)connectWithCompletionCallback:(nonnull CBLCameraConnectionCompleteBlock)callback
            userInterventionCallback:(nonnull CBLCameraConnectionUserInterventionBlock)userInterventionCallback
NS_SWIFT_NAME(connect(completionCallback:userInterventionCallback:));

/**
 Attempt to disconnect from the device.

 The passed block is called when the session is ended and connections have been
 terminated. If the `error` parameter of the callback is `nil`, disconnection was successful.

 @param flags The disconnection flags.
 @param callback The callback to be called when disconnection succeeds or fails.
 @param queue The queue on which to trigger the callback.
 */
-(void)disconnectWithFlags:(nullable NSDictionary <NSString *, id> *)flags
        completionCallback:(nullable CBLErrorableOperationCallback)callback
             callbackQueue:(nullable dispatch_queue_t)queue;

/**
 Attempt to disconnect from the device.

 The passed block is called when the session is ended and connections have been
 terminated. If the `error` parameter of the callback is `nil`, disconnection was successful.

 Equivalent to calling disconnectWithFlags:completionCallback:callbackQueue: with a `nil` `flags` parameter.

 @param callback The callback to be called when disconnection succeeds or fails.
 @param queue The queue on which to trigger the callback.
 */
-(void)disconnect:(nullable CBLErrorableOperationCallback)callback
    callbackQueue:(nullable dispatch_queue_t)queue;

// -------------
// @name Querying Available Functionality
// -------------

/** Returns a bitmask of the supported advanced functionality of this camera. */
@property (nonatomic, readonly) CBLCameraSupportedFunctionality supportedFunctionality;

/** Returns `YES` if the camera supports the given functionality, otherwise `NO`.
 
 @param functionality The functionality to test for.
 */
-(BOOL)supportsFunctionality:(CBLCameraSupportedFunctionality)functionality;

/** Returns a bitmask of the current available command categories. */
@property (nonatomic, readonly) CBLCameraAvailableCommandCategory currentCommandCategories;

/** Returns `YES` if the camera currently supports the given category, otherwise `NO`. 
 
 @param category The category to test for.
 */
-(BOOL)currentCommandCategoriesContainsCategory:(CBLCameraAvailableCommandCategory)category;

/** Returns `YES` if the camera is able to switch to the given category combination, otherwise `NO`. 
 
 @param categories The command category combination to check if the camera supports.
 */
-(BOOL)supportsCommandCategories:(CBLCameraAvailableCommandCategory)categories;

/** Attempt to switch the camera into a mode that supports the given category combination.

 It is not guaranteed that the camera's current command categories will end up exactly the same as what's passed
 in, but if the method succeeds you can expect that they will contain the requested category/categories.

 For example, some cameras support both stills shooting and filesystem access at the same time. Requesting the
 command category `.stillsShooting` will succeed, but the camera will end up with current command categories of
 `[.stillsShooting, .filesystemAccess]`.

 In general, it's safe to call this method with a single category (for example, if you want to shoot video,
 `.videoRecording`) — CascableCore will put the camera into the closest sensible mode that supports that category.

 To check if the camera supports your desired command category/categories, use `-supportsCommandCategories:`.
 
 @param categories The command categories the camera should accept.
 @param block The block to be called when the camera has switched modes and is able to accept commands in the given categories, or an error occurs.
 */
-(void)setCurrentCommandCategories:(CBLCameraAvailableCommandCategory)categories completionCallback:(nonnull CBLErrorableOperationCallback)block;

@end

// -------------
// @name Live View
// -------------

/** Reasons the live view stream can stop. */
typedef NS_ENUM(NSInteger, CBLCameraLiveViewTerminationReason) {
    /** The stream ended normally, due to mode switching or an explicit call to `endLiveViewStream`. */
    CBLCameraLiveViewTerminationReasonEndedNormally,
    /** The stream could not start because there is already a stream running from this camera. */
    CBLCameraLiveViewTerminationReasonAlreadyStreaming,
    /** The stream failed, due to disconnection or another failure. */
    CBLCameraLiveViewTerminationReasonFailed
} NS_SWIFT_NAME(LiveViewTerminationReason);

/**
 The live view frame delivery callback.

 @param frame A live view frame from the camera.
 @param completionHandler A completion handler to inform the camera that you're ready for the next frame. This MUST be called, and can be called from any thread.
 */
typedef void (^CBLCameraLiveViewFrameDelivery)(id <CBLCameraLiveViewFrame> _Nonnull frame, dispatch_block_t _Nonnull completionHandler) NS_SWIFT_NAME(LiveViewFrameDelivery);

/**
 The handler for the live view stream ending.

 @param reason The reason the live view stream ended.
 @param error The error that caused the failure, if `reason` is `CBLCameraLiveViewTerminationReasonFailed`.
 */
typedef void (^CBLCameraLiveViewTerminationHandler)(CBLCameraLiveViewTerminationReason reason, NSError * _Nullable error) NS_SWIFT_NAME(LiveViewTerminationHandler);

/** If set to `@YES`, image data will not be decoded in delivered live view frames, so the `image` property of delivered
 frames will be `nil`. All other properties will be populated as normal, including `rawImageData`. This can be useful if
 you have a frame rendering pipeline that doesn't need `NSImage`/`UIImage` objects, as turning off image decoding can
 save a significant amount of CPU resources.

 When omitted from the options dictionary, the assumed value for this option is `@NO`.
 */
static NSString * _Nonnull const CBLLiveViewOptionSkipImageDecoding = @"CBLLiveViewOptionSkipImageDecoding";

/** If set to `@YES` and if supported by the particular camera model you're connected to, live view will be configured
 to favour lower-quality image data in an attempt to achieve a higher live view frame rate. If set to `@NO` (or omitted),
 live view will be configured to favour the highest quality image.

 Setting this option after live view has started (with `-applyLiveViewStreamOptions:`) has no effect.

 When omitted from the options dictionary, the assumed value for this option is `@NO`.
 */
static NSString * _Nonnull const CBLLiveViewOptionFavorHighFrameRate = @"CBLLiveViewOptionFavorHighFrameRate";

/** Camera live view methods. */
NS_SWIFT_NAME(CameraLiveView)
@protocol CBLCameraLiveView <NSObject>

/**
 Start streaming the live view image from the camera.

 @note The frame delivery block has a completion handler, which MUST be called in order to receive the next frame. The completion handler
 can be called from any thread, and should be called when you're ready for the next frame. This allows frame delivery to correctly throttle
 without backing up frames if your image processing/display is slower than the delivery rate from the camera.

 @param delivery The frame delivery block.
 @param deliveryQueue The queue on which to deliver frames. If you pass `nil`, the main queue will be used.
 @param terminationHandler The callback to call when the live view stream ends. Will be called on the main queue.
 */
-(void)beginLiveViewStreamWithDelivery:(nonnull CBLCameraLiveViewFrameDelivery)delivery
                         deliveryQueue:(nullable dispatch_queue_t)deliveryQueue
                    terminationHandler:(nonnull CBLCameraLiveViewTerminationHandler)terminationHandler;

/**
 Start streaming the live view image from the camera with the given options.

 @note The frame delivery block has a completion handler, which MUST be called in order to receive the next frame. The completion handler
 can be called from any thread, and should be called when you're ready for the next frame. This allows frame delivery to correctly throttle
 without backing up frames if your image processing/display is slower than the delivery rate from the camera.

 @param delivery The frame delivery block.
 @param deliveryQueue The queue on which to deliver frames. If you pass `nil`, the main queue will be used.
 @param options Custom options for the live view session. See `CBLLiveViewOption…` constants for details.
 @param terminationHandler The callback to call when the live view stream ends. Will be called on the main queue.
 */
-(void)beginLiveViewStreamWithDelivery:(nonnull CBLCameraLiveViewFrameDelivery)delivery
                         deliveryQueue:(nullable dispatch_queue_t)deliveryQueue
                               options:(nullable NSDictionary <NSString *, id> *)options
                    terminationHandler:(nonnull CBLCameraLiveViewTerminationHandler)terminationHandler;

/**
 Apply new options to the running stream live view stream. Options not included in the passed dictionary will not be changed.

 Due to the threaded nature of live view streaming, a number of frames may be delivered between calling this method and
 the new options taking effect.

 @note If no live view stream is running, this method has no effect.

 @param options The options to apply to the running live view stream.
 */
-(void)applyLiveViewStreamOptions:(nonnull NSDictionary <NSString *, id> *)options;

/** Ends the current live view stream, if one is running. Will cause the stream's termination handler to be called with `CBLCameraLiveViewTerminationReasonEndedNormally`. */
-(void)endLiveViewStream;

/** Returns `YES` if the camera is currently streaming a live view image. */
@property (readonly) BOOL liveViewStreamActive;

/**
 Attempt to set the current live view zoom level.

 If the camera doesn't support the functionality `CBLCameraSupportedFunctionalityZoomableLiveView`, this operation will fail. To check the zoom level,
 see the zoomLevel property on `id <CBLCameraLiveViewFrame>`.

 @param liveViewZoomLevel The new zoom level to use.
 @param block The callback to call when the operation is complete.
 */
-(void)setLiveViewZoomLevel:(CBLCameraLiveViewZoomLevel)liveViewZoomLevel completionCallback:(nullable CBLErrorableOperationCallback)block;

/**
 Attempt to zoom in to live view by cropping in on the camera's side.

 The given crop rectangle must match the aspect ratio of the live view frame's `aspect`, must be completely contained
 within it, and must be larger or equal in size to the live view frame's `minimumCropSize`. The rect may be adjusted
 by CascableCore to match the camera's requirements. To check the final cropped frame, see live view frame's
 `imageFrameInAspect` property once the operation completes.

 Note that it may take a few frames for crop geometry to update after this operation finishes, due to frame buffers and etc.

 If the camera doesn't support the functionality `CBLCameraSupportedFunctionalityCroppableLiveView`, this operation will fail.

 @param cropRect The rectangle at which to crop live view, relative to a live view frame's `aspect`.
 @param block The callback to call when the operation is complete.
 */
-(void)setLiveViewCrop:(CGRect)cropRect completionCallback:(nullable CBLErrorableOperationCallback)block;

/**
 Attempt to reset the live view crop to the uncropped state.

 If the camera doesn't support the functionality `CBLCameraSupportedFunctionalityCroppableLiveView`, this operation will fail.

 @param block The callback to call when the operation is complete.
 */
-(void)resetLiveViewCrop:(nullable CBLErrorableOperationCallback)block;

@end

/** Camera property methods. */
NS_SWIFT_NAME(CameraProperties)
@protocol CBLCameraProperties <NSObject>

// -------------
// @name Clock
// -------------

/**
 Attempt to update the camera's internal clock to the given date/time.

 @note Olympus cameras can only update their time when the current command categories contains `CBLCameraAvailableCommandCategoryFilesystemAccess`.

 Only cameras that contain `CBLCameraSupportedFunctionalityUpdateClock` in their functionality flags support this operation.

 For cameras that support changing timezones, the camera's timezone will be set to the current system timezone and the time will be
 set correctly — e.g., passing `date` as `[NSDate new]` will set the camera to the system's timezone and the time will match the system's time.
 If the camera's time zone is CET before calling this method and the system's time zone is PST, setting 2017-01-01 12:00:00 will set the camera
 to 2017-01-01 12:00:00 PST (equivalent to 2017-01-01 20:00:00 CET).

 For cameras that don't support changing timezones, the camera's time will be set to the given time and the camera's time zone (if any) will
 remain unchanged  — e.g., passing `date` as `[NSDate new]` will set the time to the system's time, but the timezone will not change.
 If the camera's time zone is CET before calling this method and the system's time zone is PST, setting 2017-01-01 12:00:00 will set the camera
 to 2017-01-01 12:00:00 CET.

 In all cases, the user-visible date and time on the camera will match the value of `date` passed to this method. However,
 depending on the camera, the time zone may be incorrect, meaning that the camera's system time may not technically be the intended time.

 - Canon: Timezone and DST will be set correctly.
 - Nikon: Timezone cannot be changed.
 - Olympus: Timezone will be set correctly.
 - Sony: System clock cannot be changed at all (this method will always return an error).
 - Panasonic: System clock cannot be changed at all (this method will always return an error).
 - Fujifilm: System clock cannot be changed at all (this method will always return an error).

 @param date The date/time to set.
 @param block The block to trigger when the value has been set or an error occurs.
 */
-(void)updateClockTo:(nonnull NSDate *)date completionCallback:(nullable CBLErrorableOperationCallback)block NS_SWIFT_NAME(updateClock(to:completionCallback:));

// -------------
// @name Autoexposure
// -------------

/** Returns the latest auto exposure measurement from the camera, or `nil` if AE is not currently running. */
@property (readonly, nonatomic, nullable) CBLCameraAEResult *autoexposureResult;

// -------------
// @name Camera Properties
// -------------

/// The known property identifiers, encoded as `CBLPropertyIdentifier` values in `NSNumber` objects. Observable with key-value observing.
@property (nonatomic, readonly, copy, nonnull) NSArray <NSNumber *> *knownPropertyIdentifiers;

/// Returns a property object for the given identifier. If the property is currently unknown, returns an object
/// with `currentValue`, `validSettableValues`, etc set to `nil`.
///
/// The returned object is owned by the receiver, and the same object will be returned on subsequent calls to this
/// method with the same identifier.
///
/// @param identifier The property identifier to get a property object for.
-(id <CBLCameraProperty> _Nonnull)propertyWithIdentifier:(CBLPropertyIdentifier)identifier;

/// Returns an array of property objects for the given category that have a non-nil `currentValue`.
///
/// @param category The category for which to get properties.
-(NSArray <id <CBLCameraProperty>> * _Nonnull)populatedPropertiesInCategory:(CBLPropertyCategory)category;

@end

/** Camera filesystem methods. */
NS_SWIFT_NAME(CameraFileSystem)
@protocol CBLCameraFileSystem <NSObject>

// -------------
// @name Accessing The Filesystem
// -------------

/** Returns an array of `CBLFileStorage` instances representing the storage within the device. */
@property (nonatomic, readonly, copy, nullable) NSArray <id <CBLFileStorage>> *storageDevices;

@end

/** A focus drive direction. */
typedef NS_ENUM(NSInteger, CBLFocusDriveDirection) {
    /** Drive the focus towards the camera. */
    CBLFocusDriveDirectionTowardsCamera,
    /** Drive the focus towards infinity. */
    CBLFocusDriveDirectionTowardsInfinity
} NS_SWIFT_NAME(FocusDriveDirection);

/** A focus drive amount. */
typedef NS_ENUM(NSInteger, CBLFocusDriveAmount) {
    /** A very small amount of movement. */
    CBLFocusDriveAmountSmall,
    /** A medium amount of movement. */
    CBLFocusDriveAmountMedium,
    /** A large amount of movement. */
    CBLFocusDriveAmountLarge
} NS_SWIFT_NAME(FocusDriveAmount);

/** Camera focus and shutter methods. */
NS_SWIFT_NAME(CameraFocusAndShutter)
@protocol CBLCameraFocusAndShutter <NSObject>

// -------------
// @name Autofocus Setup
// -------------

/** Returns the current autofocus info from the camera. */
@property (readonly, nonatomic, nullable) id <CBLFocusInfo> focusInfo;

/** Sets the given AF point as the active point.

 @param point The AF point to set as active.
 @param block The block to trigger when the active AF point has been set or an error occurs.
 */
-(void)setActiveAutoFocusPoint:(nonnull id <CBLFocusPoint>)point completionCallback:(nullable CBLErrorableOperationCallback)block;

/** Returns `YES` if the camera currently supports freeform "touch" AF, otherwise `NO`. */
@property (readonly, nonatomic) BOOL supportsTouchAF;

/** Sets the camera's touch AF position, if available.

 @param center The centre of the touch AF point, expressed in the current live view frame's aspect.
 @param block The callback to call when the operation is complete.
 */
-(void)touchAFAtPoint:(CGPoint)center completionCallback:(nullable CBLErrorableOperationCallback)block;

// -------------
// @name Engaging Autofocus and Shutter
// -------------

/** Returns `YES` if autofocus is currently engaged, otherwise `NO`. */
@property (nonatomic, readonly) BOOL autoFocusEngaged;

/** Engages autofocus.

 @note Autofocus will remain engaged until `disengageAutoFocus:` is called. While autofocus is engaged,
 functionality not directly to taking a shot will be unavailable. Live view (if on before this method is called)
 will continue to stream, and you can use the `engageShutter:`, `disengageShutter:`, and `disengageAutoFocus:`
 methods.

 The typical ordering for taking a photograph using these methods is as follows:

 - `engageAutoFocus:`
 - `engageShutter:`
 - `disengageShutter:`
 - `disengageAutoFocus:`

 @param block The block to trigger when autofocus has been engaged or an error occurs.
 */
-(void)engageAutoFocus:(nullable CBLErrorableOperationCallback)block;

/** Disengages autofocus.

 @param block The block to trigger when autofocus has been disengaged or an error occurs.
 */
-(void)disengageAutoFocus:(nullable CBLErrorableOperationCallback)block;

/** Returns `YES` if the shutter is currently engaged, otherwise `NO`. */
@property (nonatomic, readonly) BOOL shutterEngaged;

/** Engages the shutter.

 The shutter will remain "engaged" until `disengageShutter:` is called. However,
 if the camera is set to take an exposure of a specific length (i.e., anything other than "bulb"
 mode) the timing of these calls will have no effect on the exposure.

 @note This may not engage autofocus if the camera is configured to use back-button autofocus.

 @note Even if you don't call `engageAutoFocus:` prior to this method, calling this method may cause `autoFocusEngaged`
       to become `YES`. It is the client's responsibility to detect this and called `disengageAutoFocus:` if needed.

 @param block The block to trigger when the shutter has been engaged or an error occurs.
 */
-(void)engageShutter:(nullable CBLErrorableOperationCallback)block;

/** Disengages the shutter.

 @param block The block to trigger when the shutter has been disengaged or an error occurs.
 */
-(void)disengageShutter:(nullable CBLErrorableOperationCallback)block;

/** Takes a single photo.

 This method will (optionally) engage autofocus, engage the shutter, disengage the shutter and
 disengage autofocus. Think of it as a "Take a photo!" button.

 @param triggerAutoFocus Pass `YES` to explicitly engage autofocus during the process, otherwise `NO`.
 @param block The block to trigger when the operation completes or an error occurs.
 */
-(void)invokeOneShotShutterExplicitlyEngagingAutoFocus:(BOOL)triggerAutoFocus
                                    completionCallback:(nullable CBLErrorableOperationCallback)block;

// -------------
// @name Shot Previews
// -------------

/** Adds an observer to be notified when a shot preview is available.

 @note Only cameras that support the `CBLCameraSupportedFunctionalityShotPreview` functionality flag will trigger shot preview callbacks.
 
 @param block The block to be called when a shot preview is available. Will be called on the main thread.
 */
-(nonnull CBLCameraObserverToken *)addShotPreviewObserver:(nonnull CBLCameraShotPreviewAvailableBlock)block;

/** Removes a previously registered shot preview observer.

 @param token The token for the observer block to be removed.
 */
-(void)removeShotPreviewObserverWithToken:(nonnull CBLCameraObserverToken *)token NS_SWIFT_NAME(removeShotPreviewObserver(with:));

// -------------
// @name Direct Focus Manipulation
// -------------

/**
 Drive the camera's focus a certain amount in the given direction. Requires that the camera has the `CBLCameraSupportedFunctionalityDirectFocusManipulation`
 functionality available.

 Direct focus manipulation with this method requires that the camera has live view enabled, and that autofocus is engaged. If the camera isn't in
 the correct state, an error of `CBLErrorCodeNotAvailable` will be returned. In some situations, you may receive an error of
 `CBLErrorCodeFocusDidNotMove` — this indicates that either the focus is already at the end of its travel in the specified direction, or that the focus
 didn't move for some other reason.

 @param amount The amount to move the focus. The actual change in focus will depend on the camera and lens being used.
 @param direction The direction in which the focus should move.
 @param callback The block to trigger when the operation completes or an error occurs.
 */
-(void)driveFocusByAmount:(CBLFocusDriveAmount)amount
              inDirection:(CBLFocusDriveDirection)direction
       completionCallback:(nullable CBLErrorableOperationCallback)callback
NS_SWIFT_NAME(driveFocus(amount:direction:completionCallback:));

@end

/** Video recording timer types. */
typedef NS_ENUM(NSInteger, CBLVideoTimerType) {
    /** No video timer is currently available. */
    CBLVideoTimerTypeNone,
    /** The video timer is counting down to zero (i.e., is counting the recording time remaining). */
    CBLVideoTimerTypeCountingDown,
    /** The video timer is counting up from zero (i.e., is counting the length of the current clip). */
    CBLVideoTimerTypeCountingUp
} NS_SWIFT_NAME(VideoTimerType);

/** A video timer value. Only valid during video recording. */
NS_SWIFT_NAME(VideoTimerValue)
@protocol CBLVideoTimerValue <NSObject, NSCopying>

/** The timer type. */
@property (nonatomic, readonly) CBLVideoTimerType type;

/** The current value of the timer. Will be zero if the video timer is invalid. */
@property (nonatomic, readonly) NSTimeInterval value;

@end

/** Video recording methods. */
NS_SWIFT_NAME(CameraVideoRecording)
@protocol CBLCameraVideoRecording <NSObject>

/**
 Returns `YES` if the camera is currently recording video, otherwise `NO`. Will update if video recording is started
 or stopped using the camera's on-body controls, or if video recording stopped due to the card being full etc.

 Can be observed with Key-Value Observing.
 */
@property (nonatomic, readonly) BOOL isRecordingVideo;

/**
 If available, returns the current value of the camera's video recording timer. Can be observed with Key-Value Observing.

 The returned value is immutable — a new value will be created when the timer updates.

 Will be `nil` when the camera isn't recording video.
 */
@property (nonatomic, readonly, nullable, copy) id <CBLVideoTimerValue> currentVideoTimerValue;

/**
 Start video recording.

 Will fail if the camera is already recording video, the camera isn't in a mode that allows video recording, or if
 some other condition prevents video recording to start (not enough space on the camera's storage card, etc).
 */
-(void)startVideoRecording:(nullable CBLErrorableOperationCallback)completionHandler NS_SWIFT_NAME(startVideoRecording(_:));

/** End video recording. */
-(void)endVideoRecording:(nullable CBLErrorableOperationCallback)completionHandler NS_SWIFT_NAME(endVideoRecording(_:));

@end
