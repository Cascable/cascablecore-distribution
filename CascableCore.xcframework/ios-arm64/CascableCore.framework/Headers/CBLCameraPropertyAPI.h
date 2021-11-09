//
//  CBLCameraPropertyAPI.h
//  CascableCore
//
//  Created by Daniel Kennett (Cascable) on 2021-01-21.
//  Copyright © 2021 Cascable AB. All rights reserved.
//

@import Foundation;

@protocol CBLCamera;
@protocol CBLCameraProperty;
@protocol CBLPropertyValue;
@protocol CBLExposurePropertyValue;

@protocol CBLUniversalExposurePropertyValue;

/// Property identifiers.
typedef NS_ENUM(NSUInteger, CBLPropertyIdentifier) {
    /// The camera's ISO speed setting. Common values will be of type CBLISOValue.
    CBLPropertyIdentifierISOSpeed,
    /// The camera's shutter speed setting. Common values will be of type CBLShutterSpeedValue.
    CBLPropertyIdentifierShutterSpeed,
    /// The camera's aperture setting. Common values will be of type CBLApertureValue.
    CBLPropertyIdentifierAperture,
    /// The camera's exposure compensation setting. Common values will be of type CBLExposureCompensationValue.
    CBLPropertyIdentifierExposureCompensation,
    /// The camera's battery level. Common values will be of type `CBLPropertyCommonValueBatteryLevel`.
    CBLPropertyIdentifierBatteryLevel,
    /// The camera's power source. Common values will be of type `CBLPropertyCommonValuePowerSource`.
    CBLPropertyIdentifierPowerSource,
    /// The camera's autofocus system setting (area, face detection, etc). Common values will be of type `CBLPropertyCommonValueAFSystem`.
    CBLPropertyIdentifierAFSystem,
    /// The camera's focus mode setting (manual, single, continuous, etc). Common values will be of type `CBLPropertyCommonValueFocusMode`.
    CBLPropertyIdentifierFocusMode,
    /// The camera's drive mode setting (single, continuous, timer, etc). Common values will be of type `CBLPropertyCommonValueDriveMode`.
    CBLPropertyIdentifierDriveMode,
    /// The camera's autoexposure mode setting (M, P, Tv, Av, etc). Common values will be of type `CBLPropertyCommonValueAutoExposureMode`.
    CBLPropertyIdentifierAutoExposureMode,
    /// The camera's in-camera bracketing setting. Common values will be of type `CBLPropertyCommonValueBoolean`.
    CBLPropertyIdentifierInCameraBracketingEnabled,
    /// The camera's mirror lockup enabled setting. Common values will be of type `CBLPropertyCommonValueBoolean`.
    CBLPropertyIdentifierMirrorLockupEnabled,
    /// The camera's current mirror lockup stage. Common values will be of type `CBLPropertyCommonValueMirrorLockupStage`.
    CBLPropertyIdentifierMirrorLockupStage,
    /// Whether the camera is current executing depth-of-field preview. Common values will be of type `CBLPropertyCommonValueBoolean`.
    CBLPropertyIdentifierDOFPreviewEnabled,
    /// The camera's reading of how many shots are available on its storage card(s). The common value will be a freeform integer containing the reading.
    CBLPropertyIdentifierShotsAvailable,
    /// The camera's lens status.
    CBLPropertyIdentifierLensStatus,
    /// The camera's "Color Tone" setting.
    CBLPropertyIdentifierColorTone,
    /// The camera's "Art Filter" setting.
    CBLPropertyIdentifierArtFilter,
    /// Whether the camera is currently using digital zoom. Common values will be of type `CBLPropertyCommonValueBoolean`.
    CBLPropertyIdentifierDigitalZoom,
    /// The camera's white balance setting. Common values will be of type `CBLPropertyCommonValueWhiteBalance`.
    CBLPropertyIdentifierWhiteBalance,
    /// The camera's noise reduction setting.
    CBLPropertyIdentifierNoiseReduction,
    /// The camera's image quality setting.
    CBLPropertyIdentifierImageQuality,
    /// The camera's light meter status. Common values will be of type `CBLPropertyCommonValueLightMeterStatus`.
    CBLPropertyIdentifierLightMeterStatus,
    /// The camera's current light meter reading. Common values will be of type CBLExposureCompensationValue.
    CBLPropertyIdentifierLightMeterReading,
    /// The camera's exposure metering mode setting.
    CBLPropertyIdentifierExposureMeteringMode,
    /// Whether the camera is ready to take a shot. Common values will be of type `CBLPropertyCommonValueBoolean`.
    CBLPropertyIdentifierReadyForCapture,
    CBLPropertyIdentifierMax,

    CBLPropertyIdentifierUnknown = NSNotFound
} NS_SWIFT_NAME(PropertyIdentifier);

