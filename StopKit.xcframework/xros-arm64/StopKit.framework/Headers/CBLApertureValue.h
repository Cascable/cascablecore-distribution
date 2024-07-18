#import <Foundation/Foundation.h>
#import <StopKit/CBLUniversalPropertyValue.h>

/** This class represents the aperture "f-stops" exposure property. */
NS_SWIFT_NAME(ApertureValue)
@interface CBLApertureValue : NSObject <CBLUniversalExposurePropertyValue>

/**
 Returns a singleton representing the "automatic" aperture value you might encounter when working with cameras.

 @warning Most properties and all math methods will raise an exception when called. This value should only be used for
 comparison in order to avoid trying to do math with this value when encountered.
 */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *automaticAperture;

/** Returns an instance representing f/2.8. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f2Point8;

/** Returns an instance representing f/4.0. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f4;

/** Returns an instance representing f/5.6. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f5Point6;

/** Returns an instance representing f/8. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f8;

/** Returns an instance representing f/11. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f11;

/** Returns an instance representing f/16. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f16;

/** Returns an instance representing f/22. */
@property (class, nonatomic, readonly, nonnull) CBLApertureValue *f22;

/** Returns a new value for the given number of stops from f/8.
 
 @param stops The stops from f/8.
 @return Returns the initialized aperture value.
 */
+(nonnull CBLApertureValue *)apertureValueWithStopsFromF8:(nonnull CBLExposureStops *)stops;

/** Initializes a new value for the given number of stops from f/8.

 This is the designated initializer for this class.

 @param stops The stops from f/8.
 @return Returns the initialized aperture value.
 */
-(nonnull instancetype)initWithStopsFromF8:(nonnull CBLExposureStops *)stops NS_DESIGNATED_INITIALIZER;

/** Initializes a new value for the given numeric aperture value.

 @note Initializing an aperture value with this method is only reliable for values in whole, half or third stops.

 @param aperture The numeric value.
 @return Returns the initialized aperture value.
 */
-(nullable instancetype)initWithApproximateDecimalValue:(double)aperture;

/** Returns the number of stops from f/8 for the receiver. */
@property (nonnull, nonatomic, readonly) CBLExposureStops *stopsFromF8;

/** Returns the approximate numeric value of the receiver. */
@property (nonatomic, readonly) double approximateDecimalValue;

@end
