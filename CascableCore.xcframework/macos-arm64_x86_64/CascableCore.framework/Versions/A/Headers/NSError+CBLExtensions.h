//
//  NSError+CBLExtensions.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/02/16.
//  Copyright © 2016 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>

/** CascableCore error domains. */
typedef NS_ENUM(NSUInteger, CBLErrorCameraDomain) {
    /** The error occurred with a generic PTP camera. */
    CBLErrorCameraDomainGenericPTP,
    /** The error occurred with a generic HTTP camera. */
    CBLErrorCameraDomainGenericHTTP,
    /** The error occurred with a Canon camera. */
    CBLErrorCameraDomainCanon,
    /** The error occurred with a Nikon camera. */
    CBLErrorCameraDomainNikon,
    /** The error occurred with a Sony camera. */
    CBLErrorCameraDomainSony,
    /** The error occurred with a Olympus camera. */
    CBLErrorCameraDomainOlympus,
    /** The error occurred with a Panasonic camera. */
    CBLErrorCameraDomainPanasonic,
    /** The error occurred with a Fujifilm. */
    CBLErrorCameraDomainFuji
};

/** CascableCore error codes. */
typedef NS_ENUM(NSUInteger, CBLErrorCode) {
    /** A generic, unknown error occurred. */
    CBLErrorCodeGeneric = 1000,
    /** No error. */
    CBLErrorCodeNoError,
    /** The operation failed because the camera isn't connected. Can also be used as an error code if another operation
     fails due to the camera disconnecting (such as file streaming, live view, etc). */
    CBLErrorCodeNotConnected,
    /** The operation failed because the device is busy. Typically, you can wait a moment and try again. */
    CBLErrorCodeDeviceBusy,
    /** The operation was cancelled by the user. For instance, a pairing request can fail with this code if the user
     cancels pairing from the camera body. */
    CBLErrorCodeCancelledByUser,
    /** The operation failed because the given value is not valid for the property in its current state. If you're
     caching valid values, the camera may have changed state since the cache was made (for instance, you're trying
     to set a shutter speed but the camera is now in an automatic exposure mode). */
    CBLErrorCodeInvalidPropertyValue,
    /** The operation failed because the camera's storage is write-protected. */
    CBLErrorCodeWriteProtected,
    /** The operation failed because no thumbnail is available for the requested resource. */
    CBLErrorCodeNoThumbnail,
    /** The operation failed because the camera does not support the requested operation. */
    CBLErrorCodeNotAvailable,
    /** The operation failed because the camera isn't in a command category that supports the requested operation.
     For example, you're trying to take a photo while the camera doesn't currently allow stills shooting commands. */
    CBLErrorCodeIncorrectCommandCategory,
    /** The focus operation failed, perhaps because the camera's autofocus is unable to being anything into focus. */
    CBLErrorCodeAutoFocusFailed,
    /** The operation failed because of an underlying failure in the camera's protocol. This is often an indication of
     a larger problem (for example, the network dropped or the USB cable was disconnected halfway through an operation). */
    CBLErrorCodeGenericProtocolFailure,
    /** The operation failed because of an invalid input parameter. */
    CBLErrorCodeInvalidInput,
    /** The connection failed because the camera needs a firmware update to be controlled by CascableCore. */
    CBLErrorCodeCameraNeedsSoftwareUpdate,
    /** The operation failed because the camera did not respond within a sensible time period. Check network conditions. */
    CBLErrorCodeTimeout,
    /** The focus drive operation failed because the lens was unable to move, either due to being at the end of its travel
     in the particular direction given, or due to a physical blockage. */
    CBLErrorCodeFocusDidNotMove,
    /** The operation failed because the file isn't of a supported format. */
    CBLErrorCodeUnsupportedFileFormat,
    /** The operation failed because metadata could not be retrieved for the requested file. */
    CBLErrorCodeNoMetadata,
    /** The camera connection failed because it is paired with something else. A new pairing is required. */
    CBLErrorCodeNeedsNewPairing,
    /** The operation failed because the camera is currently recording video. */
    CBLErrorCodeVideoRecordingInProgress,
    /** The operation failed because the camera can only perform the given action by having the user flip a switch
        or push a button on the camera directly. */
    CBLErrorCodeRequiresPhysicalInteraction,
    /** The operation failed because the camera doesn't allow the operation over the current transport. For example,
     older Canon cameras don't allow video recording over WiFi. */
    CBLErrorCodeDisallowedOnCurrentTransport,
    /** The operation failed because it requires live view to be running. Start live view and try again. */
    CBLErrorCodeRequiresLiveView,
    /** The operation failed because of a card error. Either the storage card is missing, damaged, or unformatted. */
    CBLErrorCodeCardError,
    /** The operation failed because the camera's storage is full. */
    CBLErrorCodeStorageFull
} NS_SWIFT_NAME(CascableCoreErrorCode);

/** NSError helpers for CascableCore. */
@interface NSError (CBL)

/**
 Create an error with the given raw camera response code in the given domain.

 @param code The raw camera error code.
 @param domain The domain in which to translate error codes. 
 */
+(NSError * _Nonnull)errorWithCameraResponseCode:(NSUInteger)code inDomain:(CBLErrorCameraDomain)domain;

/** Create an error with the given universal error code. */
+(NSError * _Nonnull)errorWithCBLErrorCode:(CBLErrorCode)code;

/** Create an error with the given universal error code and description. */
+(NSError * _Nonnull)errorWithCBLErrorCode:(CBLErrorCode)code description:(NSString * _Nonnull)description;

/** Create an error with the given universal error code and user info dictionary. */
+(NSError * _Nonnull)errorWithCBLErrorCode:(CBLErrorCode)code userInfo:(NSDictionary * _Nullable)userInfo;

/** Create an error with the given universal error code and underlying error. */
+(NSError * _Nonnull)errorWithCBLErrorCode:(CBLErrorCode)code underlyingError:(NSError * _Nullable)underlying;

@end

/** The domain string used with CascableCore `NSError` objects. */
static NSString * _Nonnull const CBLErrorDomain NS_SWIFT_NAME(CascableCoreErrorDomain) = @"se.cascable";

/** The error user info key for the underlying raw camera response code. */
static NSString * _Nonnull const CBLUnderlyingResponseCodeKey NS_SWIFT_NAME(UnderlyingResponseCodeKey) = @"PTPResponseCode";

/** The error user info key for a description of the underlying raw camera response code. */
static NSString * _Nonnull const CBLUnderlyingResponseCodeDescriptionKey NS_SWIFT_NAME(UnderlyingResponseCodeDescriptionKey) = @"PTPResponseDescription";

/** The error user info key for a description of the error code (i.e., the `CBLErrorCode` code). */
static NSString * _Nonnull const CBLErrorCodeDescriptionKey NS_SWIFT_NAME(ErrorCodeDescriptionKey) = @"ErrorCodeDescription";
