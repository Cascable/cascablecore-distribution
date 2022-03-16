//
//  DKCascablePlatformDefines.h
//  Cascable
//
//  Created by Daniel Kennett on 30/06/14.
//  Copyright (c) 2014 Daniel Kennett. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#define PLATFORM_IMAGE UIImage
#else
#import <Cocoa/Cocoa.h>
#define PLATFORM_IMAGE NSImage

@interface NSImage (CBLPlatform)
+(NSImage * _Nonnull)imageWithCGImage:(CGImageRef _Nonnull)cgImage;
@end

#endif

/// Returns a CascableCore localised string from the given table. Typically this shouldn't be used - use the various
/// localised value properties in the framework instead.
extern NSString * _Nonnull CBLCoreLocalizedString(NSString * _Nonnull key, NSString * _Nonnull table);
#define CBLCoreLocalizedStringWithFormat(key, table, ...) [NSString stringWithFormat:CBLCoreLocalizedString(key, table), __VA_ARGS__]
