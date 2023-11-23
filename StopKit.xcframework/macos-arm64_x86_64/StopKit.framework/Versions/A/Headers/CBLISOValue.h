#import <Foundation/Foundation.h>
#import <StopKit/CBLUniversalPropertyValue.h>

/** This class represents the ISO exposure property. */
NS_SWIFT_NAME(ISOValue)
@interface CBLISOValue : NSObject <CBLUniversalExposurePropertyValue>

/** Returns an instance representing ISO 100. */
@property (class, nonatomic, readonly, nonnull) CBLISOValue *ISO100;

/** Returns an instance representing ISO 200. */
@property (class, nonatomic, readonly, nonnull) CBLISOValue *ISO200;

/** Returns an instance representing ISO 400. */
@property (class, nonatomic, readonly, nonnull) CBLISOValue *ISO400;

/** Returns an instance representing ISO 800. */
@property (class, nonatomic, readonly, nonnull) CBLISOValue *ISO800;

/** Returns an instance representing ISO 1600. */
@property (class, nonatomic, readonly, nonnull) CBLISOValue *ISO1600;

/**
 Returns a singleton representing the "automatic" ISO value you might encounter when working with cameras.

 @warning Most properties and all math methods will raise an exception when called. This value should only be used for
 comparison in order to avoid trying to do math with this value when encountered.
 */
@property (class, nonatomic, readonly, nonnull) CBLISOValue *automaticISO;

/** Returns a new ISO value for the given number of stops from ISO 100. 
 
 @param stops The stops from ISO 100.
 @return Returns the initialized ISO value.
 */
+(nonnull CBLISOValue *)ISOValueWithStopsFrom100:(nonnull CBLExposureStops *)stops;

/** Initialized a new ISO value for the given number of stops from ISO 100.
 
 This is the designated initializer for this class.

 @param stops The stops from ISO 100.
 @return Returns the initialized ISO value.
 */
-(nonnull instancetype)initWithStopsFromISO100:(nonnull CBLExposureStops *)stops NS_DESIGNATED_INITIALIZER;

/** Returns a new ISO value for the give numeric value.
 
 @note Initializing an ISO value this way only works reliably for values exactly in whole, third or half stop values.
 
 @param iso The ISO value.
 @return Returns the initialized ISO value.
 */
-(nullable instancetype)initWithNumericISOValue:(NSUInteger)iso;

/** Returns the number of stops from ISO 100 of the receiver. */
@property (nonnull, nonatomic, readonly) CBLExposureStops *stopsFrom100;

/** Returns an approximate numeric ISO value for the receiver. */
@property (nonatomic, readonly) NSUInteger numericISOValue;

@end