/// Property categories, which can be useful for grouping properties into sections for the user.
typedef NS_ENUM(NSInteger, CBLPropertyCategory) {
    /// The category of the property is unknown.
    CBLPropertyCategoryUnknown,
    /// Shutter speed, ISO, EV, etc. Common values are guaranteed to conform to CBLExposureProperty.
    CBLPropertyCategoryExposureSetting,
    /// Focus modes, etc — settings that affect how the image is captured.
    CBLPropertyCategoryCaptureSetting,
    /// White balance, etc — settings that affect the image.
    CBLPropertyCategoryImagingSetting,
    /// File format, etc — settings that don't affect the image.
    CBLPropertyCategoryConfigurationSetting,
    /// Shots remaining, battery, etc — information about the camera that's usually read-only.
    CBLPropertyCategoryInformation
} NS_SWIFT_NAME(PropertyCategory);

/// Option set for identifying the type of change that occurred to a property. For performance reasons, CascableCore
/// may group value and valid values changes into one callback.
typedef NS_OPTIONS(NSUInteger, CBLPropertyChangeType) {
    /// If the option set contains this value, the current value of the property changed.
    CBLPropertyChangeTypeValue = 1 << 0,
    /// If the option set contains this value, the pending value of the property changed.
    CBLPropertyChangeTypePendingValue = 1 << 1,
    /// If the option set contains this value, the valid settable values of the property changed.
    CBLPropertyChangeTypeValidSettableValues = 1 << 2
} NS_SWIFT_NAME(PropertyChangeType);

/// A property common value. Values will be from one of the appropriate common value enums as defined below.
typedef NSInteger CBLPropertyCommonValue NS_SWIFT_NAME(PropertyCommonValue);

/// If there isn't a common value translation for a property value, APIs will instead return this value.
NS_SWIFT_NAME(PropertyCommonValueNone) static CBLPropertyCommonValue const CBLPropertyCommonValueNone = -1;

/// The block callback signature for property observations.
///
/// @param property The property that fired the change.
/// @param type The change type(s) that occurred. See `CBLPropertyChangeType` for details.
typedef void (^CBLCameraPropertyObservationCallback)(id <CBLCameraProperty> _Nonnull property, CBLPropertyChangeType type) NS_SWIFT_NAME(CameraPropertyObservationCallback);

/// An object for managing property value change notifications. When you add an observer to a property, store the returned
/// token somewhere in order to keep the observation alive. To remove the observation, you can simply remove all strong
/// references to its token, or explicitly call `invalidate` on it.
NS_SWIFT_NAME(CameraPropertyObservation)
@protocol CBLCameraPropertyObservation <NSObject>

/// Invalidate the observation. Will also be called on `dealloc`.
-(void)invalidate;

@end

/// An object representing the values for a property on the camera.
NS_SWIFT_NAME(CameraProperty)
@protocol CBLCameraProperty <NSObject>

/// The property's category.
@property (nonatomic, readonly) CBLPropertyCategory category;

/// The property's identifier.
@property (nonatomic, readonly) CBLPropertyIdentifier identifier;

/// The camera from which the property is from.
@property (nonatomic, readonly, weak, nullable) id <CBLCamera> camera;

/// The property's display name.
@property (nonatomic, readonly, copy, nullable) NSString *localizedDisplayName;

/// The current value of the property. Observable with key-value observing.
@property (nonatomic, readonly, nullable) id <CBLPropertyValue> currentValue;

/// Returns the value currently in the process of being set, if any. Observable with key-value observing.
@property (nonatomic, readonly, nullable) id <CBLPropertyValue> pendingValue;

/// The values that are considered valid for this property. Observable with key-value observing.
@property (nonatomic, readonly, copy, nullable) NSArray <id <CBLPropertyValue>> *validSettableValues;

/// Add an observer to the property.
///
/// The observer callback will be called on the main thread when either the `currentValue` or `validSettableValues`
/// properties change. If possible, these changes will be consolidated into one callback rather than two.
///
/// The returned observation object is _not_ retained by the receiver, and the observation will be invalidated
/// when the object is deallocated. Make sure you store this token somewhere to keep the observation active.
///
/// @param observerCallback The observer block to be triggered, on the main thread, when changes occur.
/// @return Returns an object to manage the lifecycle of the observation.
-(id <CBLCameraPropertyObservation> _Nonnull)addObserver:(CBLCameraPropertyObservationCallback _Nonnull)observerCallback;

