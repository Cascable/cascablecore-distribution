#import <Foundation/Foundation.h>
#import <StopKit/CBLShutterSpeedValue.h>

NS_SWIFT_NAME(IndeterminateShutterSpeedValue)
@interface CBLIndeterminateShutterSpeedValue : CBLShutterSpeedValue

-(id)initWithName:(NSString *)name;

@property (nonatomic, readonly, copy) NSString *name;

@end
