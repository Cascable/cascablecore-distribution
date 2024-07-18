//
//  CBLConstants.h
//  CascableCore
//
//  Created by Daniel Kennett on 12/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;

/**
 The block callback signature for an async operation that can fail with an error.

 @param error The error that occurred, if any. If `nil`, the operation succeeded.
 */
typedef void (^CBLErrorableOperationCallback)(NSError * _Nullable error) NS_SWIFT_NAME(ErrorableOperationCallback);

/// A value representing a camera family, usually grouped by camera manufacturer.
typedef NSInteger CBLCameraFamily NS_SWIFT_NAME(CameraFamily);

/// The camera is a Canon camera.
static CBLCameraFamily const CBLCameraFamilyCanon NS_SWIFT_NAME(CameraFamilyCanon) = 0;

/// The camera is an Olympus camera.
static CBLCameraFamily const CBLCameraFamilyOlympus NS_SWIFT_NAME(CameraFamilyOlympus) = 1;

/// The camera is a Nikon camera.
static CBLCameraFamily const CBLCameraFamilyNikon NS_SWIFT_NAME(CameraFamilyNikon) = 2;

/// The camera is a Sony camera.
static CBLCameraFamily const CBLCameraFamilySony NS_SWIFT_NAME(CameraFamilySony) = 3;

/// The camera is a Panasonic camera.
static CBLCameraFamily const CBLCameraFamilyPanasonic NS_SWIFT_NAME(CameraFamilyPanasonic) = 4;

/// The camera is a Fujifilm camera.
static CBLCameraFamily const CBLCameraFamilyFuji NS_SWIFT_NAME(CameraFamilyFuji) = 5;

/// The camera is a "generic" camera (typically an import-only camera connected via USB).
static CBLCameraFamily const CBLCameraFamilyGeneric NS_SWIFT_NAME(CameraFamilyGeneric) = 6;

/// Compare the given double values within the given amount of precision.
static inline BOOL CBLFloatAlmostEqual(double x, double y, double delta) { return fabs(x - y) <= delta; }
#define STANDARD_FLOAT_WIGGLE_ROOM 0.0000001
