//
//  CBLFileSystemFolderItem.h
//  CascableCore
//
//  Created by Daniel Kennett on 17/11/15.
//  Copyright © 2015 Daniel Kennett. All rights reserved.
//

@import Foundation;
#import <CascableCore/CBLCamera.h>
#import <CascableCore/CBLFileSystemFolderItem.h>

@protocol CBLFileStorage;
@protocol CBLCamera;

/** Filesystem operation types for storage modified observers. */
typedef NS_ENUM(NSUInteger, CBLFileSystemModificationOperation) {
    /** The modification was of an unknown type. */
    CBLFileSystemModificationUnknown,
    /** File(s) were added to the storage. */
    CBLFileSystemModificationFilesAdded,
    /** File(s) were removed from the storage. */
    CBLFileSystemModificationFilesRemoved
} NS_SWIFT_NAME(FileSystemModificationOperation);

/** Identifiers for camera slots. */
typedef NS_ENUM(NSInteger, CBLStorageSlot) {
    /** The numbering of the storage's slot is unknown. */
    CBLStorageSlotUnknown,
    /** The storage is in the camera storage slot marked 'Slot 1'. */
    CBLStorageSlotSlot1,
    /** The storage is in the camera storage slot marked 'Slot 2'. */
    CBLStorageSlotSlot2
} NS_SWIFT_NAME(StorageSlot);

/** A filesystem observation block.
 
 @param storage The filesystem storage instance that the change occurred on. 
 @param modifiedFolder The folder in which the change occurred.
 @param operation The operation that occurred.
 @param affectedItems The items that were added or removed. 
 */
typedef void(^CBLFileStorageFilesModifiedObserver)(id <CBLFileStorage> _Nonnull storage,
                                                   id <CBLFileSystemFolderItem> _Nullable modifiedFolder,
                                                   CBLFileSystemModificationOperation operation,
                                                   NSArray <id <CBLFileSystemItem>> * _Nullable affectedItems) NS_SWIFT_NAME(FileStorageFilesModifiedObserver);

/**
 A filesystem observer token. Required to unregister an oberver.
 */
typedef NSString CBLFileStorageObserverToken NS_SWIFT_NAME(FileStorageObserverToken);

/**
 * Represents a file storage container in a camera, such as an SD card.
 */
NS_SWIFT_NAME(FileStorage)
@protocol CBLFileStorage <NSObject>

/** Returns the description of the storage container as reported by the camera. */
@property (nullable, nonatomic, readonly, copy) NSString *storageDescription;

/** Returns the volume label of the storage container as reported by the camera. Can be `nil`. */
@property (nullable, nonatomic, readonly, copy) NSString *label;

/** Returns a name string appropriate for display to the user. */
@property (nullable, nonatomic, readonly, copy) NSString *displayName;

/** Returns the free space of the storage container, in bytes. */
@property (nonatomic, readonly) uint64_t availableSpace;

/** Returns the capacity of the storage container, in bytes. */
@property (nonatomic, readonly) uint64_t capacity;

/** The physical slot the file storage object occupies. */
@property (nonatomic, readonly) CBLStorageSlot slot;

/** Returns `YES` if the storage container allows write access, otherwise `NO`. */
@property (nonatomic, readonly) BOOL allowsWrite;

/**
 Returns `YES` if the storage container contains images that the camera is incapable of transferring.

 For example, some older Panasonic models will list RAW images, but aren't capable of transferring them. These
 images are ignored by CascableCore, but it may lead to user confusion if they're presented with an empty list.

 This property can be useful to provide the user context as to why no images are available.
 */
@property (nonatomic, readonly) BOOL hasInaccessibleImages;

/**
 If available, returns the overall progress of the storage device's cataloging progress.
 This is not neccessarily tied to any particular `loadChildren` call.
 */
@property (nonatomic, readonly, nullable, strong) NSProgress *catalogProgress;

/** Returns the camera associated with this storage. */
@property (nullable, nonatomic, readonly, weak) id <CBLCamera> camera;

/** Returns the root directory of this storage. */
@property (nonnull, nonatomic, readonly, strong) id <CBLFileSystemFolderItem> rootDirectory;

/** Add an observer to the storage's filesystem.
 
 The registered observer block will be called on the main queue.

 @note Changes in directories that haven't had their children loaded at least once will not trigger a notification.

 @param observer The observer block to be called when the filesystem changes.
 @return Returns an observer token to be used when removing the observer.
 */
-(CBLFileStorageObserverToken * _Nonnull)addFileSystemObserver:(nonnull CBLFileStorageFilesModifiedObserver)observer;

/** Remove an observer to the storage's filesystem.
 
 @note It is safe for a triggered observer block to remove itself during execution, allowing easy one-shot observations.

 @param observer The existing observer token to remove.
 */
-(void)removeFileSystemObserverWithToken:(nonnull CBLFileStorageObserverToken *)observer;

@end
