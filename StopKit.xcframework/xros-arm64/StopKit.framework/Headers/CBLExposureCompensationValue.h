#import <Foundation/Foundation.h>
#import <StopKit/CBLUniversalPropertyValue.h>
#import <StopKit/CBLExposureStops.h>

@protocol CBLUniversalExposurePropertyValue;

/** This class represents the exposure compensation property. */
NS_SWIFT_NAME(ExposureCompensationValue)
@interface CBLExposureCompensationValue : NSObject <CBLUniversalExposurePropertyValue>

/** Returns an exposure compensation value of zero.  */
@property (class, nonatomic, readonly, nonnull) CBLExposureCompensationValue *zeroEV;

/** Returns an exposure compensation value for the given number of stops from zero.
 
 @param stops The number of stops from zero EV to initialise the new value with.
 */
+(nonnull CBLExposureCompensationValue *)valueWithStopsFromZeroEV:(nonnull CBLExposureStops *)stops;

/** Initializes an exposure compensation value for the given number of stops from zero. 
 
 @param stops The number of stops from zero EV to initialise the new value with.
 */
-(nonnull id)initWithStopsFromZeroEV:(nonnull CBLExposureStops *)stops NS_DESIGNATED_INITIALIZER;

/** Returns the number of stops from zero of the receiver. */
@property (nonnull, nonatomic, readonly) CBLExposureStops *stopsFromZeroEV;

@end
