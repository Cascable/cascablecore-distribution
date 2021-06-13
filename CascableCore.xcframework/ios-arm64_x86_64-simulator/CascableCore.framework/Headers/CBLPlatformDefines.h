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
+(NSImage *)imageWithCGImage:(CGImageRef)cgImage;
@end

#endif

extern NSString * CBLCoreLocalizedString(NSString *key, NSString *table);
#define CBLCoreLocalizedStringWithFormat(key, table, ...) [NSString stringWithFormat:CBLCoreLocalizedString(key, table), __VA_ARGS__]
