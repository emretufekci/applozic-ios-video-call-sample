//
//  TVIConnectOptions.h
//  TwilioVideo
//
//  Copyright © 2016-2017 Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TVILocalAudioTrack;
@class TVILocalVideoTrack;
@class TVIIceOptions;

/**
 *  `TVIConnectOptionsBuilder` is a builder class for `TVIConnectOptions`.
 */
@interface TVIConnectOptionsBuilder : NSObject

/**
 *  @brief A collection of local audio tracks which will be shared in the Room.
 */
@property (nonatomic, copy, nonnull) NSArray<TVILocalAudioTrack *> *audioTracks;

/**
 *  @brief The queue where the Room and associated classes will invoke delegate methods.
 *
 *  @discussion All delegate methods except for `TVIVideoViewDelegate` and `TVICameraCaptureDelegate`
 *  are performed on this queue. Any `TVIRoom` instance which is created with these options will maintain a
 *  strong reference to the queue until it is destroyed.
 *  The default value of `nil` indicates that the main dispatch queue will be used.
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 *  @brief A custom ICE configuration used to connect to a Room.
 */
@property (nonatomic, strong, nullable) TVIIceOptions *iceOptions;

/**
 *  @brief A BOOL which determines if the SDK will attempt to reconnect after returning to the foreground.
 *
 *  @discussion When the Room is in `TVIRoomStateConnected` state, the SDK attempts to reconnect if the app comes to
 *  foreground within a short period of time. If the app does not come to foreground within a short time, SDK triggers
 *  disconnect. If the Room is in `TVIRoomStateConnecting` state before the app goes to background, the SDK will trigger
 *  disconnect.
 *  By default, this behavior is enabled when CallKit is not used. Set this connect options to `NO` to disable it.
 */
@property (nonatomic, assign, getter = shouldReconnectAfterReturningToForeground) BOOL reconnectAfterReturningToForeground;

/**
 *  @brief The name of the Room which you want to connect to.
 *
 *  @discussion You can provide the name of new or existing Room. The default value of `nil` indicates that a new Room will be created.
 */
@property (nonatomic, copy, nullable) NSString *roomName;

/**
 *  @brief A collection of local video tracks which will be shared in the Room.
 */
@property (nonatomic, copy, nonnull) NSArray<TVILocalVideoTrack *> *videoTracks;

/**
 *  @brief You should not initialize `TVIConnectOptionsBuilder` directly, use a TVIConnectOptionsBuilderBlock instead.
 */
- (null_unspecified instancetype)init __attribute__((unavailable("Use a TVIConnectOptionsBuilderBlock instead.")));

@end

/**
 *  CallKit specific additions.
 */
@interface TVIConnectOptionsBuilder (CallKit)

/**
 *  @brief The CallKit identifier for the Room.
 *
 *  @discussion This property allows you to provide your CallKit UUID as part of `TVIConnectOptions`. This is offered
 *  as a convenience if you wish to use `TVIRoom` for CallKit book keeping. The UUID set here will be reflected on any
 *  `TVIRoom` instance created with these options.
 */
@property (nonatomic, strong, nullable) NSUUID *uuid;

@end

/**
 *  `TVIConnectOptionsBuilderBlock` allows you to construct `TVIConnectOptions` using the builder pattern.
 *
 *  @param builder The builder
 */
typedef void (^TVIConnectOptionsBuilderBlock)(TVIConnectOptionsBuilder * _Nonnull builder);

/**
 *  @brief `TVIConnectOptions` represents a custom configuration to use when connecting to a Room.
 *
 *  @discussion This configuration overrides what was provided in `TVIClientOptions`.
 */
@interface TVIConnectOptions : NSObject

/*
 * @bief A JWT access token which will be used to join the Room.
 */
@property (nonatomic, copy, readonly, nonnull) NSString *accessToken;

/**
 *  @brief A collection of local audio tracks which will be shared in the Room.
 */
@property (nonatomic, copy, readonly, nonnull) NSArray<TVILocalAudioTrack *> *audioTracks;

/**
 *  @brief The queue where the Room and associated classes will invoke delegate methods.
 *
 *  @discussion All delegate methods except for `TVIVideoViewDelegate` and `TVICameraCaptureDelegate`
 *  are performed on this queue. Any `TVIRoom` instance which is created with these options will maintain a
 *  strong reference to the queue until it is destroyed.
 *  The default value of `nil` indicates that the main dispatch queue will be used.
 */
@property (nonatomic, strong, readonly, nullable) dispatch_queue_t delegateQueue;

/**
 *  @brief A custom ICE configuration used to connect to a Room.
 */
@property (nonatomic, strong, readonly, nullable) TVIIceOptions *iceOptions;

/**
 *  @brief A BOOL which determines if the SDK will attempt to reconnect after returning to the foreground.
 *
 *  @discussion When the Room is in `TVIRoomStateConnected` state, the SDK attempts to reconnect if the app comes to
 *  foreground within a short period of time. If the app does not come to foreground within a short time, SDK triggers
 *  disconnect. If the Room is in `TVIRoomStateConnecting` state before the app goes to background, the SDK will trigger
 *  disconnect.
 *  By default, this behavior is enabled when CallKit is not used. Set this connect options to `NO` to disable it.
 */
@property (nonatomic, assign, readonly, getter = shouldReconnectAfterReturningToForeground) BOOL reconnectAfterReturningToForeground;

/**
 *  @brief The name of the Room which you want to connect to.
 *
 *  @discussion You can provide the name of new or existing Room. The default value of `nil` indicates that a new Room will be created.
 */
@property (nonatomic, copy, readonly, nullable) NSString *roomName;

/**
 *  @brief A collection of local video tracks which will be shared in the Room.
 */
@property (nonatomic, copy, readonly, nonnull) NSArray<TVILocalVideoTrack *> *videoTracks;

/**
 *  @brief Developers shouldn't initialize this class directly.
 *
 *  @discussion Use the class methods `optionsWithToken:` or `optionsWithToken:block:` instead.
 */
- (null_unspecified instancetype)init __attribute__((unavailable("Use optionsWithToken: or optionsWithToken:block: to create a TVIConnectOptions instance.")));

/**
 *  @brief Creates `TVIConnectOptions` using an access token.
 *
 *  @param token A JWT access token which will be used to join the Room.
 *
 *  @return An instance of `TVIConnectOptions`.
 */
+ (nonnull instancetype)optionsWithToken:(nonnull NSString *)token;

/**
 *  @brief Creates an instance of `TVIConnectOptions` using an access token and a builder block.
 *
 *  @param token A JWT access token which will be used to join the Room.
 *  @param block The builder block which will be used to configure the `TVIConnectOptions` instance.
 *
 *  @return An instance of `TVIConnectOptions`.
 */
+ (nonnull instancetype)optionsWithToken:(nonnull NSString *)token
                                   block:(nonnull TVIConnectOptionsBuilderBlock)block;

@end

/**
 *  CallKit specific additions.
 */
@interface TVIConnectOptions (CallKit)

/**
 *  @brief The CallKit identifier for the Room.
 *
 *  @discussion This property allows you to provide your CallKit UUID as part of `TVIConnectOptions`. This is offered 
 *  as a convenience if you wish to use `TVIRoom` for CallKit book keeping. The UUID set here will be reflected on any 
 *  `TVIRoom` instance created with these options.
 */
@property (nonatomic, strong, readonly, nullable) NSUUID *uuid;

@end
