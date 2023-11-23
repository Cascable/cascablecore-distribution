#import <Foundation/Foundation.h>
#import <StopKit/CBLUniversalPropertyValue.h>

/** This class represents the shutter speed exposure property. */
NS_SWIFT_NAME(ShutterSpeedValue)
@interface CBLShutterSpeedValue : NSObject <CBLUniversalExposurePropertyValue>

/** Returns an instance representing a shutter speed of one second. */
@property (class, nonatomic, readonly, nonnull) CBLShutterSpeedValue *oneSecondShutterSpeed;

/** Returns an instance representing a shutter speed of 1/250 of a second. */
@property (class, nonatomic, readonly, nonnull) CBLShutterSpeedValue *oneTwoHundredFiftiethShutterSpeed;

/**
 Returns a singleton representing a "bulb" (indeterminate) shutter speed you might encounter when working with cameras.
 
 @warning Most properties and all math methods will raise an exception when called. This value should only be used for
 comparison in order to avoid trying to do math with this value when encountered. You can also check against the `isDeterminate` property.
 */
@property (class, nonatomic, readonly, nonnull) CBLShutterSpeedValue *bulbShutterSpeed;

/**
 Returns a singleton representing the "automatic" shutter speed you might encounter when working with cameras.

 @warning Most properties and all math methods will raise an exception when called. This value should only be used for
 comparison in order to avoid trying to do math with this value when encountered.
 */
@property (class, nonatomic, readonly, nonnull) CBLShutterSpeedValue *automaticShutterSpeed;

/** 
 Returns an array of values representing the expected shutter speeds between the given values.
 
 @param low The lower value.
 @param high The higher value.
 @return Returns an array of shutter speeds between (and including) `low` and `high`.
 */
+(nullable NSArray <CBLShutterSpeedValue *> *)shutterSpeedsBetween:(nonnull CBLShutterSpeedValue *)low and:(nonnull CBLShutterSpeedValue *)high;

/**
 Returns the significant fraction integer for the given number of stops from 1 second.

 @param stops The stops from one second.
 @return The value.
 */
+(NSUInteger)significantFractionIntegerForStopsFromASecond:(nonnull CBLExposureStops *)stops NS_SWIFT_NAME(significantFraction(for:));

/** Initializes a new shutter speed value with the given number of stops from one second.
 
 This is the designated initializer for this class.
 
 @param stops The stops from one second.
 @return Returns the initialized shutter speed value.
 */
-(nonnull id)initWithStopsFromASecond:(nonnull CBLExposureStops *)stops NS_DESIGNATED_INITIALIZER;

/** Initializes a new shutter speed value with the given duration.

@note Initializing a shutter speed value in this way is only reliable with values at whole, half or third stops.

 @param interval The duration of the shutter speed.
 @return Returns the initialized shutter speed value.
 */
-(nullable id)initWithApproximateDuration:(NSTimeInterval)interval;

/** Returns the number of stops from one second of the receiver. */
@property (nonnull, nonatomic, readonly) CBLExposureStops *stopsFromASecond;

/** Returns `YES` if the receiver represents a "determinate" shutter speed, otherwise `NO`.
 
 A shutter speed is determinate if it has a fixed duration known beforehand. Shutter speeds like Bulb, Automatic, etc are not determinate.
 
 @note Calling -approximateTimeInterval, -fractionalRepresentation, -lowerFractionalValue, -upperFractionalValue, or
 -valueByAddingStops: on a value that isn't determinate will cause a runtime exception to be thrown.
 */
@property (nonatomic, readonly) BOOL isDeterminate;

/** Returns `YES` if the receiver represents a "bulb" shutter speed, otherwise `NO`. */
@property (nonatomic, readonly) BOOL isBulb;

/** Returns the approximate numeric duration of the receiver, in seconds. */
@property (nonatomic, readonly) NSTimeInterval approximateTimeInterval;

/**
 Returns a string containing a fractional representation of the receiver.
 
 This method is not typically appropriate for user-facing text, since for speeds slower 
 than one second it'll return top-heavy fractions (i.e., 2/1 for two seconds). 
 */
@property (nonatomic, readonly, copy, nonnull) NSString *fractionalRepresentation;

/** Returns the upper fractional numeric of the receiver. I.e., the "1" in "1/2". */
@property (nonatomic, readonly) NSUInteger upperFractionalValue;

/** Returns the lower fractional numeric of the receiver. I.e., the "2" in "1/2". */
@property (nonatomic, readonly) NSUInteger lowerFractionalValue;

@end
