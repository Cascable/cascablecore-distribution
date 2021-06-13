//
//  CBLCamera+Diagnostics.h
//  CascableCore
//
//  Created by Daniel Kennett on 24/03/16.
//  Copyright © 2016 Daniel Kennett. All rights reserved.
//

@import Foundation;
#import <CascableCore/CBLCamera.h>

/** Diagnostics methods for cameras. */
NS_SWIFT_NAME(CameraDiagnostics)
@protocol CBLCameraDiagnostics <CBLCamera>

/**
 Generate a diagnostics report for the camera. Typically, this is only useful for Cascable support.

 @return The diagnostics report, if successfully created.
 */
-(nullable NSData *)generateDiagnosticsReport;

@end