/// Remove a previously-registered observer from this property. Equivalent to calling `-invalidate` on the observer object.
///
/// @param observer The observer to remove.
-(void)removeObserver:(id <CBLCameraPropertyObservation> _Nonnull)observer;

/// Attempt to find a valid settable value for the given common value.
///
/// @param commonValue The common value to find a value for. The intent must match the property identifier.
/// @return Returns a valid settable value for the given intent, or `nil` if no value matches.
-(id <CBLPropertyValue> _Nullable)validValueMatchingCommonValue:(CBLPropertyCommonValue)commonValue;

/// Attempt to set a new value for the property. The value must be in the `validSettableValues` property.
///
/// @param newValue The value to set.
/// @param queue The queue on which to call the completion handler.
/// @param completionHandler The completion handler to call when the operation succeeds or fails.
-(void)setValue:(id <CBLPropertyValue> _Nonnull)newValue completionQueue:(dispatch_queue_t _Nonnull)queue
    completionHandler:(CBLErrorableOperationCallback _Nonnull)completionHandler;

/// Attempt to set a new value for the property. The value must be in the `validSettableValues` property.
///
/// @param newValue The value to set.
/// @param completionHandler The completion handler to call on the main queue when the operation succeeds or fails.
-(void)setValue:(id <CBLPropertyValue> _Nonnull)newValue completionHandler:(CBLErrorableOperationCallback _Nonnull)completionHandler;

@end

/// A property that exposes its values as universal exposure values.
NS_SWIFT_NAME(ExposureProperty)
@protocol CBLExposureProperty <CBLCameraProperty>

/// Returns the current value as a universal exposure value.
@property (nonatomic, readonly, copy, nullable) id <CBLExposurePropertyValue> currentExposureValue;

/// Returns the valid settable values as an array of universal exposure values.
@property (nonatomic, readonly, copy, nullable) NSArray <id <CBLExposurePropertyValue>> *validSettableExposureValues;

/// Returns the item value in `validSettableValues` that is considered the "zero" value.
/// For most properties this will be the first item in the array, but in some (for example,
/// E.V.) it will be a value somewhere in the middle.
///
/// Values at a lesser index than this value in `validSettableValues` are considered to
/// be negative. This can be useful when constructing UI.

/// Guaranteed to return a non-nil value if `validSettableValues` isn't empty.
@property (nonatomic, readonly, copy, nullable) id <CBLExposurePropertyValue> validZeroValue;

/// Returns the value in `validSettableValues` that, when set, will cause the camera to
/// attempt to derive the value for this property automatically.
///
/// If there is no such value, returns `nil`.
@property (nonatomic, readonly, copy, nullable) id <CBLExposurePropertyValue> validAutomaticValue;

/// Attempt to find a valid settable value for the given exposure value.
///
/// @param exposureValue The exposure value to find a value for. The type must match the property identifier.
/// @return Returns a valid settable value for the given exposure value, or `nil` if no value matches.
-(id <CBLExposurePropertyValue> _Nullable)validValueMatchingExposureValue:(id <CBLUniversalExposurePropertyValue> _Nonnull)exposureValue;

@end

/// A property value. This could either be the current value of a property, or something in the list of values that can be set.
NS_SWIFT_NAME(PropertyValue)
@protocol CBLPropertyValue <NSObject>

/// The common value that this value matches, or `CBLPropertyCommonValueNone` if it doesn't match any common value.
@property (nonatomic, readonly) CBLPropertyCommonValue commonValue;

/// A localized display value for the value. May be `nil` if the value is unknown to CascableCore and
/// a display value is not provided by the camera.
@property (nonatomic, readonly, copy, nullable) NSString *localizedDisplayValue;

/// A string value for the value. Will always return *something*, but the quality is not guaranteed — particularly
/// if the value is unknown to CascableCore and a display value is not provided by the camera.
@property (nonatomic, readonly, copy, nonnull) NSString *stringValue;

/// An opaque value representing the property. Not guaranteed to be anything in particular, as this is an internal
/// implementation detail for each particular camera.
@property (nonatomic, readonly, nonnull) id opaqueValue;

@end

/// A property value that exposes its values as universal exposure values.
NS_SWIFT_NAME(ExposurePropertyValue)
@protocol CBLExposurePropertyValue <CBLPropertyValue>

/// Returns the value as a universal exposure value.
@property (nonatomic, readonly, copy, nonnull) id <CBLUniversalExposurePropertyValue> exposureValue;

@end

// MARK: - Common Values

