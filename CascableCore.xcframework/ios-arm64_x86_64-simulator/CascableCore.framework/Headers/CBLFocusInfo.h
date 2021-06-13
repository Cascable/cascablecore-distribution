//
//  CBLFocusInfo.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
@import CoreGraphics;
#import <CascableCore/CBLFocusPoint.h>

/** Represents an autofocus state of the camera. */
NS_SWIFT_NAME(FocusInfo)
@protocol CBLFocusInfo <NSObject>

/** Returns the aspect of the autofocus, typically representing the area of the viewfinder. */
@property (readonly, nonatomic) CGSize aspect;

/** Returns an array of `CBLFocusPoint` instances that define the autofocus cluster. */
@property (nullable, readonly, nonatomic, copy) NSArray <id <CBLFocusPoint>> *points;

/** Translates the given AF point's rect to a rect inside the target container. Useful for
 translating AF point rects into views, for example.

 @param point The AF point to translate.
 @param targetContainer The rect defining the bounds of the target container.
 @return The rect representing `point` inside `targetContainer`.
 */
-(CGRect)translateRectOfPoint:(nonnull id <CBLFocusPoint>)point toSubRectOfRect:(CGRect)targetContainer;

@end
