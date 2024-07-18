//
//  CBLFileSystemFolderItem.h
//  CascableCore
//
//  Created by Daniel Kennett on 17/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;

@protocol CBLFileSystemItem;

/** Represents a folder on a camera's storage device. */
NS_SWIFT_NAME(FileSystemFolderItem)
@protocol CBLFileSystemFolderItem <NSObject, CBLFileSystemItem>

/** 
 Returns an array of child objects, if the folder has been loaded.
 
 @note For performance and memory reasons, storage objects to not automatically load the contents
 of any of its child folders - you need to iterate the filesystem in a manner that best fits your application.
 */
@property (nullable, nonatomic, readonly, copy) NSArray <id <CBLFileSystemItem>> *children;

/** Returns `true` if this item has successfully loaded its children (even if it has no children), otherwise `false`.

 @note For performance and memory reasons, storage objects to not automatically load the contents
 of any of its child folders - you need to iterate the filesystem in a manner that best fits your application.
 */
@property (nonatomic, readonly) BOOL childrenLoaded;

/** Returns `true` if this item is currently in the process of loading its children. */
@property (nonatomic, readonly) BOOL childrenLoading;

/**
 Attempt to load the item's children.

 @note For performance and memory reasons, storage objects to not automatically load the contents
 of any of its child folders - you need to iterate the filesystem in a manner that best fits your application.

 @param callback The callback to trigger when the operation succeeds (or fails).
 */
-(void)loadChildren:(nonnull CBLErrorableOperationCallback)callback;

@end