/// Boolean common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueBoolean) {
    /// The value is equivalent to "false" or "off".
    CBLPropertyCommonValueBooleanFalse = 0,
    /// The value is equivalent to "true" or "on".
    CBLPropertyCommonValueBooleanTrue = 1
} NS_SWIFT_NAME(PropertyCommonValueBoolean);

/// Autoexposure mode common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueAutoExposureMode) {
    /// The value is equivalent to a fully automatic/"green box" mode.
    CBLPropertyCommonValueAutoExposureModeFullyAutomatic = 50,
    /// The value is equivalent to the P/Program mode.
    CBLPropertyCommonValueAutoExposureModeProgramAuto,
    /// The value is equivalent to the Tv/S shutter priority mode.
    CBLPropertyCommonValueAutoExposureModeShutterPriority,
    /// The value is equivalent to the Av/A aperture priority mode.
    CBLPropertyCommonValueAutoExposureModeAperturePriority,
    /// The value is equivalent to the M/manual mode.
    CBLPropertyCommonValueAutoExposureModeFullyManual,
    /// The value is equivalent to the B/bulb mode.
    CBLPropertyCommonValueAutoExposureModeBulb,
    /// The value is equivalent to a "flexible priority" mode, such as Canon's Fv.
    CBLPropertyCommonValueAutoExposureModeFlexiblePriority
} NS_SWIFT_NAME(PropertyCommonValueAutoExposureMode);

/// White balance common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueWhiteBalance) {
    /// The value is equivalent to an automatic white balance setting.
    CBLPropertyCommonValueWhiteBalanceAuto = 100,
    /// The value is equivalent to daylight/sunny white balance.
    CBLPropertyCommonValueWhiteBalanceDaylight,
    /// The value is equivalent to shade white balance.
    CBLPropertyCommonValueWhiteBalanceShade,
    /// The value is equivalent to cloudy white balance.
    CBLPropertyCommonValueWhiteBalanceCloudy,
    /// The value is equivalent to tungsten white balance.
    CBLPropertyCommonValueWhiteBalanceTungsten,
    /// The value is equivalent to fluorescent white balance.
    CBLPropertyCommonValueWhiteBalanceFluorescent,
    /// The value is equivalent to flash white balance.
    CBLPropertyCommonValueWhiteBalanceFlash,
    /// The value is equivalent to a custom white balance.
    CBLPropertyCommonValueWhiteBalanceCustom,
    /// The value is equivalent to a second custom white balance for cameras that support multiple custom values.
    CBLPropertyCommonValueWhiteBalanceCustom2,
    /// The value is equivalent to a third custom white balance for cameras that support multiple custom values.
    CBLPropertyCommonValueWhiteBalanceCustom3
} NS_SWIFT_NAME(PropertyCommonValueWhiteBalance);

/// Focus mode common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueFocusMode) {
    /// The value is equivalent to the manual focus mode.
    CBLPropertyCommonValueFocusModeManual = 150,
    /// The value is equivalent to the single drive focus mode (once focus is acquired, the camera stops focusing).
    CBLPropertyCommonValueFocusModeSingleDrive,
    /// The value is equivalent to the continuous drive focus mode (the camera continually performs autofocus until told to stop).
    CBLPropertyCommonValueFocusModeContinuousDrive,
} NS_SWIFT_NAME(PropertyCommonValueFocusMode);

/// Battery level common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueBatteryLevel) {
    /// The value is equivalent to a full battery.
    CBLPropertyCommonValueBatteryLevelFull = 200,
    /// The value is equivalent to a 75% full battery.
    CBLPropertyCommonValueBatteryLevelThreeQuarters,
    /// The value is equivalent to a 50% full battery.
    CBLPropertyCommonValueBatteryLevelHalf,
    /// The value is equivalent to a 25% full battery.
    CBLPropertyCommonValueBatteryLevelOneQuarter,
    /// The value is equivalent to an empty battery. Typically the camera is flashing a red battery symbol at this point.
    CBLPropertyCommonValueBatteryLevelEmpty
} NS_SWIFT_NAME(PropertyCommonValueBatteryLevel);

/// Power source common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValuePowerSource) {
    /// The value is equivalent to a battery power source.
    CBLPropertyCommonValuePowerSourceBattery = 210,
    /// The value is equivalent to a mains or external power source.
    CBLPropertyCommonValuePowerSourceMainsPower
} NS_SWIFT_NAME(PropertyCommonValuePowerSource);

