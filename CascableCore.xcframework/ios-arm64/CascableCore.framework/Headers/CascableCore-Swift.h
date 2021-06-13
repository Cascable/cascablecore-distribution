// Generated by Apple Swift version 5.4 (swiftlang-1205.0.26.9 clang-1205.0.19.55)
#ifndef CASCABLECORE_SWIFT_H
#define CASCABLECORE_SWIFT_H
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <Foundation/Foundation.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(ns_consumed)
# define SWIFT_RELEASES_ARGUMENT __attribute__((ns_consumed))
#else
# define SWIFT_RELEASES_ARGUMENT
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import CoreGraphics;
@import Dispatch;
@import Foundation;
@import ImageCaptureCore;
@import ObjectiveC;
#endif

#import <CascableCore/CascableCore.h>

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="CascableCore",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif



@class NSData;

SWIFT_CLASS("_TtC12CascableCore18CBLEOSSwiftInterop")
@interface CBLEOSSwiftInterop : NSObject
+ (NSData * _Nullable)createJpegDataFrom:(NSData * _Nonnull)heifData SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end

@class NSString;

SWIFT_CLASS_NAMED("CR3Parser")
@interface CBLCR3Parser : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull CR3PreviewImageKey;)
+ (NSString * _Nonnull)CR3PreviewImageKey SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull CR3LargePreviewImageKey;)
+ (NSString * _Nonnull)CR3LargePreviewImageKey SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull CR3ThumbnailImageKey;)
+ (NSString * _Nonnull)CR3ThumbnailImageKey SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull CR3ImageMetadataKey;)
+ (NSString * _Nonnull)CR3ImageMetadataKey SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
+ (NSDictionary<NSString *, id> * _Nullable)extractPreviewAndThumbnailFromData:(NSData * _Nonnull)data SWIFT_WARN_UNUSED_RESULT;
@end


SWIFT_CLASS_NAMED("CascableCoreSwiftBootstrap")
@interface CascableCoreSwiftBootstrap : NSObject
+ (void)setupSwiftLogging;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end




@class ICDevice;
@class ICCameraItem;
@class NSNumber;

SWIFT_AVAILABILITY(macos,introduced=10.11) SWIFT_AVAILABILITY(ios,introduced=13.0)
@interface ICCameraDevice (SWIFT_EXTENSION(CascableCore)) <ICCameraDeviceDelegate>
- (void)device:(ICDevice * _Nonnull)device didOpenSessionWithError:(NSError * _Nullable)error;
- (void)device:(ICDevice * _Nonnull)device didCloseSessionWithError:(NSError * _Nullable)error;
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didCompleteDeleteFilesWithError:(NSError * _Nullable)error;
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didAddItems:(NSArray<ICCameraItem *> * _Nonnull)items;
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didRemoveItems:(NSArray<ICCameraItem *> * _Nonnull)items;
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didReceiveThumbnail:(CGImageRef _Nullable)thumbnail forItem:(ICCameraItem * _Nonnull)item error:(NSError * _Nullable)error SWIFT_AVAILABILITY(macos,introduced=10.15) SWIFT_AVAILABILITY(ios,introduced=13.0);
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didReceiveMetadata:(NSDictionary * _Nullable)metadata forItem:(ICCameraItem * _Nonnull)item error:(NSError * _Nullable)error SWIFT_AVAILABILITY(macos,introduced=10.15) SWIFT_AVAILABILITY(ios,introduced=13.0);
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didRenameItems:(NSArray<ICCameraItem *> * _Nonnull)items;
- (void)cameraDeviceDidChangeCapability:(ICCameraDevice * _Nonnull)camera;
- (void)cameraDevice:(ICCameraDevice * _Nonnull)camera didReceivePTPEvent:(NSData * _Nonnull)eventData;
- (void)deviceDidBecomeReadyWithCompleteContentCatalog:(ICCameraDevice * _Nonnull)device;
- (void)cameraDeviceDidRemoveAccessRestriction:(ICDevice * _Nonnull)device;
- (void)cameraDeviceDidEnableAccessRestriction:(ICDevice * _Nonnull)device;
- (void)didRemoveDevice:(ICDevice * _Nonnull)device;
- (void)deviceDidBecomeReady:(ICDevice * _Nonnull)device;
- (void)device:(ICDevice * _Nonnull)device didReceiveStatusInformation:(NSDictionary<ICDeviceStatus, id> * _Nonnull)status;
- (void)device:(ICDevice * _Nonnull)device didEncounterError:(NSError * _Nullable)error;
- (void)device:(ICDevice * _Nonnull)device didEjectWithError:(NSError * _Nullable)error;
- (BOOL)cameraDevice:(ICCameraDevice * _Nonnull)cameraDevice shouldGetThumbnailOfItem:(ICCameraItem * _Nonnull)item SWIFT_WARN_UNUSED_RESULT;
- (BOOL)cameraDevice:(ICCameraDevice * _Nonnull)cameraDevice shouldGetMetadataOfItem:(ICCameraItem * _Nonnull)item SWIFT_WARN_UNUSED_RESULT;
@end







