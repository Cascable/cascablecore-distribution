//
//  CBLConstants.h
//  CascableCore
//
//  Created by Daniel Kennett on 12/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;

typedef void (^CBLErrorableOperationCallback)(NSError * _Nullable) NS_SWIFT_NAME(ErrorableOperationCallback);
static NSString * _Nonnull const CBLErrorDomain NS_SWIFT_NAME(CascableCoreErrorDomain) = @"se.cascable";
static NSString * _Nonnull const CBLUnderlyingResponseCodeKey NS_SWIFT_NAME(UnderlyingResponseCodeKey) = @"PTPResponseCode";
static NSString * _Nonnull const CBLUnderlyingResponseCodeDescriptionKey NS_SWIFT_NAME(UnderlyingResponseCodeDescriptionKey) = @"PTPResponseDescription";
static NSString * _Nonnull const CBLErrorCodeDescriptionKey NS_SWIFT_NAME(ErrorCodeDescriptionKey) = @"ErrorCodeDescription";

typedef NSInteger CBLCameraFamily NS_SWIFT_NAME(CameraFamily);

static CBLCameraFamily const CBLCameraFamilyCanon NS_SWIFT_NAME(CameraFamilyCanon) = 0;
static CBLCameraFamily const CBLCameraFamilyOlympus NS_SWIFT_NAME(CameraFamilyOlympus) = 1;
static CBLCameraFamily const CBLCameraFamilyNikon NS_SWIFT_NAME(CameraFamilyNikon) = 2;
static CBLCameraFamily const CBLCameraFamilySony NS_SWIFT_NAME(CameraFamilySony) = 3;
static CBLCameraFamily const CBLCameraFamilyPanasonic NS_SWIFT_NAME(CameraFamilyPanasonic) = 4;
static CBLCameraFamily const CBLCameraFamilyFuji NS_SWIFT_NAME(CameraFamilyFuji) = 5;
static CBLCameraFamily const CBLCameraFamilyGeneric NS_SWIFT_NAME(CameraFamilyGeneric) = 6;

typedef NS_ENUM(NSInteger, CBLCameraTransport) {
    /** The camera is communicating via a TCP/IP network, either using WiFi or Ethernet. */
    CBLCameraTransportNetwork = 0,
    /** The camera is communicating via USB. */
    CBLCameraTransportUSB = 1
} NS_SWIFT_NAME(CameraTransport);

typedef NS_ENUM(NSUInteger, CBLPropertyIdentifier) {
    CBLPropertyIdentifierISOSpeed,
    CBLPropertyIdentifierShutterSpeed,
    CBLPropertyIdentifierAperture,
    CBLPropertyIdentifierExposureCompensation,
    CBLPropertyIdentifierBatteryLevel,
    CBLPropertyIdentifierPowerSource,
    CBLPropertyIdentifierAFSystem,
    CBLPropertyIdentifierFocusMode,
    CBLPropertyIdentifierDriveMode,
    CBLPropertyIdentifierAutoExposureMode,
    CBLPropertyIdentifierInCameraBracketingEnabled,
    CBLPropertyIdentifierMirrorLockupEnabled,
    CBLPropertyIdentifierMirrorLockupStage,
    CBLPropertyIdentifierDOFPreviewEnabled,
    CBLPropertyIdentifierShotsAvailable,
    CBLPropertyIdentifierLensStatus,
    CBLPropertyIdentifierColorTone,
    CBLPropertyIdentifierArtFilter,
    CBLPropertyIdentifierDigitalZoom,
    CBLPropertyIdentifierWhiteBalance,
    CBLPropertyIdentifierNoiseReduction,
    CBLPropertyIdentifierImageQuality,
    CBLPropertyIdentifierLightMeterStatus,
    CBLPropertyIdentifierLightMeterReading,
    CBLPropertyIdentifierExposureMeteringMode,
    CBLPropertyIdentifierReadyForCapture,
    CBLPropertyIdentifierMax,

    CBLPropertyIdentifierUnknown = NSNotFound
} NS_SWIFT_NAME(PropertyIdentifier);

#define STANDARD_FLOAT_WIGGLE_ROOM 0.0000001
static inline BOOL CBLFloatAlmostEqual(double x, double y, double delta) { return fabs(x - y) <= delta; }

