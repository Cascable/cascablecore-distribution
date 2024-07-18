//
//  CBLLicenseVerification.h
//  CascableCore
//
//  Created by Daniel Kennett on 2017-11-14.
//  Copyright © 2017 Cascable AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/** A class to register your license. */
NS_SWIFT_NAME(CascableCoreLicenseVerification)
@interface CBLLicenseVerification : NSObject

/** A result from a license registration. */
typedef NS_ENUM(NSUInteger, CBLLicenseVerificationResult) {
    /** The license was applied successfully. */
    CBLLicenseVerificationResultSuccess,
    /** The license expired. */
    CBLLicenseVerificationResultExpired,
    /** The license is invalid. */
    CBLLicenseVerificationResultInvalidLicense
} NS_SWIFT_NAME(LicenseVerificationResult);

/**
 Register your license with CascableCore.

 This should be done before any other CascableCore APIs.

 @param licenseData The license data to apply.
 @return The result of the license.
 */
+(CBLLicenseVerificationResult)applyLicense:(NSData * _Nonnull)licenseData NS_SWIFT_NAME(apply(license:));

@end