@protocol CBLCamera;
@protocol CBLCameraLegacyPropertyAPI;
@protocol CBLCameraProperty;

SWIFT_CLASS_NAMED("LegacyPropertyAPIWrapper")
@interface CBLLegacyPropertyAPIWrapper : NSObject
- (nonnull instancetype)initWrapping:(NSObject <CBLCamera, CBLCameraLegacyPropertyAPI> * _Nonnull)legacyPropertyAPIProvider OBJC_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly, copy) NSArray<NSNumber *> * _Nonnull knownPropertyIdentifiers;
- (id <CBLCameraProperty> _Nonnull)propertyWithIdentifier:(CBLPropertyIdentifier)identifier SWIFT_WARN_UNUSED_RESULT;
- (NSArray<id <CBLCameraProperty>> * _Nonnull)populatedPropertiesInCategory:(CBLPropertyCategory)category SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@protocol CBLCameraLiveViewFrame;

/// This class provides camera-agnostic logic for implementing the CascableCore 5.0 live view streaming API.
SWIFT_CLASS_NAMED("LiveViewStreamAdapter")
@interface CBLLiveViewStreamAdapter : NSObject
@property (nonatomic, readonly, strong) dispatch_queue_t _Nonnull deliveryQueue;
@property (nonatomic, readonly, copy) CBLCameraLiveViewFrameDelivery _Nonnull delivery;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
- (nonnull instancetype)initWithDelivery:(CBLCameraLiveViewFrameDelivery _Nonnull)deliveryBlock on:(dispatch_queue_t _Nullable)queue OBJC_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly) BOOL hasPendingFrames;
- (void)deliverFrame:(id <CBLCameraLiveViewFrame> _Nonnull)frame;
@end



@class NSInputStream;
@class NSOutputStream;
@protocol CBLPTPIPQueueDelegate;
@class CBLPTPIPPacket;
@class NSStream;

/// This class provides an asynchonous method of writing and receiving packets from a PTP/IP device.
SWIFT_CLASS_NAMED("PTPIPQueue")
@interface CBLPTPIPQueue : NSObject <NSStreamDelegate>
/// Initialise the receiver with the given streams.
/// If the streams aren’t opened, they will be opened automatically.
/// \param input The input stream.
///
/// \param output The output stream.
///
- (nonnull instancetype)initWithInputStream:(NSInputStream * _Nonnull)input outputStream:(NSOutputStream * _Nonnull)output OBJC_DESIGNATED_INITIALIZER;
/// Set the receiver’s delegate.
/// \param delegate The delegate object.
///
/// \param queue The queue on which to call the delegate methods. Delegates will be called asynchronously.
///
- (void)setDelegate:(id <CBLPTPIPQueueDelegate> _Nullable)delegate onQueue:(dispatch_queue_t _Nonnull)queue;
/// Write a PTP packet to the connected device.
/// See <code>write(packets:,preflightBlock:,whenDone:,onQueue:)</code> for discussion.
/// \param packet The packet to write.
///
/// \param preflight The optional block to call when the command is about to be written to the device. Return <code>YES</code> to continue with writing, otherwise <code>NO</code>. This can be called on any queue.
///
/// \param block The block to invoke when the write succeeded or failed.
///
/// \param queue The queue on which to invoke the block.
///
- (void)writePacket:(NSData * _Nonnull)packet preflightBlock:(BOOL (^ _Nullable)(void))preflight whenDone:(void (^ _Nonnull)(NSError * _Nullable))block onQueue:(dispatch_queue_t _Nonnull)queue;
/// Write some PTP packets to the connected device.
/// The packets will be added to the internal write queue to be written at the receiver’s
/// earliest convenience. There are no guarantees on timing, but the packets will be written
/// in the order in which they’re queued.
/// Responses will be given to the receiver’s delegate.
/// \param packets The packets to write.
///
/// \param preflight The optional block to call when the command is about to be written to the device. Return <code>YES</code> to continue with writing, otherwise <code>NO</code>. This can be called on any queue.
///
/// \param block The block to invoke when the write succeeded or failed.
///
/// \param queue The queue on which to invoke the block.
///
- (void)writePackets:(NSArray<NSData *> * _Nonnull)packets preflightBlock:(BOOL (^ _Nullable)(void))preflight whenDone:(void (^ _Nonnull)(NSError * _Nullable))block onQueue:(dispatch_queue_t _Nonnull)queue;
/// Write a PTP packet to the connected device and wait for the first response packet.
/// The queueing semantics for this method are the same as <code>write(packets:,preflightBlock:,whenDone:,onQueue:)</code>.
/// However, the callback block will be called when a response is received from the connected device
/// instead of going through delegate delivery.
/// \param packet The packet to write.
///
/// \param preflight The optional block to call when the command is about to be written to the device. Return <code>YES</code> to continue with writing, otherwise <code>NO</code>. This can be called on any queue.
///
/// \param block The block to invoke when the write succeeded or failed.
///
/// \param queue The queue on which to invoke the block.
///
- (void)writePacketAndAwaitFirstResponsePacket:(NSData * _Nonnull)packet preflightBlock:(BOOL (^ _Nullable)(void))preflight whenDone:(void (^ _Nonnull)(NSError * _Nullable, CBLPTPIPPacket * _Nullable, NSData * _Nullable))block onQueue:(dispatch_queue_t _Nonnull)queue;
/// Cancel all requests and close all connections to the connected device.
/// After the receiver has been closed, it cannot be reopened.
- (void)close;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
- (void)stream:(NSStream * _Nonnull)aStream handleEvent:(NSStreamEvent)eventCode;
@end


