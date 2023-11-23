#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, CBLExposureStopFraction) {
    CBLExposureStopFractionNone = 0x0,
    CBLExposureStopFractionOneThird = 1 << 0,
    CBLExposureStopFractionOneHalf = 1 << 1,
    CBLExposureStopFractionTwoThirds = 1 << 2
} NS_SWIFT_NAME(ExposureStopFraction);

/** This class represents a vector of exposure stops. Since this is a vector,
 an instance of this on its own doesn't mean too much. */
NS_SWIFT_NAME(ExposureStops)
@interface CBLExposureStops : NSObject <NSCopying, NSSecureCoding>

/** Returns a zero exposure stop vector. */
@property (class, nonatomic, readonly, nonnull) CBLExposureStops *zeroStops;

/** Returns a stop vector parsed from the given decimal value.
 
 @note: Since stops are fractional, the decimal value will be clamped to the closest
 sensible fraction.
 
 @param decimalValue The value to convert to an exposure stop vector.
 @return Returns a `CBLExposureStops` object representing the given value.
 */
+(nonnull CBLExposureStops *)stopsFromDecimalValue:(double)decimalValue;

/** Returns an array of exposure stop vectors between (and including) the given exposure stop vectors.

 Fractions are calculated from the starting value. Whole stops are always included.

 @param from The starting exposure stop vector.
 @param to The terminating exposure stop vector.
 @param fractions The fractions to include.
 @return Returns the array of exposure stops.
 */
+(nullable NSArray <CBLExposureStops *> *)stopsBetween:(nonnull CBLExposureStops *)from and:(nonnull CBLExposureStops *)to including:(CBLExposureStopFraction)fractions;

/**
 Returns an exposure stop object representing the given values.
 
 This is the designated initializer of this class.
 
 @param wholeStops The number of whole stops from zero.
 @param fraction The fractional value of the stops.
 @param negative `YES` if the value is negative, otherwise `NO`.
 @return Returns the initialised object.
 */
-(nonnull id)initWithWholeStops:(NSUInteger)wholeStops fraction:(CBLExposureStopFraction)fraction isNegative:(BOOL)negative NS_DESIGNATED_INITIALIZER;

/** Compares two stop values.

 @param other The other value to compare the receiver to.
 @return Returns `NSOrderedDescending` if the parameter is less than the receiver, `NSOrderedAscending` if the parameter is greater than
 the receiver, or `NSOrderedSame` if the values are equal.
*/
-(NSComparisonResult)compare:(nonnull CBLExposureStops *)other;

/** Returns a string succinctly describing the value. For debug only - not appropriate for user-facing UI. */
@property (nonatomic, readonly, copy, nonnull) NSString *succinctDescription;

/** 
 Returns a new object containing the result of adding the passed object to the receiver.
 
 @param stops The stops instance to add to the receiver.
 @return Returns the result of the operation.
 */
-(nonnull CBLExposureStops *)stopsByAdding:(nonnull CBLExposureStops *)stops;

/**
 Returns a new object containing the difference in stops between the receiver and the passed value.
 
 @param stops The object to compare to.
 @return Returns a new instance representing the difference between the receiver and `stops`.
 */
-(nonnull CBLExposureStops *)differenceFrom:(nonnull CBLExposureStops *)stops;

/** Returns an approximate decimal representation of the receiver. */
@property (nonatomic, readonly) double approximateDecimalValue;

/** Returns `YES` if the receiver represents a negative value, otherwise `NO`. */
@property (nonatomic, readonly) BOOL isNegative;

/** Returns the whole number of the stops represented by the receiver. */
@property (nonatomic, readonly) NSUInteger wholeStopsFromZero;

/** Returns the fractional value of the stops represented by the receiver. */
@property (nonatomic, readonly) CBLExposureStopFraction fraction;

@end
