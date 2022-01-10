//
//  CascableCore.h
//  CascableCore
//
//  Created by Daniel Kennett on 15/05/15.
//  Copyright (c) 2017 Cascable AB. All rights reserved.
//

#import <CascableCore/CBLPlatformDefines.h>
#import <CascableCore/CBLCoreVersions.h>
#import <CascableCore/CBLConstants.h>
#import <CascableCore/CBLReachabilityConstants.h>
#import <CascableCore/NSError+CBLExtensions.h>
#import <CascableCore/CBLLicenseVerification.h>

// Universal Values
#import <StopKit/StopKit.h>

// Discovery
#import <CascableCore/CBLCameraDiscovery.h>
#import <CascableCore/CBLCameraDiscoveryService.h>
#import <CascableCore/CBLNetworkConfigurationHelper.h>
#import <CascableCore/CBLCameraQRDecoding.h>
#import <CascableCore/CBLCameraManualDiscovery.h>

// Camera and Properties
#import <CascableCore/CBLCamera.h>
#import <CascableCore/CBLCamera+Diagnostics.h>
#import <CascableCore/CBLCameraShotPreviewDelivery.h>
#import <CascableCore/CBLDeviceInfo.h>

// Specific Structures
#import <CascableCore/CBLCameraAEResult.h>
#import <CascableCore/CBLCameraLiveViewFrame.h>
#import <CascableCore/CBLCameraLiveViewAFArea.h>
#import <CascableCore/CBLFocusInfo.h>
#import <CascableCore/CBLFocusPoint.h>

// File System
#import <CascableCore/CBLFileSystemItem.h>
#import <CascableCore/CBLFileSystemFolderItem.h>
#import <CascableCore/CBLFileStorage.h>

// Helpers
#import <CascableCore/CBLRAWImageDescription.h>
#import <CascableCore/CBLImageMetadataWritingHelpers.h>
#import <CascableCore/CBLExifHelpers.h>
#import <CascableCore/CBLImageManipulationHelpers.h>
#import <CascableCore/CBLCorePluginEntryPoint.h>

// This is here to work around an apparent bug in Clang that causes it to insert an import to our private
// Swift module into the public Swift header. This #define makes it import CoreFoundation instead.
#define CascableCoreSwift_Private CoreFoundation