@class CBLCameraDiscovery;
@protocol CBLCameraManualDiscoveryInternal;

SWIFT_CLASS_NAMED("PluginLoader")
@interface CBLPluginLoader : NSObject
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) CBLPluginLoader * _Nonnull shared;)
+ (CBLPluginLoader * _Nonnull)shared SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
/// Attempt to load CascableCore plugins in the current runtime environment. Can only be called once — subsequent
/// calls to this method will do nothing.
/// \param discovery The <code>CameraDiscovery</code> object to register discovery providers with.
///
/// \param manualDiscovery The <code>CameraManualDiscoveryInternal</code> object to register manual discovery providers with.
///
- (void)loadPluginsWithDiscovery:(CBLCameraDiscovery * _Nonnull)discovery manualDiscovery:(id <CBLCameraManualDiscoveryInternal> _Nonnull)manualDiscovery;
@end


/// RunloopQueue is a serial queue based on CFRunLoop, running on the background thread.
SWIFT_CLASS_NAMED("RunloopQueue")
@interface CBLRunloopQueue : NSObject
/// Init a new queue with the given name.
/// \param name The name of the queue.
///
- (nonnull instancetype)initWithName:(NSString * _Nullable)name OBJC_DESIGNATED_INITIALIZER;
/// Returns <code>true</code> if the queue is running, otherwise <code>false</code>. Once stopped, a queue cannot be restarted.
@property (nonatomic, readonly) BOOL running;
/// Execute a block of code in an asynchronous manner. Will return immediately.
/// \param block The block of code to execute.
///
- (void)async:(void (^ _Nonnull)(void))block;
/// Execute a block of code in a synchronous manner. Will return when the code has executed.
/// It’s important to be careful with <code>sync()</code> to avoid deadlocks. In particular, calling <code>sync()</code> from inside
/// a block previously passed to <code>sync()</code> will deadlock if the second call is made from a different thread.
/// \param block The block of code to execute.
///
- (void)sync:(void (^ _Nonnull)(void))block;
/// Query if the caller is running on this queue.
///
/// returns:
/// <code>true</code> if the caller is running on this queue, otherwise <code>false</code>.
- (BOOL)isRunningOnQueue SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


@interface CBLRunloopQueue (SWIFT_EXTENSION(CascableCore))
/// Schedules the given stream into the queue.
/// \param stream The stream to schedule.
///
- (void)scheduleStream:(NSStream * _Nonnull)stream;
/// Removes the given stream from the queue.
/// \param stream The stream to remove.
///
- (void)unscheduleStream:(NSStream * _Nonnull)stream;
@end

@class NSURLConnection;

@interface CBLRunloopQueue (SWIFT_EXTENSION(CascableCore))
/// Schedules the given NSURLConnection into the queue.
/// \param connection The connection to schedule.
///
- (void)scheduleConnection:(NSURLConnection * _Nonnull)connection;
/// Removes the given NSURLConnection from the queue.
/// \param connection The connection to remove.
///
- (void)unscheduleConnection:(NSURLConnection * _Nonnull)connection;
@end



enum ReachabilityStatus : NSInteger;

SWIFT_CLASS("_TtC12CascableCore16WiFiReachability")
@interface WiFiReachability : NSObject
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
/// The shared reachability object.
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, strong) WiFiReachability * _Nonnull reachability;)
+ (WiFiReachability * _Nonnull)reachability SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly, copy) NSString * _Nonnull reachabilityChangedNotificationName;)
+ (NSString * _Nonnull)reachabilityChangedNotificationName SWIFT_WARN_UNUSED_RESULT;
/// The current reachability status.
@property (nonatomic, readonly) enum ReachabilityStatus status;
@end

typedef SWIFT_ENUM(NSInteger, ReachabilityStatus, open) {
  ReachabilityStatusNotReachable = 0,
  ReachabilityStatusReachableViaWiFi = 1,
};

#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop
#endif
