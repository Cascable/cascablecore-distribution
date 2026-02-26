//
//  CBLLicenseVerification.h
//  CascableCore
//
//  Created by Daniel Kennett on 2017-11-14.
//  Copyright © 2017 Cascable AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/// An offline activation token as issued by the Cascable licensing service when validating a CascableCore license key.
NS_SWIFT_NAME(LicenseKeyOfflineToken)
@protocol CBLLicenseKeyOfflineToken <NSObject>

/// The token's expiry date. The token can be used to maintain activation status without an internet connection
/// until this date.
@property (nonatomic, readonly, copy, nonnull) NSDate *tokenExpiry;

/// The token itself. This is an opaque data structure appropriate for storing in the Keychain, User Defaults, etc.
@property (nonatomic, readonly, copy, nonnull) NSData *tokenData;

/// Whether the token was newly-issued by the licensing service. If `YES`, your local storage should be updated with
/// this new token. If `NO`, this is the same token that was passed in when applying your license key.
@property (nonatomic, readonly) BOOL wasRefreshed;

@end

/** A class to register your CascableCore license. */
NS_SWIFT_NAME(CascableCoreLicenseVerification)
@interface CBLLicenseVerification : NSObject

/** A result from license file registration. */
typedef NS_ENUM(NSUInteger, CBLLicenseVerificationResult) {
    /** The license was applied successfully. */
    CBLLicenseVerificationResultSuccess = 0,
    /** The license expired. */
    CBLLicenseVerificationResultExpired = 1,
    /** The license is invalid. */
    CBLLicenseVerificationResultInvalidLicense = 2
} NS_SWIFT_NAME(LicenseVerificationResult);

/**
 Register your license file with CascableCore.

 This should be done before calling any other CascableCore APIs.

 @param licenseData The license data to apply.
 @return The result of the license.
 */
+(CBLLicenseVerificationResult)applyLicense:(NSData * _Nonnull)licenseData NS_SWIFT_NAME(apply(license:));

/// License key offline activation token refresh modes.
typedef NS_ENUM(NSInteger, CBLLicenseKeyOfflineTokenRefreshMode) {
    /// Apply the default logic for offline activation token refresh.
    CBLLicenseKeyOfflineTokenRefreshModeAutomatic = 0,
    /// Always attempt to contact the licensing service for a new offline activation token.
    CBLLicenseKeyOfflineTokenRefreshModeAlways = 1,
    /// Don't contact the license service unless absolutely required.
    CBLLicenseKeyOfflineTokenRefreshModeNeverUnlessExpired = 2
} NS_SWIFT_NAME(LicenseKeyOfflineTokenRefreshMode);

/// A result from license key activation.
typedef NS_ENUM(NSInteger, CBLLicenseKeyVerificationResult) {
    /// The license key was successfully verified with the offline token provided.
    CBLLicenseKeyVerificationResultActivated = 0,
    /// The license key failed to be verified (usually due to a connectivity issue), and a valid offline token was not
    /// provided. The SDK will not function.
    CBLLicenseKeyVerificationResultFailedWithoutValidOfflineToken = 1,
    /// The license key is not valid in the current environment (for example, a trial license was attempted to be used
    /// in the App Store). The SDK will not function.
    CBLLicenseKeyVerificationResultNotAllowedInCurrentEnvironment = 2,
    /// The license is not valid for this process (wrong bundle ID, platform, etc). The SDK will not function.
    CBLLicenseKeyVerificationResultInvalidLicense = 3
} NS_SWIFT_NAME(LicenseKeyVerificationResult);

/// The signature of the completion handler for the license key verification process.
///
/// - Parameters:
///   - result: The result of the operation.
///   - token: If the operation was successful, the granted offline activation token.
typedef void (^CBLLicenseKeyCompletionHandler)(CBLLicenseKeyVerificationResult result, id <CBLLicenseKeyOfflineToken> _Nullable token) NS_SWIFT_NAME(LicenseKeyCompletionHandler);

/// Applies the given license key with the default token refresh mode. This should be done (and the completion handler
/// received) before calling any other CascableCore APIs, otherwise an "unlicensed" dialog may be shown to the user.
///
/// For more information, see the documentation for `-applyLicenseKey:offlineToken:tokenRefreshMode:completionHandler:`.
///
/// - Parameters:
///   - licenseKey: Your CascableCore license key.
///   - offlineToken: A previously-issued offline activation token, if you have one.
///   - completionHandler: The completion handler, called on the main thread, to be executed when the
///                        process succeeds or fails.
+(void)applyLicenseKey:(NSString * _Nonnull)licenseKey
          offlineToken:(NSData * _Nullable)offlineToken
     completionHandler:(CBLLicenseKeyCompletionHandler _Nonnull)completionHandler
NS_SWIFT_NAME(apply(licenseKey:offlineToken:completionHandler:));

/// Applies the given license key. This should be done (and the completion handler received) before calling any
/// other CascableCore APIs, otherwise an "unlicensed" dialog may be shown to the user.
///
/// The CascableCore license key verification process involves connecting to the Cascable licensing service to
/// verify the license key and retrieve an offline activation token. Once verified, that token is returned via
/// the completion callback for the caller to store and supply in subsequent calls to this method. Activation
/// tokens are small (less than a kilobyte) and appropriate for storing in the Keychain, User Defaults, etc.
///
/// **NOTE:** Offline activation tokens are per end-user device, and shouldn't be synced around.
///
/// If you provide a valid offline activation token alongside your license key, CascableCore will not need to connect
/// to the licensing service again so long as the token isn't expired. By default, CascableCore won't contact the
/// service to get a new token unless the given one has less than seven days of validity remaining.
///
/// You can customise this behaviour with the `refreshMode` parameter. It's also safe to call this method more than
/// once in your app's lifecycle, so if you're aware that your app may be entering an extended period with no internet
/// access, you can call this with the `CBLLicenseKeyOfflineTokenRefreshModeAlways` refresh mode to get a new token
/// for the longest offline validity period.
///
/// If the connection to the licensing service fails for whatever reason, the overall operation will succeed as long
/// as a valid offline activation token is present, no matter the value of `refreshMode`. In practice, this means
/// that the only time an internet connection is **required** is if you have no token at all (i.e., an end-user
/// installation's first launch) or if your previously granted token has expired.
///
/// - Parameters:
///   - licenseKey: Your CascableCore license key.
///   - offlineToken: A previously-issued offline activation token, if you have one.
///   - refreshMode: The token refresh mode.
///   - completionHandler: The completion handler, called on the main thread, to be executed when the
///                        process succeeds or fails.
+(void)applyLicenseKey:(NSString * _Nonnull)licenseKey
          offlineToken:(NSData * _Nullable)offlineToken
      tokenRefreshMode:(CBLLicenseKeyOfflineTokenRefreshMode)refreshMode
     completionHandler:(CBLLicenseKeyCompletionHandler _Nonnull)completionHandler
NS_SWIFT_NAME(apply(licenseKey:offlineToken:refreshMode:completionHandler:));

@end
