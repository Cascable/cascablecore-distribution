#import <Foundation/Foundation.h>

@class CBLExposureStops;

/** An object-based camera property value that can be used across camera types. */
NS_SWIFT_NAME(UniversalPropertyValue)
@protocol CBLUniversalPropertyValue <NSObject, NSCopying, NSSecureCoding>

/** Returns a string succinctly describing the value. For debug only - not appropriate for user-facing UI. */
@property (nonatomic, readonly, copy, nonnull) NSString *succinctDescription;

/** Returns the localized display string for the receiver. */
@property (nonatomic, readonly, copy, nullable) NSString *localizedDisplayValue;

@end

static NSComparisonResult const CBLExposureComparisonInvalid NS_SWIFT_NAME(ExposureComparisonInvalid) = -100;

/** Properties that represent exposure properties should implement this protocol. */
NS_SWIFT_NAME(UniversalExposurePropertyValue)
@protocol CBLUniversalExposurePropertyValue <CBLUniversalPropertyValue>

/** Returns `YES` if the value is determinate (i.e., isn't 'automatic' or 'bulb'). */
@property (nonatomic, readonly) BOOL isDeterminate;

/** Returns a new instance of the property, adjusted by the given number of stops. 
 
 @param stops The number of stops to adjust the property by.
 @return Returns a new property with the adjustment applied, or `nil` if the receiver's `isDeterminate` property returns false.
 */
-(nullable id <CBLUniversalExposurePropertyValue>)valueByAddingStops:(nonnull CBLExposureStops *)stops;

/** Compares the receiver to the given value. Returns `CBLExposureComparisonInvalid` if the objects aren't of the same type, or
 if the receiver's `isDeterminate` property returns false.
 
 @param value The value to compare to the receiver.
 */
-(NSComparisonResult)compare:(nonnull id <CBLUniversalExposurePropertyValue>)value;

/** Returns the difference, in stops, from the passed object. Returns `nil` if the objects aren't of the same type, or
 if the receiver's `isDeterminate` property returns false.

 @param value The value from which to calculate the stops distance from.
 */
-(nullable CBLExposureStops *)stopsDifferenceFrom:(nonnull id <CBLUniversalExposurePropertyValue>)value;

@end
