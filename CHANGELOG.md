# CascableCore 12.4

### API Changes

- Added the `CBLVideoFormatCompressionLevel` enum and `compressionLevel` property to `id <CBLVideoFormatPropertyValue>`.

### Bug Fixes

- Fixed an issue that would cause the `CBLErrorCodeRequiresPhysicalInteraction` error to *not* be thrown when failing to switch to stills mode due to the physical position of the stills/video switch on some Canon camera models.

- `-setCurrentCommandCategories:completionCallback:` now correctly waits for Canon cameras to switch in/out of the requisite mode before calling the completion handler, matching the documented behaviour.


# CascableCore 12.3

### New Property: Video Recording Format

The new `CBLPropertyIdentifierVideoRecordingFormat` property allows the ability to change the camera's video recording format on supported cameras. This property is currently implemented for Canon and Nikon cameras.

Objects for this property conform to `id <CBLVideoFormatProperty>` and values to `id <CBLVideoFormatPropertyValue>`, allowing the programmatic inspection of the frame rate and frame size of each format value. For users of our [CascableCoreSwift](https://github.com/cascable/cascablecore-swift) library, you'll get a typed property with `VideoFormatValue` common values.

### Camera Compatibility

- Added support for the Canon EOS R6 Mark II, EOS R100, EOS R8, and EOS R50. [CORE-558]

- Added support for the Nikon Z8 and Z30.

### Bug Fixes

- Fixed a problem that would cause video recording to fail to start on newer Nikon cameras. [CORE-507]

- Fixed a problem that would cause still image shooting to get "stuck" on Canon cameras that'd been connected to other apps (such as EOS Utility) that configure the camera with a "PC" image destination before being connected to CascableCore without being switched off in between - CascableCore will clear that destination upon connection. A future update will enable full support for this shooting mode and the `CBLPropertyIdentifierImageDestination` property. [CORE-563] 


# CascableCore 12.2.4

### Bug Fixes

- Fixed a crash that would occur on the "iOSOnMac" environment on Apple Silicon when searching for USB devices. Running CascableCore in this mode is currently experimental — please report any problems you find.


# CascableCore 12.2.3

### Bug Fixes

- Fixed a crash that could occur on macOS when disconnecting from a USB camera on macOS 13 Ventura. [CORE-399]

- Improved internal protection around the handling of messages on USB cameras on iOS. [CORE-400]

### Other

- CascableCore now requires macOS 10.13 High Sierra or later.


# CascableCore 12.2.2

### Bug Fixes

- Fixed a bug that could cause live view to not start again after it'd been stopped on some Canon cameras. [CORE-394]


# CascableCore 12.2.1

### Camera Compatibility

- Added support for the Canon EOS R7 and EOS R10. [CORE-392]

### Other

- CascableCore now requires iOS 11.0 or higher.


# CascableCore 12.2

### Improvements

- Improved support for HEIF images when shooting with Sony cameras. This includes correct property display values when the camera is in HEIF mode, and camera-initiated transfers from these cameras may now report an original representation UTI of `public.heic` and a suggested filename extension of `HEIC`.

    **Note:** Sony cameras use the extension `.HIF` for HEIF images, which isn't recognised by macOS or iOS as a valid extension for these files — it should be `.HEIC`. CascableCore currently exposes these filenames as-is — for example, a camera-initiated transfer of a HEIF image from a Sony camera would report a suggested filename extension of `HEIC`, but the `fileNameHint` will report a value like `DSCXXXXX.HIF`.

### Bug Fixes

- Fixed the reported display values of some shutter speeds faster than 1/8000 via an updated StopKit.

- Fixed a bug that would cause camera-initiated transfers to fail from the Sony α1 when connected via USB. [CORE-376]


# CascableCore 12.1

### API Changes

- Methods for streaming files (`-streamItemWithPreflightBlock:…`) now return an `NSProgress` object for easier progress reporting.

### Documentation Changes

- Clarified that file streaming (`-streamItemWithPreflightBlock:…`, etc) can, in some circumstances, deliver empty data objects during streaming. This is not an error — client code should handle this circumstance correctly and return the desired streaming instruction.

### Bug Fixes

- Fixed "Delegate Updated" messages flooding the system console when connected to a camera via USB.

- Fixed a crash when serialising certain exposure property values from some cameras via `NSCoding`. [CORE-378]


# CascableCore 12.0.1

This release backports the bug fixes from 12.1 and 12.2 without including the API changes from 12.1.


# CascableCore 12.0

### Increased Compatibility with Sony Cameras

CascableCore 12 greatly expands support for Sony cameras. USB remote control via **PC Remote (USB)** has been added for the following already-supported models:

- α7 II, α7 III
- α7R II, α7R III
- α7S, α7S II
- α6000, α6300, α6500

In addition, USB remote control via **PC Remote (USB)** and network remote control via **Control with Smartphone**, and **PC Remote (WiFi)** (where available) has been added for these newly-supported models:

- α7 IV
- α7R IV
- α7S III
- α7C
- α9, α9 II
- α1
- α6100, α6400, α6600
- ZV-E10, ZV-1
- RX100 V, RX100 VI, RX100 VII

### Other Camera Compatibility

- Added support for the OM System OM-1. This camera is identified as an Olympus camera (`CBLCameraFamilyOlympus`) by CascableCore.

### New API: Camera-Initiated Transfer

Shot preview (`id <CBLCameraShotPreviewDelivery>`) has been removed and replaced by a more powerful API that's more suited to the fact that original images can be transferred as well as previews.

The new API uses the terminology of "camera-initiated transfers", and is designed to handle both previews of shots added to a memory card as well as the transfer of full image files — including cameras set to "Host Only" saving – i.e., the full image needs to be transferred to the host to avoid data loss. The new API can handle simple cases ("I just want a preview") and more complex ones ("I want a preview, and if the image would otherwise be lost, the original image too").

This new API is defined in `CBLCameraInitiatedTransfer.h`. The flow is as follows:

- The client receives a callback from the camera notifying it of a new camera-initiated transfer request. This will be an object of type `id <CBLCameraInitiatedTransferRequest>`, which contains some metadata about the incoming image, whether or not transferring it is required to avoid data loss (i.e., "Host Only" saving), and which representations the request contains.

- The client then executes the request, informing it which representations are wanted. Current representations are "preview" and "original". The image transfer is then performed, optimising data transfer if possible (for instance, if the client only requests the preview representation of a RAW image, CascableCore will try to avoid transferring the entire RAW image).

- When the request is complete, a result object of type `id <CBLCameraInitiatedTransferResult>` will be delivered. The result object contains additional metadata about the transferred image, as well as helpers for writing representations to disk, getting them as in-memory data, and getting preview images.

Previous uses of the shot preview API can be migrated to camera-initiated transfers with no loss in functionality by transferring preview representations (`CBLCameraInitiatedTransferRepresentationPreview`), then using either `-generatePreviewImage:` or `-generateDataForRepresentation:completionHandler:` on the result.

### New API: Stepped Properties

CascableCore now supports "stepped properties" — properties that don't have a list of valid values, and are instead changed by adjusting the property "up" or "down" in steps. 

This change has been implemented in a backwards-compatible way, and with no code changes stepped properties will appear read-only (i.e., will have an empty `validSettableValues` value).

To implement stepped properties, see the new `valueSetType` property on `id <CBLCameraProperty>`. If that returns `CBLPropertyValueSetTypeStepping`, you can use the `incrementValue:` and `decrementValue:` methods to change that property's value.

### Other API Changes

- Added the `CBLPropertyIdentifierImageDestination` property. Values are typically along the lines of "Host", "Camera", and "Camera & Host". Common values are of type `CBLPropertyCommonValueImageDestination`.

- Added the error code `CBLErrorCodeIncorrectCommunicationMode`, of which connections will fail on a Sony USB camera not in PC Remote mode.

- Added the error code `CBLErrorCodeObjectTooLarge`, which can be returned when requesting very large assets as in-memory data objects from an `id <CBLCameraInitiatedTransferResult>` object.

### Known Issues

- There is no video timer on some Sony cameras when being controlled via USB. Video recording still works, if available.

- Live view zoom is not yet implemented for newly-supported Sony cameras.

- Extremely new cameras (such as the α7 IV) support touch AF via remote control, but this is not yet supported in CascableCore.


# CascableCore 11.0

### Video Recording

Added an initial, basic API for working with video recording. This API has currently been implemented for Canon EOS and Nikon cameras.

To see if a camera supports video recording, check for `CBLCameraSupportedFunctionalityVideoRecording`. To switch a camera into a mode that allows video recording, use `CBLCameraAvailableCommandCategoryVideoRecording`.

Once the camera is in a mode in which video recording can go ahead, start and stop video recording with `-startVideoRecording:` and `-endVideoRecording:`. Whether or not the camera is currently recording video can be observed with `-isRecordingVideo`. 

Video recording has ramifications across the entire API surface of a camera, and particularly changes a number of assumptions you may have been making when working with Canon cameras. In particular: 

- A number of APIs are unavailable while video is recording, including all filesystem access. See the new error code `CBLErrorCodeVideoRecordingInProgress`.

- Canon EOS and Nikon cameras can now be placed into a mode where taking photos isn't allowed. Previously, these cameras always allowed both stills shooting and filesystem access.

- Older Canon EOS cameras don't allow video recording while WiFi is active. If you try to start recording video via a WiFi connection, the `CBLErrorCodeDisallowedOnCurrentTransport` error will be returned.

- Some cameras require moving a physical switch to move the camera in or out of video mode. If that's the case, attempting to switch the available command categories to or from `CBLCameraAvailableCommandCategoryVideoRecording` may produce the error `CBLErrorCodeRequiresPhysicalInteraction`. If this happens, instruct the user to flip the relavent switch manually. The `-currentCommandCategories` property is observable with Key-Value Observing, and will change automatically when the video mode is changed by the user.

#### New API

- Added `CBLCameraSupportedFunctionalityVideoRecording` to enable checks to see if video recording is supported by a particular camera.

- Added `CBLCameraAvailableCommandCategoryVideoRecording` to put a camera into video recording mode.

- Added the `-isRecordingVideo` and `-currentVideoTimerValue` properties to `id <CBLCamera>`, which are observable with Key-Value Observing.

- Added `-startVideoRecording:` and `endVideoRecording:` to `id <CBLCamera>` to start and stop video recording.

- Added the error codes `CBLErrorCodeVideoRecordingInProgress`, `CBLErrorCodeRequiresPhysicalInteraction`, `CBLErrorCodeDisallowedOnCurrentTransport`, `CBLErrorCodeRequiresLiveView`, `CBLErrorCodeCardError`, and `CBLErrorCodeStorageFull`.

#### Breaking API changes:

- `CBLCameraAvailableCommandCategoryRemoteShooting` has been renamed to `CBLCameraAvailableCommandCategoryStillsShooting`.

- A number of existing situations where a camera would return a `CBLErrorCodeNotAvailable` error code have been changed so a more accurate error code is returned instead. Particularly, `CBLErrorCodeRequiresLiveView` and `CBLErrorCodeVideoRecordingInProgress` have replaced a number of more generic existing error paths.

#### Known Issues

- Some older Canon cameras will automatically terminate live view when exiting video mode. If this happens, re-start live view.

- Newer Nikon cameras have separate properties for video exposure settings, which aren't currently exposed by CascableCore. They will be added in a future release.

### Camera Compatibility

- Added support for the Canon EOS R3.

- Added `CBLCameraSupportedFunctionalityRemoteControlWithoutLiveView` to the Canon EOS 5D Mark II. [CORE-363]

- Greatly improved file transfer performance from a number of Nikon cameras. [CORE-354]

### Bug Fixes

- CascableCore will no longer attempt to deliver shot preview callbacks for video or other non-image file types from Canon or Nikon cameras.

- Improved the accuracy of the `focused` and `active` properties of `id <CBLCameraLiveViewAFArea>` objects from Canon cameras.

- Fixed some missing autoexposure mode localized display values for certain Nikon cameras. [CORE-347]


# CascableCore 10.1.2

### Camera Compatibility

- Added support for "focusless half-press" for the EOS M6 Mark II (i.e., photos can be taken without autofocus even if the camera is set to autofocus). [CORE-353]


# CascableCore 10.1.1

### Bug Fixes 

- Fixed an issue that would cause live view to get into an odd state on the Nikon D800 after taking a photo. [CORE-337]


# CascableCore 10.1

### New Features

- Added full support for Canon's Fv mode, including a new common value for flexible priority autoexposure modes (`CBLPropertyCommonValueAutoExposureModeFlexiblePriority`). [CORE-341]

- Autoexposure results now report whether autoexposure is clipped (i.e., values are blinking) on Canon cameras. [CORE-342]

### Bug Fixes 

- Fixed an issue that could cause "Automatic" shutter speed and aperture values to be represented incorrectly on some Canon cameras. [CORE-341]

- Fixed an issue that could cause incorrect autoexposure results on Canon EOS R5 and R6 cameras. [CORE-342]

- Added support for live view on older Nikon cameras, including the D800 and D810. [CORE-337]

- Fixed `CBLImageQualityTIFF` not being represented properly on some Nikon cameras. [CORE-337]

- Fixed the disconnection callback never being fired on USB-connected cameras on macOS Monterey. [CORE-345]

- Nikon cameras are no longer explicitly put into "Application Mode" when connected to via USB. [CORE-345]


# CascableCore 10.0.2

### New Features

- Nikon cameras can now be operated with full remote control functionality over USB on iOS 15.0 and higher. [CORE-207]

- Added support for live view zoom (`CBLCameraSupportedFunctionalityZoomableLiveView`) on newer Nikon cameras, including the Z series. [CORE-50]

### Changes

- Added support for "focusless half-press" for the EOS M50 (i.e., photos can be taken without autofocus even if the camera is set to autofocus). [CORE-326]

### Bug Fixes

- Fixed a bug that could cause the EOS M5 and EOS M6 Mark II to not correctly start live view. [CORE-302, CORE-325]

- Fixed a bug where certain Canon cameras would be extremely slugglish to respond to events when connected via USB on iOS. [CORE-326]


# CascableCore 10.0.1

### Bug Fixes

- Fixed an issue that could cause user authorisation for USB cameras on iOS 14+ to not be obtained correctly. [CORE-313]

- Fixed an issue that caused the exposure mode property to be incorrectly reported from Phase One cameras in some instances. [CORE-318]


# CascableCore 10.0

This version of CascableCore contains a significant number of large breaking changes.

### New Property API

CascableCore's old API for dealing with camera settings has been replaced with a more modern one. The significant change here is that we are no longer trying to unify every single camera property under a single "universal" system, which was getting out of hand (just take a look at the old `CBLAutoExposureMode` enum!).

Instead, properties are presented as an opaque list of values, which have display values for presentation to the user. By and large, what these values represent are implementation details of the camera themselves, and should be presented to the user as-is — the display values should be recognisable to the user.

However, it is of course useful to either know what the camera is doing, or to target a particular camera setting. For this case, we have "common values" — values that are both common to most cameras, and useful to be able to target when getting and setting values. You can't get or set common values directly, but rather you can ask a property value "Do you match this common value?" or "Give me a value to set that matches this common value.".

For example, in example below, we print out the camera's current white balance:

```
id <CBLCameraProperty> whiteBalance = [camera propertyWithIdentifier:CBLPropertyIdentifierWhiteBalance];
NSLog(@"The camera's white balance is: %@", whiteBalance.currentValue.localizedDisplayValue);
```

However, since we don't know what particular strings the connected camera might report, we can't programatically tell what the white balance actually is. For this, we need to use the common value:

```
id <CBLCameraProperty> whiteBalance = [camera propertyWithIdentifier:CBLPropertyIdentifierWhiteBalance];
BOOL isTungsten = (whiteBalance.currentValue.commonValue == CBLPropertyCommonValueWhiteBalanceTungsten);
```

And additionally, we can set a particular white balance if the camera is able:

```
id <CBLCameraProperty> whiteBalance = [camera propertyWithIdentifier:CBLPropertyIdentifierWhiteBalance];
id <CBLPropertyValue> flashWhiteBalanceValue = [whiteBalance validValueMatchingCommonValue:CBLPropertyCommonValueWhiteBalanceFlash];
if (flashWhiteBalanceValue != nil) {
    [whiteBalance setValue:flashWhiteBalanceValue completionQueue:dispatch_get_main_queue() completionHandler:^(NSError *error) {
        NSLog(@"Set white balance value with error: %@", error);
    }];
}
```

The main differences between the new API and old one are:

  - The property system is always interacted with via objects representing that property, rather than directly with the camera.
  - Property values are always `id <CBLPropertyValue>` objects, rather than `id`.
  - Property values and valid settable values are opaque, and don't have constants defined for them (many enums have been removed).
  - Common settings you're likely to want to query programmatically can be translated using "common values".
  
You can see the new `CBLCameraPropertyAPI.h` file to see the whole API and its documentation.

### Changed Live View API

Live view frames can now contain pixel data that isn't JPEG data. The API has been updated to reflect this, and the `rawImageData` property has been renamed to `rawPixelData` to make sure uses of this property are dealt with. You can use the new `rawPixelFormat` property to query the pixel format at a basic level, and `rawPixelFormatDescription` at a detailed level.

This change makes no difference to the `image` property if you're relying on CascableCore to parse live view frame images.

On supported cameras, live view can be cropped using `-setLiveViewCrop:completionCallback:` and `-resetLiveViewCrop:` if the camera supports the new `CBLCameraSupportedFunctionalityCroppableLiveView` functionality. Instead of calling the old zoom methods, live view can effectively zoomed in by cropping the image — the crop is applied on the camera side, before the image is transmitted, so the image delivered by the camera is the same size as before. This allows the implementation of pinch-to-zoom for live view.

### Manual Discovery API

In situations where automatic camera discovery over the network is not desirable or available, CascableCore now has a "manual discovery" API that lets your users say "Hey, there's a Canon camera at this IP address" and have you do something about it. 

To use this API, first you need a camera descriptor. There are descriptors for specific IP addresses and for cameras at the suggested gateway (i.e., cameras that create their own WiFi networks):

```
CBLCameraDescriptor *gatewayNikon = [CBLCameraDescriptor descriptorForCameraFamilyAtSuggestedGateway:CBLCameraFamilyNikon];
CBLCameraDescriptor *ipCanon = [CBLCameraDescriptor descriptorForCameraFamily:CBLCameraFamilyCanon atIPAddress:@"10.0.1.123"];
```

Once you have a descriptor, you must attempt to resolve it into a camera. To do this, get the manual discovery object then use it to resolve the camera. It's a good idea to make sure that manually resolving the camera family you're interested in is possible, since not all cameras can be manually resolved:

```
id <CBLCameraManualDiscovery> manualDiscovery = [[CBLCameraDiscovery sharedInstance] manualDiscovery];

if (![manualDiscovery.supportedCameraFamilies containsObject:@(descriptor.cameraFamily)]) {
    NSLog(@"Can't resolve this kind of camera!");
    return;
}

[manualDiscovery attemptToDiscoverCamera:descriptor completionHandler:^(id <CBLCamera> camera, NSError *error) {
    // Use the camera.
}];
```

It's important to note that in some cases, manual discovery can succeed even if the given descriptor doesn't point to a valid camera. This can happen if it's impossible to tell if a camera exists before actually connecting to it. In such circumstances, the camera object will fail to connect. This can take a little while if the underlying protocol has a long timeout.

Additionally, although the manual discovery object is fetched from `CBLCameraDiscovery`, it is *completely* separate from the automatic discovery provided by that class. You don't need to use automatic discovery at all, and a camera resolved using manual discovery will *not* be added to the automatic discovery's list of cameras (unless automatic discovery is running and the camera is separately discoverable).

Finally, manual discovery is much more error-prone than automatic discovery given that you could be trying to connect to a camera that doesn't exist, is already connected to by something else, etc. Make sure you have robust error handling around connection to and unexpected disconnection from cameras.


### Plugin API

CascableCore now allows camera support to be added by including separate framework binaries into the client application. These will then be discovered and initialised automatically at runtime by CascableCore with no intervention from the client app. 

New APIs have been added to `CBLCameraDiscovery` to allow control over plugins. The `-loadedPluginIdentifiers` property allows clients to see which plugins are available, and `-enabledPluginIdentifiers` to see which ones are enabled (plugins are enabled by default). Plugins can be enabled or disabled with `-setEnabled:forPluginWithIdentifier:`. This allows you to, for instance, only have the fake camera enabled in the iOS Simulator.

For information on the plugin API itself, see the new `CBLCorePluginEntryPoint.h` file.

At this point, the only publicly available plugin is a "Fake Camera" plugin that allows you to work with CascableCore without having a physical camera connected. For information on this, see that project's page.

### Other API Changes

- Added the `-originalBackingImageUrl` property to `id <CBLCameraShotPreviewDelivery>`. In some circumstances, CascableCore will choose to store the source data for the shot preview on disk instead of in RAM to conserve resources. If this is the case, the value of this property will be non-nil and you can access the original image at the given location while the shot preview delivery object is active.

- Added `+[CBLNetworkConfigurationHelper ipv4AddressFromNetServiceData:]` for converting binary address data into an IP address.

- Due to the fact that additional cameras can be added by plugins, `CBLCameraFamily` is no longer an enum.

- Added `-requestProgress` to `id <CBLCameraShotPreviewDelivery>`, which can be used to observe shot preview progress for some cameras. 

- Various APIs have been tidied up for use in Swift.

### Bug Fixes

- Canon cameras now correctly call the live view termination handler if live view is terminated by disconnecting from the camera.

### Known Issues

- Live view cropping and the "ready for capture" property are currently only supported by Phase One cameras. This functionality will come to other cameras soon.


# CascableCore 9.2.4

### Changes

- Improved CascableCore's behaviour around image previews involving RAW or RAW+JPEG images. In most cases, preview loading will be faster. [CORE-288]

### Bug Fixes

- The `completeQueue` parameter is now correctly respected when a file streaming operation fails on Nikon cameras.


# CascableCore 9.2.3

### Changes

- Improved the image size of previews from files on Nikon Z-series cameras. [CORE-288]


# CascableCore 9.2.2

### Bug Fixes

- Fixed a problem in which connections would fail to the Nikon D3200 and other similar era Nikon cameras. [CORE-215]


# CascableCore 9.2.1

### Bug Fixes

- Fixed a problem in which the connection completion callback would not be called in some circumstances for Canon and Nikon cameras. [CORE-213]


# CascableCore 9.2

### New Features

- Added native support for Apple Silicon Macs. [CORE-198]

- Added support for the Canon EOS 850D/T8i and the EOS M50 Mark II. [CORE-192]

- Added support for the Canon EOS R5 and R6 [CORE-182]: 

    - Added `CBLDriveModeCanonHighSpeedPlusContinuousShooting` to `CBLDriveMode`.
    
    - Added support for HEIF images when working with files on a Canon cameras, and on all cameras connected via USB. 
    
      **Note:** Canon cameras use the extension `.HIF` for HEIF images, which isn't recognised by macOS or iOS as a valid extension
      for these files — it should be `.heic`. CascableCore currently exposes these files as-is.
      
      **Note:** Previewing HEIF images either via `-fetchPreviewWithPreflightBlock:…` or a shot preview callback can take longer
      than expected for the file size due to the additional processing time required to render HEIF images.
    
- Canon cameras can now be operated with full remote control functionality over USB on iOS 14.2 and higher. [CORE-188]
    
- Added the following APIs to `CBLCameraDiscovery`:

    - `-hasAuthorizationToDiscoverWiredCameras` allows clients to know if camera discovery is likely to be able to see connected wired cameras.

    - `-attemptToObtainWiredCameraAuthorization:` allows clients to prompt for the correct authorisation for the current OS version.
    
    - `discoveryMode`, a property allowing the client to choose whether to search for network cameras, USB cameras, or both. [CORE-204]

### Bug Fixes

- Improves camera detection on macOS, fixing problems that could cause cameras to be incorrectly detected, or not detected at all. [CORE-205]


# CascableCore 9.1

### New Features

- Added support for the Olympus E-M1 Mark III in "Device Connection mode". [CORE-49]

### Other Changes

- As part of the work for the Olympus E-M1 Mark III, several improvements were made to the Olympus subsystem. This may change behaviour for existing Olympus models:
    
    - If provided by the camera, the reported camera serial number will now be the "real" serial number rather than a different unique ID.
    
    - If supported by the camera, Olympus cameras can now support `CBLCameraSupportedFunctionalityFileDeletion`, and files can be deleted.
    
    - If supported by the camera, multiple storage slots are now fully supported.

### Bug Fixes

- Fixed failure to connect to USB-connected cameras on iOS 14 betas.


# CascableCore 9.0

### New Features

- Nikon and Canon cameras can now be operated with full remote control functionality over USB on macOS. [CORE-104]

### Bug Fixes

- Fixed a bug that could cause the connection process to hang on some Canon models with no SD card inserted.

- On Canon models, fixed a bug that would cause the live view termination handler to not be called when live view was terminated by the camera, due to low battery or other circumstsances. [CORE-143]

- Fixed a number of bugs that could cause crashes when attempting to connect to unsupported devices. [CORE-148]

- CascableCore will no longer attempt to connect to iOS devices connected via USB on the Mac.

- USB-connected cameras should be discovered more quickly.

- Canon cameras should no longer power down after a period of time if connections are left open without photos being taken. [CORE-154]

- Calling `touchAFAtPoint:completionCallback:` on older Canon models of camera will now correctly engage autofocus, rather than just moving the focus point. [CORE-160]


# CascableCore 8.0.2

### New Features

- Added support for newer Fujifilm cameras, including the X-T4 and X100V. [CORE-100]

- Added support for the Canon EOS 250D. [CORE-142]

### Other Changes

- Higher resolutions are used for live view on Nikon cameras that support it. Previously, all Nikon cameras streamed an image of 320x240 pixels when `CBLLiveViewOptionFavorHighFrameRate` was set to `YES`, otherwise 640x480 pixels. With this update, newer cameras will stream sizes of 640x480 pixels and 1024x768 pixels respectively. [CORE-103]

### Bug Fixes

- Cancelling pairing requests from Canon cameas after pairing has completed is now correctly ignored. [CORE-122]


# CascableCore 8.0.1

### Bug Fixes

- Fixed a bug that would cause CascableCore to incorrectly detect some network routers as cameras. [CORE-93]


# CascableCore 8.0

### New Features 

- Added support for accessing images on wired cameras. This requires iOS 13.2 or macOS 10.15 or higher. [CBC-222]

### API Changes

- Added `CBLCameraFamilyGeneric` to `CBLCameraFamily`.

- Added the `-cameraTransport` property to `id <CBLCamera>`, which can be one of two values: `CBLCameraTransportNetwork` or `CBLCameraTransportUSB`.

- Added the `-operatingSystemIsNewEnoughForWiredCameras` property to `CBLCameraDiscovery`.

- Added the `-catalogProgress` property to `id <CBLFileStorage>`.

- `-supportedFunctionality` and related APIs will always report that a camera supports `CBLCameraSupportedFunctionalityDirectFocusManipulation` if it is able to do so, even if it currently isn't in a state to execute those commands.

### Bug Fixes

- Fixed a bug that could cause a crash when passing invalid data to the RAW parser.

- Timestamps for filesystem items on Olympus cameras are no longer incorrectly parsed using the system timezone. [CBC-226]


# CascableCore 7.0.1

### New Features

- Added support for the Canon EOS 90D. [CBC-219]

### Bug Fixes

- Fixed a problem that would cause clock sync to fail on Canon cameras during connection (with `CBLConnectionFlagSyncCameraClockToSystemClock` set). [CBC-220]

- Fixed the CR3 parser not returning a large preview image for CR3 files from certain cameras (including the EOS RP). [CBC-216]


# CascableCore 7.0

### API Changes

- The client name from `[CBLCamera -connectWithClientName:…]` methods has been removed. The client name is now registered with `CBLDiscovery`'s `clientName` property. 

- `[CBLNetworkConfigurationHelper -ssidOfInterface:]` has been deprecated on iOS.

- Added `CBLErrorCodeNeedsNewPairing`, which will be returned as an error code in situations where connection failures could be caused by the camera being paired to another device or app.

### Bug Fixes

- Fujifilm cameras can now be discovered on iOS devices running iOS 13.0 or later. [CBC-217]

- Reduced the amount of logging from internal CascableCore processes.


# CascableCore 6.2

### New Features

- Added `-fetchEXIFMetadataWithPreflightBlock:metadataDeliveryBlock:` and `-fetchEXIFMetadataWithPreflightBlock:metadataDeliveryBlock:deliveryQueue:` to `id <CBLFileSystemItem>`, allowing clients to quickly load EXIF-style metadata without having to transfer the whole image. [CBC-205]

- Added `CBLStorageSlot` and the `slot` property to `id <CBLFileStorage>`. [CBC-209]

- Added `fileNameHint` to `id <CBLCameraShotPreviewDelivery>`. On cameras that support it, the source image filename will be provided. [CBC-204]

- Added `rating` to `id <CBLFileSystemItem>`. Canon EOS cameras will populate this value with the on-camera image rating. [CBC-206]

- Verified compatibility with Nikon SnapBridge cameras that recently had their Bluetooth limit removed. This includes the D500, D5600, D7500 and D850. [CBC-212]

### Bug Fixes

- Fixed image previews failing to load from JPEG images stored on Olympus cameras. [CBC-208]

- Renamed a internally-used third-party dependency to avoid Objective-C namespace clashing when a linked client happens to use the same dependency. [CBC-207]

- Thumbnails from Nikon cameras are now rotated correctly. [CBC-213]

- Improved the reliability of loading shot previews when working with a dual-slot Nikon camera that's set to put RAW and JPEG images on different cards. [CBC-146]

- Fixed a bug that would cause EOS M and some low-end EOS Rebel cameras to get stuck with autofocus active if `engageShutter:` was called without first calling `engageAutoFocus:`. [CBC-210]

- Fixed a bug that would cause Fujifilm cameras with a trailing hyphen in their SSID to not be discovered correctly. [CBC-202]

- Fixed a crash that could occur when Panasonic LUMIX cameras delivered invalid live view frames. [CBC-215]


# CascableCore 6.1.1

### Other Changes

- CascableCore is now compiled with Swift 5.

### Bug Fixes

- New images added to the same storage card when shooting RAW+JPEG will no longer incorrectly share metadata on Canon cameras. [CBC-199]


# CascableCore 6.1

### New Features

Added support for the Nikon Z series of cameras (the Z6 and Z7) in "Connect to Smartphone" mode.

API ramifications are as follows:

- Added `CBLDriveModeNikonHighSpeedExtendedContinuousShooting` to the `CBLDriveMode` enum.
- Added `CBLWhiteBalanceAutomaticNaturalLight` to the `CBLWhiteBalance` enum.
- Added `CBLImageQualityNikonJPEGFineHighQuality`, `CBLImageQualityNikonJPEGNormalHighQuality`, `CBLImageQualityNikonJPEGBasicHighQuality`, and `CBLImageQualityTIFF` to the `CBLImageQuality` enum.
- Added `CBLAutoExposureModeNikonUser3` to the `CBLAutoExposureMode` enum.

### Other New Features

- Significantly reduced the time it takes to connect to Nikon cameras. [CBC-123]

### Bug Fixes

- Image quality settings are now correctly represented on all Nikon cameras.

- Nikon cameras in "PC Mode" are no longer incorrectly discovered as Canon cameras (connections to which would subsequently fail).

- The removed support for `CBLLiveViewOptionFavorHighFrameRate` from the 7D Mark II. 


# CascableCore 6.0.2

### Bug Fixes

- Fixed certain Canon cameras powering down due to inactivity when live view is inactive and the camera isn't being used. [CBC-194]

- Fixed a regression in 6.0.0 that would cause `engageFocus:` to not engage focus on Canon cameras set to back-button focusing, and would cause the shutter not to be released correctly on lower-end Canon cameras when performing bulb exposures. [CBC-195]

- Fixed a rare crash when parsing event packets from Canon cameras. [CBC-196]

- Fixed a crash when disconnecting from a PowerShot, IXUS or ELPH camera with a `nil` callback. [CBC-197]


# CascableCore 6.0.1

### Bug Fixes

- Fixed a crash that could occur when connecting to Fujifilm cameras. [CBC-192]

- Fixed live view for the Canon EOS 70D failing when `CBLLiveViewOptionFavorHighFrameRate` is specified. [CBC-193]


# CascableCore 6.0

### New Features

Added support for WiFi-enabled Canon PowerShot and IXUS/ELPH cameras [CBC-184] , which come in two flavours:

- "Modern" PowerShot cameras (G7X II and newer, SX70 HS and newer, SX730 HS and newer) share the same platform as EOS M cameras and other than not providing focus maniuplation or other odd things, they are fully featured.
    
- "Legacy" PowerShot cameras (everything older) and IXUS/ELPH cameras have their own platform which is a lot more limited. In particular:
    - Some PowerShot cameras don't support remote shooting at *all*, and only allow filesystem access.
    - No RAW images.
    - No simultaneous access to remote control and storage - you must switch modes. 
    - Very limited control - no focus points, no half-press of the shutter, and a very small number of changeable settings (no exposure settings can be changed).
    
CascableCore does not directly expose which platform the camera is running. Instead, use APIs such as `-supportsFunctionality:`, `-supportsCommandCategories:` and so on as with other cameras. 

### Other Changes

- Some Canon cameras (notably EOS M, PowerShot and low-end cameras such as the 1300D) will see increased live view performance.

- More Canon cameras (notably EOS 750D series, EOS 800D series, EOS R) support `CBLLiveViewOptionFavorHighFrameRate`. [CBC-191]

- Calling `engageShutter:` on Canon cameras without first calling `engageAutofocus:` will cause photos to be taken without first triggering autofocus. [CBL-935]

### API Changes

- The values of the `CBLCameraSupportedFunctionality` enum have been renamed to correctly match modern naming guidelines.

- Added `CBLCameraSupportedFunctionalityExposureControl` to the `CBLCameraSupportedFunctionality` enum. Several PowerShot cameras only provide live view and shot taking when remote controlling - no exposure settings can be changed. Those cameras won't provide `CBLCameraSupportedFunctionalityExposureControl`, while the rest will.

- Added `CBLCameraSupportedFunctionalityShotPreview` to the `CBLCameraSupportedFunctionality` enum. Only cameras that support this flag will trigger shot preview callbacks.

- Added the `requestInProgress` to `id <CBLCameraShotPreviewDelivery>`. If a shot preview is being loaded, this property will return `YES`.

- Added `+dateFromExifDateString:` to `CBLExifHelpers`.

- Added `+cropMetadatalessThumbnail:basedOnMetadata:` and `+cropMetadatalessThumbnail:toPreRotationRatio:` to `CBLImageManipulationHelpers`.

- Added `+metadataInJPEGHeader:` to `CBLRAWImageDescription`.

- Removed `CBLCameraLCDEVFFunctionality` and `CBLCameraSmartPhoneEVFFunctionality`, since they were internal flags only used by the Canon subsystem.


# CascableCore 5.2.8

### Bug Fixes

- Fixed an issue that would cause client-initiated shots to not deliver shot preview callbacks on Sony cameras when the shutter speed was slower than around 10 seconds. [CBC-186]

- Fixed an issue that would cause EOS Rebel (i.e., cameras not sold in the EU) cameras to behave incorrectly regarding live view. [CBC-189]


# CascableCore 5.2.7

### Additions

- Added support for the Fuji X-T3. [CBC-181]


# CascableCore 5.2.6

### Additions

- Added support for the Canon EOS R. [CBC-179]

- Added the following new `CBLAFSystem` values: `CBLAFSystemZone`, `CBLAFSystemCanonExpandPlus`, `CBLAFSystemCanonExpandAround`, `CBLAFSystemCanonLargeZoneHorizontal`, and `CBLAFSystemCanonLargeZoneVertical`.

- Added the following new `CBLAutoExposureMode` value: `CBLAutoExposureModeCanonFlexiblePriorityAuto`.

### Bug Fixes

- Fixed a bug that would cause observers for valid settable values (i.e., those added with `observeValidSettableValuesForProperty:withBlock:`) to not fire for Canon cameras. [CBC-180]


# CascableCore 5.2.5

### Bug Fixes

- Fixed a crash that could occur when encountering Fuji cameras that aren't yet officially supported. [CBC-178]


# CascableCore 5.2.4

### Changes

- CascableCore is now built using Swift 4.2 (it was previously Swift 3). This should have no outwards-facing changes.

- Halved the chunk delivery size when streaming images from Canon cameras. [CBC-175]

### Bug Fixes

- Fixed a rare crash the could occur in the Olympus subsystem. [CBC-157]

- Fixed a crash that occurred when encountering a damaged failsystem item on Canon cameras. [CBC-174]

- Fixed a crash that occured when starting live view on a Sony camera that claims to support live view sizing but provides no sizes. [CBC-158]


# CascableCore 5.2.3

- Replaced an internal class, `CBLPTPIPQueue`, with a modern re-implementation. This class is the very core of all communications with PTPIP-based cameras - all Canon, Fujifilm, and Nikon models, and has been around for man years. However, it was the cause of several very rare and hard to reproduce crashes, so the decision was made to re-write it. [CBC-120, CBC-167]


# CascableCore 5.2.2

### Additions

- Sony cameras will now trigger shot preview callbacks when the shot is taken using the on-body shutter button. [CBC-168]

- Added support for the Panasonic LUMIX G9. [CBC-171]

### Bug Fixes

- Fixed a bug that would cause Live View to fail on Canon EOS 2000D and 4000D series models. [CBC-170]

- Fixed a bug that would cause Live View to fail on the Canon EOS 70D when `CBLLiveViewOptionFavorHighFrameRate` is set to `@YES`.

- Fixed a bug that would cause the value of `CBLPropertyIdentifierAperture` to return odd values on some Canon models when in automatic exposure modes. An "automatic" aperture value will be returned instead. [CBC-169]


# CascableCore 5.2.1

### Additions

- Added support for the Fujifilm X-H1, and the new film simulation mode it has (exposed as `CBLColorToneFlatVideo`). [CBC-164]

- Added support for the new Bleach Bypass colour tone (`CBLColorToneBleachBypass`) and art filter (`CBLArtFilterBleachBypass`) added to newer Olympus cameras. [CBC-140]

- The Canon EOS M50 now supports the live view orientation (`CBLCameraOrientationFunctionality`) and clock update (`CBLCameraUpdateClockFunctionality`) functionalities. [CBC-166]

### Bug Fixes

- Fixed a bug that would cause Olympus cameras to occasionally deliver invalid live view frames if `CBLLiveViewOptionSkipImageDecoding` is set. [CBC-165]

- Metadata dictionaries from CR3 images now correctly place TIFF metadata into the `kCGImagePropertyTIFFDictionary` sub-dictionary. [CBC-155] 

- Calling `-endLiveViewStream:` and then `-beginLiveViewStreamWithDelivery:…` without switching modes on Fuji cameras no longer causes live view to fail. [CBL-883]


# CascableCore 5.2

### New Features

Added options to live view, allowing the customisation of how live view is streamed. This manifests in two new APIs:

The method `-beginLiveViewStreamWithDelivery:deliveryQueue:options:terminationHandler:` is used to pass options when starting live view. 

The method `-applyLiveViewStreamOptions:` is used to change options when live view is running (where supported).

The following options are currently available: 

- `CBLLiveViewOptionSkipImageDecoding`: When set to `@YES`, live view frames will not decode their image data into `NSImage`/`UIImage` objects. In cases where the client doesn't need these image objects to perform live view processing, this saves a decent amount of CPU resources. The default value for this option is `@NO` (i.e., live view frames will decode their images). [CBC-162]

- `CBLLiveViewOptionFavorHighFrameRate`: When set to `@YES`, CascableCore will attempt to configure live view such that it delivers smaller or lower quality images during live view in order to achieve a higher framerate. This is only supported on Nikon, some Canon, and some Sony cameras. On other cameras, this option has no effect. The default value for this option is `@NO` (i.e., live view will be in the highest quality available). [CBC-163] 

### Other Additions

- CascableCore can now correctly parse CR3 files as produced by new Canon cameras. This means that thumbnail and preview fetching APIs will return correct results, and `-isKnownImageType` with return `YES` for these files. [CBC-155]

- Black bars should no longer appear around the image returned by the thumbnail fetching APIs for JPEG and CR2 images on Canon cameras. [CBC-155]

- `CBLCameraLiveViewFrame.h` now has nullability attributes. [CBC-162]

- Added `-rawImagePixelSize` to `id <CBLCameraLiveViewFrame>` objects. [CBC-162]

- Added `-rawImageCropRect` to `id <CBLCameraLiveViewFrame>` objects. [CBC-162]

- Added support for the newest firmware updates from Panasonic (GH-5 2.3+, etc). [CBC-160]

### Bug Fixes

- Fixed a bug where the valid settable values result for `CBLPropertyIdentifierAperture` would return a long list of garbage values for Panasonic cameras without a lens attached. [CBC-161]

- Live view will now work correctly with EOS M50 cameras. [CBC-140]


# CascableCore 5.1.2

### Additions

- Added support for early 2018 Canon cameras: EOS M50, EOS T7/2000D/1500D, EOS T10/4000D/3000D, and EOS SL2/200D/Kiss X9. CR3 support for the EOS M50 will be added in a future update. [CBC-140]

### Bug Fixes

- Camera discovery no longer excessively logs to the console.


# CascableCore 5.1.1

### Bug Fixes

- Fixed an issue that could cause unbound memory usage on Fujifilm and Panasonic cameras. [CBC-150]


# CascableCore 5.1

### Support for Sony a7R III, a9, etc

CascableCore now supports newer Sony cameras that don't support the "Smart Remote Control" on-camera app, including the a7R III, a9, etc. Unfortunately, these cameras are missing a number of properties compared to other Sony cameras and don't support access to the camera's storage. [CBC-145]


### Support for decoding camera-generated QR codes.

The new `CBLCameraQRDecoding` class contains logic for decoding the strings contained in Sony, Olympus and Panasonic QR codes. [CBL-862]


### Bug Fixes

- Improvements to `CBLCameraDiscovery` to improve reliability. [CBC-142]

- Fixed an issue that could cause Shot Preview deliveries to fail on Canon cameras with multiple in-use storage slots. [CBC-146]

- Fixed an issue that would cause `validSettableValuesForProperty:` to incorrectly return no valid values for `CBLPropertyIdentifierAperture` on Fuji cameras. [CBC-143]

- Internal work to live view streaming in Fuji cameras to try to prevent a memory corruption issues in certain conditions. [CBC-138]


# CascableCore 5.0.2

### Bug Fixes

- Fixed an issue that would cause Fuji cameras to freeze when switching from `CBLCameraAvailableCommandCategoryFilesystemAccess` to `CBLCameraAvailableCommandCategoryRemoteShooting` when live view was never enabled in the previous `CBLCameraAvailableCommandCategoryRemoteShooting`  period. [CBC-144]


# CascableCore 5.0.1

### Bug Fixes

- Fixed an issue that could cause Nikon cameras to deliver `nil` frames to the live view frame delivery callback. [CBC-141]


# CascableCore 5.0

### New Live View API

The API for working with Live View has changed for all cameras. The new API is designed to allow greater flexibility and better behaviour when processing live view image frames, particularly in situations where the camera is delivering frames faster than your image processing pipeline can deal with them. [CBC-115]

The new API will provide live view frames on the queue you pass, allowing you to process frames on background queue. The supplied completion callback signals that you're ready for the next frame, and can be called from any queue — you can process the frames in the background, render them on the main queue, then call the completion handler to get the next frame.

The new API also removes `CBLCameraLiveViewUpdateFrequency` and the `liveViewUpdateFrequency` property, which only had an effect on Canon and Nikon cameras. If you wish to throttle live view frames for performance reasons, you can simply defer calling a frame delivery's completion handler. This works for all cameras, and allows you to tailor the frame rate for your application.

To start live view, make sure the camera has the `CBLCameraAvailableCommandCategoryRemoteShooting` command category available, then enable as so:

```
CBLCameraLiveViewFrameDelivery delivery = ^(id<CBLCameraLiveViewFrame> frame, dispatch_block_t completionHandler) {
    // This will be called for each frame being delivered.
    [self processAndDisplayFrame:frame];

    // The completion handler *must* be called in order to get the next frame.
    completionHandler();
};

[self.camera beginLiveViewStreamWithDelivery:delivery
                               deliveryQueue:dispatch_get_main_queue()
                          terminationHandler:^(CBLCameraLiveViewTerminationReason reason, NSError *error) {

    // This will be called when live view ends either normally or because of an error.
    if (reason == CBLCameraLiveViewTerminationReasonFailed) {
        [self displayLiveViewFailedDialogWithError:error];
    }
}];
```

To end live view:

```
// This will cause the termination handler given to beginLiveViewStream… to be called with the termination
// reason of CBLCameraLiveViewTerminationReasonEndedNormally.
[self.camera endLiveViewStream];
```


### Direct Focus Manipulation

Added `driveFocusByAmount:inDirection:completionCallback:` to `id <CBLCamera>`. Requires the `CBLCameraDirectFocusManipulationFunctionality` functionality flag, which is currently only available on Canon and Nikon cameras due to protocol limitations on the other manufacturers. [CBC-136]

Using `driveFocusByAmount:inDirection:completionCallback:` allows you to move the focus point of the connected lens towards the camera or towards infinity by a small, medium, or large amount. This API requires that live view is active, and that the camera's focus mode is NOT set to MF.

When triggering the shutter after using this API, ensure you don't trigger autofocus to undo the user's work.


### Power Off On Disconnect

Added `disconnectWithFlags:completionCallback:callbackQueue:` to `id <CBLCamera>`. If you pass the flag `CBLDisconnectionFlagPowerOffCamera` set to `YES` and the camera supports the functionality `CBLCameraPowerOffOnDisconnectFunctionality`, the camera will power down as part of the disconnection procedure. [CBC-1]

`CBLDisconnectionFlagPowerOffCamera` is currently only supported on Olympus cameras.


### Other Additions

 Fujifilm, Olympus, and Panasonic cameras now all support `CBLCameraHalfShutterPressFunctionality`, and you can call `engageAutoFocus:` and `disengageAutoFocus:` on them. For cameras that don't support "half press shutter" commands, `CascableCore` will fall back to using `touchAFAtPoint:callback:` with either the last point passed to `touchAFAtPoint:callback:`, or the centre of the frame. [CBC-49]

If you were previously checking for `CBLCameraHalfShutterPressFunctionality` and either performing `engageAutoFocus:` or `touchAFAtPoint:callback:` depending on the result, you should now be able to remove that check and exclusively use `engageAutoFocus:`/`disengageAutoFocus:`  unless you have a particular point you wish to focus on.


### Bug Fixes

New instances of `id <CBLPropertyProxy>` no longer return `nil` for the `localizedDisplayValue` property for certain property identifiers on Fujifilm and Panasonic cameras. [CBC-137]

Sony cameras no longer permanently set their `storageDevices` property to `nil` when encountering a timeout or other transient error when switching to `CBLCameraAvailableCommandCategoryFilesystemAccess`. Additionally, timeouts for these switches have been increased. [CBC-133]


# CascableCore 4.2.1

### Changes

- Moved `StopKit` to an external dependency.


# CascableCore 4.2

### Licensing Changes

CascableCore licenses are no longer baked into your binary. Instead, CascableCore releases can be downloaded from the [CascableCore Binaries](https://github.com/Cascable/cascablecore-binaries) repo on GitHub, and your license is applied at runtime. You can download your license from the [Cascable Developer Portal](https://developer.cascable.se/).

### Bug Fixes

- Extra hardening against a rare crash related to cameras that use PTP. [CBC-110]


# CascableCore 4.1.2

### Additions

Added a new notification: `CBLWiFiConnectivityDidChangeNotificationName`, which will always be delivered on the main queue. This notification will be posted when device WiFi reachability changes (like the standard reachability code supplied by Apple), but also when the device changes WiFi networks without triggering a reachability change - for example, when a camera is turned off and the device falls back to another available network.

### Bug Fixes

- Fixed a crash caused by Reachability. [CBC-129, CBC-131]

- Fixes for various reported crashes. [CBC-130, CBC-127, CBC-126, CBC-122, CBC-121, CBC-119, CBC-113, CBC-112, CBC-111, CBC-110]


# CascableCore 4.1.1

### Bug Fixes

- Explicitly support the Canon EOS M100 (no real code changes from 4.1.0). [CBC-113]

- Fixed a minor model name parsing issue with the Olympus E-M10 III. [CBC-116]


# CascableCore 4.1.0

### Additions

Added a new functionality flag: `CBLCameraLimitedRemoteControlWithoutLiveViewFunctionality`, which is currently only used for the Canon EOS 1300D. Cameras that contain this functionality flag will only guarantee that they are able to take "simple" shots while live view is disabled. [CBC-100]

Cameras that use this flag have *some* control functionality while live view is disabled, but not enough for them to be considered by CascableCore as fully controllable. In the case of the 1300D:

- `engageAutoFocus:` and `disengageAutoFocus:` will throw errors.
- Bulb exposures are not supported.
- Values for some properties may become read-only.

Cameras may change the values of their `supportedFunctionality` properties when live view is disabled to reflect this reduced functionality state. It's important to react accordingly for the best user experience — apps may, for example, remove autofocus UI from view when cameras remove their `CBLCameraHalfShutterPressFunctionality` functionality flag when live view is disabled.

### Bug Fixes

- Fixed a number of crashes triggered when parsing malformed data. [CBC-106, CBC-105, CBC-104]

- Sony cameras will no longer appear multiple times in the `cameras` property of `CBLCameraDiscovery`. [CBC-108]

- CascableCore will now correctly fail to connect (with error code `CBLErrorCodeCameraNeedsSoftwareUpdate`) to newer Sony cameras that don't have Smart Remote Control installed. Previously, the connection would succeed but live view would fail to start. [CBC-109]


# CascableCore 4.0.2

### Bug Fixes

- Improvements to the internal class `CBLPTPIPQueue` to reduce crashes. [CBC-101]


# CascableCore 4.0.1

### Bug Fixes

- Shot previews no longer require storage folders to be loaded to fire correctly on Canon and Nikon cameras. [CBL-677]

- `-invokeOneShotShutterExplicitlyEngagingAutoFocus:completionCallback:` now works correctly when passing `YES` to the `triggerAutoFocus` parameter. [CBC-96]

- Fixed a connection failure that would occur when the `CBLConnectionFlagSyncCameraClockToSystemClock` connection flag was set to `YES` on a small number of Canon cameras (mainly EOS M models). [CBC-95]


# CascableCore 4.0

### API Changes

- Added a `clientName` parameter to `id <CBLCamera>`'s connection method:
    - `-connectWithClientName:completionCallback:userInterventionCallback:`

- Added an optional `connectionFlags:` parameter to `id <CBLCamera>`'s connection method. You can pass the value `@YES` for the `CBLConnectionFlagSyncCameraClockToSystemClock` key to have CascableCore attempt to sync the camera's clock to the system clock on connection.
    -  `-connectWithClientName:connectionFlags:completionCallback:userInterventionCallback:`

- Added `CBLCameraConnectionWarningCategoryMisc`, `CBLCameraConnectionWarningTypeClockSyncFailed`, and `CBLCameraConnectionWarningTypeClockSyncNotSupported` values to the connection warning system. If you pass the value `@YES` for the `CBLConnectionFlagSyncCameraClockToSystemClock` connection flag and the camera doesn't support camera clock sync, or does but fails to do so, a connection warning will be generated with these values.

- Renamed properties on `id <CBLCameraDiscoveryService>` to bring them in line with `id <CBLDeviceInfo>`:
    - `modelName` is now `model`.
    - `cameraSerialNumber` is now `serialNumber`.

- `CBLPropertyProxy` is now a protocol (`id <CBLPropertyProxy>`) instead of an empty base class.

- Added the following values to `CBLAFSytem`:
    - `CBLAFSystemSinglePoint`
    - `CBLAFSystemSinglePointTracking`
    - `CBLAFSystemPanasonicCustomMultipleAreas`

- Added the following values to `CBLFocusMode`: 
    - `CBLFocusModeSingleAFWithRefocusing`

- Added the following values to `CBLWhiteBalance`:
    - `CBLWhiteBalanceCustom4`

- Replaced the Sony-specific fluorescent white balance in favour of generic equivalents:
    - `CBLWhiteBalanceSonyFluorescentWarm` -> `CBLWhiteBalanceFluorescentWarm`
    - `CBLWhiteBalanceSonyFluorescentWhite`, -> `CBLWhiteBalanceFluorescentWhite`
    - `CBLWhiteBalanceSonyFluorescentDaylight ` -> `CBLWhiteBalanceFluorescentDaylight`

- Added the following values to `CBLColorTone`:
    - `CBLColorToneNone`
    - `CBLColorToneSepia`
    - `CBLColorToneSoftPortrait`
    - `CBLColorToneMonotoneYellowFilter`
    - `CBLColorToneMonotoneRedFilter`
    - `CBLColorToneMonotoneGreenFilter`
    - `CBLColorToneFujiClassicChrome`

- Added `CBLExifHelpers` and `CBLImageManipulationHelpers`.

- Added `+[CBLNetworkConfigurationHelper ssidOfInterface:]`.

- `CBLPropertyIdentifierEVFOutputDevice` and `CBLEVFDestination` have been removed. Use the `liveViewEnabled` property on `id <CBLCamera>` to determine live view status.

- `-[id <CBLCamera> setLiveViewEnabled:displayOnDeviceScreen:callback:]` has been renamed to `-[id <CBLCamera> setLiveViewEnabled:callback:]`.

- Added `-[id <CBLCamera> updateClockTo:callback:]` for setting the system clock on supported cameras.

- Added `-[id <CBLCamera> setLiveViewZoomLevel:callback:]` for setting the camera's live view zoom level on supported cameras.

- Added `CBLCameraUpdateClockFunctionality` and `CBLCameraZoomableLiveViewFunctionality` functionality flags.

- Improved some legacy APIs on `id <CBLCameraLiveViewFrame>` and improved documentation on others.

- The filesystem observation API has changed. When adding an observer to an `id <CBLFileStorage>` object, a token is returned. That token is then used to remove the observer with the new `-removeFileSystemObserverWithToken:` method. `-removeFileSystemObserver:` has been removed. 

- Observation of camera properties and valid settable values has changed in the same way as filesystem observation.

- Observation of shot previews has changed in the same way as filesystem observation.

- Added `removalRemovesPairedItems` to `id <CBLFileSystemItem>`. If this property returns `YES`, deleting the filesystem item may have other side effects, such as deleting the other half of a RAW+JPEG pair.

- Added `hasInaccessibleImages` to `id <CBLFileSystemItem>`. If this property returns `YES`, the storage item contains images that are inaccessible to CascableCore. For example, some older Panasonic models list RAW files but can't transfer them. CascableCore ignores these items and sets this property to `YES`.

- Added `+automaticAperture` to `CBLApertureValue`. This operates the same as automatic shutter speeds, in that you can't perform stop maths on these values.

# CascableCore 3.2.6

- Fixed a bug that would cause CascableCore to not correctly detect Sony cameras where the device name was changed from the default.

# CascableCore 3.2.5

- Added support for the Canon EOS 77D, EOS 800D and EOS M6. [CBC-64]

*Note:* As of this version the Sony RX100 V, Sony RX10 III and a6500 are supported. However, no code changes were needed.

# CascableCore 3.2.4

- Fixed a bug that would cause an invalid live view orientation to be reported on Canon cameras that don't supply this information. The orientation is new reported as landscape. [CBL-731]

# CascableCore 3.2.3

- Added support for the Canon EOS 1DX II. [CBC-28]

# CascableCore 3.2.2

- `-[id <CBLCamera> friendlyDisplayName]` will no return an empty string on some Canon models.

- `-[id <CBLCamera> supportedFunctionality]` will return the correct values for the Canon EOS 5D Mark III.

This release makes the 5D Mark III + WFT-E7 a supported camera.

# CascableCore 3.2.1

- Fixed crash that would occur when encountering an Olympus thumbnail image that was both invalid and in an orientation other than upright landscape. 

- CascableCore should no longer detect Sony TVs as cameras.


# CascableCore 3.2

- Added support for the Olympus OM-D E-M1 Mark II. [CBC-2, CBC-3]

- `CBLFileStreamChunkDelivery` callbacks are coalesced internally in some cases. [CBC-5] 

The behaviour of file streaming has changed slightly from previous releases. Some cameras deliver chunks of data in small amounts very frequently, which in some circumstances could lead to `CBLFileStreamChunkDelivery` callbacks being delivered at upwards of 100 times per second. From version 3.2, CascableCore enforces a minimum delivery size, which reduces the frequency of delivery callbacks to a manageable level.

Additionally, the behaviour of battery readings for cameras whose `cameraFamily` is `CBLCameraFamilyOlympus` has changed slightly. Previously, the value of the `CBLPropertyIdentifierBatteryLevel` property was `CBLBatteryPowerLevelFull` until a valid battery reading could be taken from the live view event stream. To better reflect reality, the value is now `CBLBatteryPowerLevelUnknown` until a battery reading is taken.


# CascableCore 3.1

### New Features

- Added `CBLRAWImageDescription`, a helper class for parsing the headers of RAW files, including extracting the JPEG previews from such files.

- Added `CBLImageMetadataWritingHelpers`, a helper class for writing metadata into image files.


# CascableCore 3.0.1

### Bug Fixes

- Fixed a bug that would cause a crash when using `-[CBLNetworkConfigurationHelper suggestedInterfaceForCameraCommunication]` on Mac machines that contain network interfaces with BSD names longer than 9 characters.


# CascableCore 3.0

### New Features

- Complete audit on all public APIs for use in Swift projects, including nullability annotations, naming changes, and the removal of the CBL prefix as per Swift naming guidelines. As a result of this, breaking changes were made to the API in both Swift and Objective-C which in turn required a new breaking version number.

- Added `CBLNetworkConfigurationHelper` to the public API, allowing client applications to perform network interface work with the same logic as CascableCore.

- Added support for the Canon EOS 7D Mark II, the Canon EOS 5DS and 5DSR, and the Canon EOS 5D Mark IV.

### Behaviour Changes

- Olympus cameras with "Mark" in the official name (such as the Olympus E-M5 Mark II) have more friendly display names. In this instance, "E-M5MarkII" becomes "E-M5 II".

### Bug Fixes

- CascableCore will no longer unnecessarily output to the console log when connecting to Olympus cameras.


# CascableCore 2.1
### New Features

Added two new properties: `CBLPropertyIdentifierLightMeterReading` and `CBLPropertyIdentifierLightMeterStatus`, which are supported on all camera families except Sony. 

- `CBLPropertyIdentifierLightMeterReading`  returns values of type `CBLExposureCompensation`. It is read-only.

- `CBLPropertyIdentifierLightMeterStatus` returns values of the new type `CBLLightMeterStatus`. It is also read-only.

Use these properties together to implement a light meter, which is useful when cameras are being used in manual exposure mode. Indeed,  typically the light meter is only active when the camera is set to `CBLAutoExposureModeManual` or `CBLAutoExposureModeBulbManual`.

Cameras don't always have their light meters active. When the value of `CBLPropertyIdentifierLightMeterStatus` is `CBLLightMeterStatusNotInUse`, the value for `CBLPropertyIdentifierLightMeterReading` is undefined and should not be used. When the value is `CBLLightMeterStatusReadingBeyondBounds`, the current exposure settings are so far away from a 'normal' exposure that the light meter cannot accurately give a reading. In this case, the camera itself will typically blink the light meter to show that it's invalid. In this case, you should hide your UI, or blink it, or otherwise inform the user of the situation.

### Behaviour Changes

- Canon, Nikon: When calling `-loadChildren` on an instance of `id <CBLFileSystemFolderItem>` that has already been loaded, the library will no longer create new instances for children that existed before the method was called, resusing the previous instances instead.

### Bug Fixes

- Olympus: Fixed a problem in which `validSettableValues` for exposure properties could be missing values when the drive mode is set to Manual.

- Canon: Fixed a problem in which the camera's `autoexposureResult` could be missing values.

- All: Improved the reliability of shot preview, particularly when multiple shots are taken in a short amount of time.

- All: Improved the reliability of camera discovery, particularly on iOS between app suspensions and on iOS 10.