/// Light meter common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueLightMeterStatus) {
    /// The value is equivalent to the camera's light meter not being in use.
    CBLPropertyCommonValueLightMeterStatusNotInUse = 250,
    /// The value is equivalent to the camera's light meter being operational and providing a valid reading.
    CBLPropertyCommonValueLightMeterStatusValidReading,
    /// The value is equivalent to the camera's light meter being operational but the reading is outside valid bounds
    /// (for example, the current settings will produce an image completely over- or under-exposed.
    CBLPropertyCommonValueLightMeterStatusBeyondBounds
} NS_SWIFT_NAME(PropertyCommonValueLightMeterStatus);

/// Mirror lockup common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueMirrorLockupStage) {
    /// The value is equivalent to the camera's mirror lockup feature being disabled.
    CBLPropertyCommonValueMirrorLockupStageDisabled = 300,
    /// The value is equivalent to the camera's mirror lockup feature being enabled and ready to operate.
    CBLPropertyCommonValueMirrorLockupStageReady,
    /// The value is equivalent to the camera's mirror being flipped up and waiting for a shot.
    CBLPropertyCommonValueMirrorLockupStageMirrorUpBeforeShot
} NS_SWIFT_NAME(PropertyCommonValueMirrorLockupStage);

/// Autofocus system common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueAFSystem) {
    /// The value is equivalent to using a "traditional" off-sensor array of autofocus points for autofocus.
    CBLPropertyCommonValueAFSystemViewfinderAFPoints = 350,
    /// The value is equivalent to using a single area on the sensor for autofocus.
    CBLPropertyCommonValueAFSystemSingleArea,
    /// The value is equivalent to using multiple areas on the sensor for autofocus.
    CBLPropertyCommonValueAFSystemMultipleAreas,
    /// The value is equivalent to using face-detection for autofocus.
    CBLPropertyCommonValueAFSystemFaceDetection,
    /// The value is equivalent to using a single small point on the sensor for autofocus.
    CBLPropertyCommonValueAFSystemSinglePoint,
    /// The value is equivalent to using a single point on the sensor for autofocus, then tracking the subject from that
    /// point while autofocus is active.
    CBLPropertyCommonValueAFSystemSinglePointTracking
} NS_SWIFT_NAME(PropertyCommonValueAFSystem);

/// Drive mode common values.
typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueDriveMode) {
    /// The value is equivalent to a single shot drive mode.
    CBLPropertyCommonValueDriveModeSingleShot = 400,
    /// The value is equivalent to a single shot, electronic first-curtain drive mode. Often called quiet, vibration
    /// reduction, VR, etc.
    CBLPropertyCommonValueDriveModeSingleShotElectronicFirstCurtain,
    /// The value is equivalent to a single shot, electronic shutter drive mode. Often called silent, S, etc.
    CBLPropertyCommonValueDriveModeSingleElectronic,

    /// The value is equivalent to a continous/multi-shot shot drive mode.
    CBLPropertyCommonValueDriveModeContinuous,
    /// The value is equivalent to a continous/multi-shot shot, electronic first-curtain drive mode.
    CBLPropertyCommonValueDriveModeContinuousElectronicFirstCurtain,
    /// The value is equivalent to a continous/multi-shot shot, electronic shutter drive mode.
    CBLPropertyCommonValueDriveModeContinuousElectronic,

    /// The value is equivalent to a low-speed continous/multi-shot shot drive mode on cameras that have multiple levels
    /// of speed for their continuous shooting.
    CBLPropertyCommonValueDriveModeContinuousLowSpeed,
    /// The value is equivalent to a medium-speed continous/multi-shot shot drive mode on cameras that have multiple levels
    /// of speed for their continuous shooting.
    CBLPropertyCommonValueDriveModeContinuousMediumSpeed,
    /// The value is equivalent to a high-speed continous/multi-shot shot drive mode on cameras that have multiple levels
    /// of speed for their continuous shooting.
    CBLPropertyCommonValueDriveModeContinuousHighSpeed,

    /// The value is equivalent to a short duration timer drive mode, usually 2-3 seconds or so.
    CBLPropertyCommonValueDriveModeTimerShort,
    /// The value is equivalent to a long duration timer drive mode, usually 10 seconds or so.
    CBLPropertyCommonValueDriveModeTimerLong,
    /// The value is equivalent to a timer drive mode with a custom duration set by the user.
    CBLPropertyCommonValueDriveModeTimerCustomDuration,
    /// The value is equivalent to a timer drive mode, that takes a burst of shots at the end.
    CBLPropertyCommonValueDriveModeTimerWithContinuousShooting
} NS_SWIFT_NAME(PropertyCommonValueDriveMode);
