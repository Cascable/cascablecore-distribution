//
//  CBLCameraLiveViewAFArea.h
//  CascableCore
//
//  Created by Daniel Kennett on 16/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
@import CoreGraphics;

/** Represents an autofocus area in a camera's focus aspect. Typically rendered as a rectangle on top of the live view image. */
NS_SWIFT_NAME(LiveViewAFArea)
@protocol CBLCameraLiveViewAFArea <NSObject>

/** Returns `YES` if the AF area is focused, otherwise `NO`. */
@property (nonatomic, readonly) BOOL focused;

/** Returns `YES` if the AF area is active, otherwise `NO`. */
@property (nonatomic, readonly) BOOL active;

/** Returns the area of the receiver, relative to the parent live view frame's aspect. */
@property (nonatomic, readonly) CGRect rect;

@end
