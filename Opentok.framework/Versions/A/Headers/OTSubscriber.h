//
//  OTSubscriber.h
//  opentok-ios-sdk
//
//  Created by Charley Robinson on 10/24/11.
//  Copyright (c) 2011 Tokbox, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Opentok.h"

@protocol OTSubscriberDelegate;

/**
 * An OTSubscriber (subscriber) object rasterizes media data bound to an <OTStream>.
 * The subscriber object references a stream that you have subscribed to.
 * The subscriber object includes methods that let you disable and enable
 * local audio and video playback for the subscribed stream.
 */

@interface OTSubscriber : NSObject 

/** @name Getting basic information about a Subscriber */

/**
 * The <OTSession> object that owns this subscriber. An instance will have
 * one and only one <OTSession> associated with it, and this property
 * is immutable.
 */
@property(nonatomic, readonly) OTSession* session;

/**
 * The stream this subscriber is bound to. Any media channels
 * on the stream should be available for display/playback with
 * this instance.
 */
@property(nonatomic, readonly) OTStream* stream;

/**
 * The view containing a playback buffer for associated video data. Add this
 * view to your view heirarchy to display a video
 * stream.
 */
@property(nonatomic, readonly) OTVideoView* view;

/**
 * The <OTSubscriberDelegate> object that serves as a delegate,
 * handling events for this OTSubscriber object.
 */
@property(nonatomic, weak) id<OTSubscriberDelegate> delegate;

/**
 * Whether to subscribe to the stream's audio.
 *
 * The default value is YES.
 *
 * Setting this property has no effect if the <[OTStream hasAudio]> property is set to NO.
 */
@property(nonatomic) BOOL subscribeToAudio;

/**
 * Whether to subscribe to the stream's video. Setting this property only has an affect if you do so immediately
 * after initializing the OTSubscriber object.
 *
 * The default value is YES.
 *
 * Setting this property has no effect if the <[OTStream hasVideo]> property is set to NO.
 */
@property(nonatomic) BOOL subscribeToVideo;

/** @name Initializing a Subscriber */

/**
 * Initializes an OTSubscriber and binds it to an <OTStream> instance.
 * Once initialized, the instance is permanently bound to the stream.
 *
 * The OpenTok iOS SDK supports a limited number of simultaneous audio-video streams in an app:
 *
 * - On iPad 2 and iPad 3, the limit is four streams. An app can have up to four simultaneous subscribers,
 * or one publisher and up to three subscribers.
 * - On all other supported iOS devices, the limit is two streams. An app can have up to two subscribers,
 * or one publisher and one subscriber.
 * 
 * Initializing an OTSubscriber causes it to start streaming data from the OpenTok server, regardless of whether
 * the view of the OTSubscriber object is added to a superview.
 *
 * You can stream audio only (without subscribing to the video stream) by setting the
 * <[OTSubscriber subscribeToVideo]> property to NO immediately after initializing the OTSubscriber object.
 * You can stream video only (without subscribing to the audio stream) by setting the
 * <[OTSubscriber subscribeToAudio]> property to NO immediately after initializing the
 * OTSubscriber object.
 *
 * When the subscriber connects to the stream, the <[OTSubscriberDelegate subscriberDidConnectToStream:]> message
 * is sent to the subscriber delegate. Then, when the first frame of video has been decoded, the
 * <[OTSubscriberDelegate subscriberVideoDataReceived:]> message is sent to the subscriber delegate.
 *
 * If the subscriber fails to connect to the stream, the <[OTSubscriberDelegate subscriber:didFailWithError:]>
 * message is sent to the subscriber delegate.
 *
 * @param stream The <OTStream> object to bind this instance to.
 * @param delegate The delegate (<OTSubscriberDelegate>) that will handle events generated by
 * this instance.
 */
- (id)initWithStream:(OTStream*)stream
            delegate:(id<OTSubscriberDelegate>)delegate;

/** @name Controling audio and video playback */

/**
 * Disconnect the subscriber from the stream and removes
 * the view from its superview.
 */
-(void)close;

@end

/**
 * Used to send messages for an OTSubscriber instance. When you send
 * the <[OTSubscriber initWithStream:delegate:]> message, you specify an
 * OTSubscriberDelegate object.
 */
@protocol OTSubscriberDelegate <NSObject>

/** @name Using subscribers */

/**
 * Sent when the subscriber successfully connects to the stream.
 * @param subscriber The subscriber that generated this event.
 */
- (void)subscriberDidConnectToStream:(OTSubscriber*)subscriber;

/**
 * Sent if the subscriber fails to connect to its stream.
 * @param subscriber The subscriber that generated this event.
 * @param error The error (an <OTError> object) that describes this connection error. The
 * `OTSubscriberErrorCode` enum (defined in the OTError class) defines values for the `code`
 * property of this object.
 */
- (void)subscriber:(OTSubscriber*)subscriber didFailWithError:(OTError*)error;

@optional

/**
 * Sent when the first frame of video has been decoded. Although the
 * subscriber will connect in a relatively short time, video can take
 * more time to synchronize. This message is sent after the
 * <subscriberDidConnectToStream> message is sent.
 * @param subscriber The subscriber that generated this event.
 */
 - (void)subscriberVideoDataReceived:(OTSubscriber*)subscriber;

@end
