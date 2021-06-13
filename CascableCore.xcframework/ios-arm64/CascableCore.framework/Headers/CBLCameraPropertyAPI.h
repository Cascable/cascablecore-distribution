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

typedef NS_ENUM(NSInteger, CBLPropertyCategory) {
    CBLPropertyCategoryUnknown,
    CBLPropertyCategoryExposureSetting, // Shutter speed, ISO, EV, etc. Guaranteed to conform to CBLExposureProperty.
    CBLPropertyCategoryCaptureSetting, // Focus modes, etc — settings that affect how the image is captured.
    CBLPropertyCategoryImagingSetting, // White balance, etc — settings that affect the image.
    CBLPropertyCategoryConfigurationSetting, // File format, etc — settings that don't affect the image.
    CBLPropertyCategoryInformation, // Shots remaining, battery, etc
} NS_SWIFT_NAME(PropertyCategory);

typedef NS_OPTIONS(NSUInteger, CBLPropertyChangeType) {
    CBLPropertyChangeTypeValue = 1 << 0, // The current value of the property changed.
    CBLPropertyChangeTypePendingValue = 1 << 1, // The pending value of the property changed.
    CBLPropertyChangeTypeValidSettableValues = 1 << 2 // The valid settable values of the property changed.
} NS_SWIFT_NAME(PropertyChangeType);

typedef NSInteger CBLPropertyCommonValue NS_SWIFT_NAME(PropertyCommonValue);
NS_SWIFT_NAME(PropertyCommonValueNone) static CBLPropertyCommonValue const CBLPropertyCommonValueNone = -1;

typedef void (^CBLCameraPropertyObservationCallback)(id <CBLCameraProperty> _Nonnull, CBLPropertyChangeType) NS_SWIFT_NAME(CameraPropertyObservationCallback);

// An object for managing property value change notifications.
NS_SWIFT_NAME(CameraPropertyObservation)
@protocol CBLCameraPropertyObservation <NSObject>

/// Invalidate the observation. Will also be called on `dealloc`.
-(void)invalidate;

@end

// An object representing the values for a property on the camera.
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

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueBoolean) {
    CBLPropertyCommonValueBooleanFalse = 0,
    CBLPropertyCommonValueBooleanTrue = 1
} NS_SWIFT_NAME(PropertyCommonValueBoolean);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueAutoExposureMode) {
    CBLPropertyCommonValueAutoExposureModeFullyAutomatic = 50,
    CBLPropertyCommonValueAutoExposureModeProgramAuto,
    CBLPropertyCommonValueAutoExposureModeShutterPriority,
    CBLPropertyCommonValueAutoExposureModeAperturePriority,
    CBLPropertyCommonValueAutoExposureModeFullyManual,
    CBLPropertyCommonValueAutoExposureModeBulb
} NS_SWIFT_NAME(PropertyCommonValueAutoExposureMode);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueWhiteBalance) {
    CBLPropertyCommonValueWhiteBalanceAuto = 100,
    CBLPropertyCommonValueWhiteBalanceDaylight,
    CBLPropertyCommonValueWhiteBalanceShade,
    CBLPropertyCommonValueWhiteBalanceCloudy,
    CBLPropertyCommonValueWhiteBalanceTungsten,
    CBLPropertyCommonValueWhiteBalanceFluorescent,
    CBLPropertyCommonValueWhiteBalanceFlash,
    CBLPropertyCommonValueWhiteBalanceCustom,
    CBLPropertyCommonValueWhiteBalanceCustom2,
    CBLPropertyCommonValueWhiteBalanceCustom3
} NS_SWIFT_NAME(PropertyCommonValueWhiteBalance);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueFocusMode) {
    CBLPropertyCommonValueFocusModeManual = 150,
    CBLPropertyCommonValueFocusModeSingleDrive,
    CBLPropertyCommonValueFocusModeContinuousDrive,
} NS_SWIFT_NAME(PropertyCommonValueFocusMode);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueBatteryLevel) {
    CBLPropertyCommonValueBatteryLevelFull = 200,
    CBLPropertyCommonValueBatteryLevelThreeQuarters,
    CBLPropertyCommonValueBatteryLevelHalf,
    CBLPropertyCommonValueBatteryLevelOneQuarter,
    CBLPropertyCommonValueBatteryLevelEmpty
} NS_SWIFT_NAME(PropertyCommonValueBatteryLevel);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValuePowerSource) {
    CBLPropertyCommonValuePowerSourceBattery = 210,
    CBLPropertyCommonValuePowerSourceMainsPower
} NS_SWIFT_NAME(PropertyCommonValuePowerSource);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueLightMeterStatus) {
    CBLPropertyCommonValueLightMeterStatusNotInUse = 250,
    CBLPropertyCommonValueLightMeterStatusValidReading,
    CBLPropertyCommonValueLightMeterStatusBeyondBounds
} NS_SWIFT_NAME(PropertyCommonValueLightMeterStatus);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueMirrorLockupStage) {
    CBLPropertyCommonValueMirrorLockupStageDisabled = 300,
    CBLPropertyCommonValueMirrorLockupStageReady,
    CBLPropertyCommonValueMirrorLockupStageMirrorUpBeforeShot
} NS_SWIFT_NAME(PropertyCommonValueMirrorLockupStage);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueAFSystem) {
    CBLPropertyCommonValueAFSystemViewfinderAFPoints = 350, // Traditional focus sensor in the viewfinder assembly
    CBLPropertyCommonValueAFSystemSingleArea,
    CBLPropertyCommonValueAFSystemMultipleAreas,
    CBLPropertyCommonValueAFSystemFaceDetection,
    CBLPropertyCommonValueAFSystemSinglePoint,
    CBLPropertyCommonValueAFSystemSinglePointTracking
} NS_SWIFT_NAME(PropertyCommonValueAFSystem);

typedef NS_ENUM(CBLPropertyCommonValue, CBLPropertyCommonValueDriveMode) {
    CBLPropertyCommonValueDriveModeSingleShot = 400,
    CBLPropertyCommonValueDriveModeSingleShotElectronicFirstCurtain,
    CBLPropertyCommonValueDriveModeSingleElectronic,

    // Multi-shot
    CBLPropertyCommonValueDriveModeContinuous,
    CBLPropertyCommonValueDriveModeContinuousElectronicFirstCurtain,
    CBLPropertyCommonValueDriveModeContinuousElectronic,

    CBLPropertyCommonValueDriveModeContinuousLowSpeed,
    CBLPropertyCommonValueDriveModeContinuousMediumSpeed,
    CBLPropertyCommonValueDriveModeContinuousHighSpeed,

    // Timer
    CBLPropertyCommonValueDriveModeTimerShort, // Typically 2-3 seconds
    CBLPropertyCommonValueDriveModeTimerLong, // Typically 10 seconds or so
    CBLPropertyCommonValueDriveModeTimerCustomDuration,
    CBLPropertyCommonValueDriveModeTimerWithContinuousShooting
} NS_SWIFT_NAME(PropertyCommonValueDriveMode);
