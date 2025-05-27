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
extern CBLCameraFamily const CBLCameraFamilyCanon NS_SWIFT_NAME(CameraFamilyCanon);

/// The camera is an Olympus camera.
extern CBLCameraFamily const CBLCameraFamilyOlympus NS_SWIFT_NAME(CameraFamilyOlympus);

/// The camera is a Nikon camera.
extern CBLCameraFamily const CBLCameraFamilyNikon NS_SWIFT_NAME(CameraFamilyNikon);

/// The camera is a Sony camera.
extern CBLCameraFamily const CBLCameraFamilySony NS_SWIFT_NAME(CameraFamilySony);

/// The camera is a Panasonic camera.
extern CBLCameraFamily const CBLCameraFamilyPanasonic NS_SWIFT_NAME(CameraFamilyPanasonic);

/// The camera is a Fujifilm camera.
extern CBLCameraFamily const CBLCameraFamilyFuji NS_SWIFT_NAME(CameraFamilyFuji);

/// The camera is a "generic" camera (typically an import-only camera connected via USB).
extern CBLCameraFamily const CBLCameraFamilyGeneric NS_SWIFT_NAME(CameraFamilyGeneric);

/// Compare the given double values within the given amount of precision.
static inline BOOL CBLFloatAlmostEqual(double x, double y, double delta) { return fabs(x - y) <= delta; }
#define STANDARD_FLOAT_WIGGLE_ROOM 0.0000001
