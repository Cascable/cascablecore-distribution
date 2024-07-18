//
//  CBLFocusPoint.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
@import CoreGraphics;

/** Represents an individual focus point. */
NS_SWIFT_NAME(FocusPoint)
@protocol CBLFocusPoint <NSObject>

/** Returns whether the point is active or not — that is, whether the camera will use the point for autofocus. */
@property (readonly, nonatomic) BOOL active;

/** Returns whether the point currently has focus. */
@property (readonly, nonatomic) BOOL hasFocus;

/** Returns the rect defining this point within the parent's aspect. */
@property (readonly, nonatomic) CGRect pointRect;

@end
