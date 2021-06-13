//
//  NSError+CBLExtensions.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/02/16.
//  Copyright © 2016 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CBLErrorCameraDomain) {
    CBLErrorCameraDomainGenericPTP,
    CBLErrorCameraDomainGenericHTTP,
    CBLErrorCameraDomainCanon,
    CBLErrorCameraDomainNikon,
    CBLErrorCameraDomainSony,
    CBLErrorCameraDomainOlympus,
    CBLErrorCameraDomainPanasonic,
    CBLErrorCameraDomainFuji
};

typedef NS_ENUM(NSUInteger, CBLErrorCode) {
    CBLErrorCodeGeneric = 1000,
    CBLErrorCodeNoError,
    CBLErrorCodeNotConnected,
    CBLErrorCodeDeviceBusy,
    CBLErrorCodeCancelledByUser,
    CBLErrorCodeInvalidPropertyValue,
    CBLErrorCodeWriteProtected,
    CBLErrorCodeNoThumbnail,
    CBLErrorCodeNotAvailable,
    CBLErrorCodeIncorrectCommandCategory,
    CBLErrorCodeAutoFocusFailed,
    CBLErrorCodeGenericProtocolFailure,
    CBLErrorCodeInvalidInput,
    CBLErrorCodeCameraNeedsSoftwareUpdate,
    CBLErrorCodeTimeout,
    CBLErrorCodeFocusDidNotMove,
    CBLErrorCodeUnsupportedFileFormat,
    CBLErrorCodeNoMetadata,
    CBLErrorCodeNeedsNewPairing
} NS_SWIFT_NAME(CascableCoreErrorCode);

@interface NSError (CBL)

+(NSError *)errorWithCameraResponseCode:(NSUInteger)code inDomain:(CBLErrorCameraDomain)domain;
+(NSError *)errorWithCBLErrorCode:(CBLErrorCode)code;
+(NSError *)errorWithCBLErrorCode:(CBLErrorCode)code description:(NSString *)description;
+(NSError *)errorWithCBLErrorCode:(CBLErrorCode)code userInfo:(NSDictionary *)userInfo;
+(NSError *)errorWithCBLErrorCode:(CBLErrorCode)code underlyingError:(NSError *)underlying;

@end
