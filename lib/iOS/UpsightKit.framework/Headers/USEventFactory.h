//
//  USEventFactory.h
//  UpsightAnalytics
//
//  Created by Anton Fedorchenko on 5/18/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol USDataBundle;

@class USAnalyticsEvent;
@class USDataCollectionEvent;
@class USUnrenderedContentEvent;
@class USMilestoneEvent;
@class USInstallEvent;
@class USInAppPurchaseEvent;
@class USInAppPurchaseInfo;
@class USDynamicEvent;
@class USMonetizationEvent;
@class USMonetizationPurchaseInfo;
@class USConfigurationRequest;
@class USSessionStartEvent;
@class USSessionPauseEvent;
@class USSessionResumeEvent;
@class USPushReceivedEvent;
@class USPushRegistrationEvent;
@class USPushUnregistrationEvent;
@class USUXMEnumerateEvent;

/** A factory for Upsight events. Created events should be sent to Upsight server by calling
<[USAnalyticsInterface record:]>.
*/
@interface USEventFactory : NSObject
/** Creates an analytics event with the given name. You can provide any additional data you'd like to send as a dictionary of key->value pairs.

@param aName A publisher-defined string representing the event name.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USAnalyticsEvent *)analyticsEventWithName:(NSString *)aName pubData:(NSDictionary *)aPubData;

/** Creates an event containing data collected from the user.

@param aBundle A bundle with user data.
@param aStreamID A unique identifer provided by the server. This identifier is applied to all the events related to a single piece of content.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USDataCollectionEvent *)dataCollectionEventWitDataBundle:(id<USDataBundle>)aBundle streamID:(NSString *)aStreamID pubData:(NSDictionary *)aPubData;

/** Events of this kind indicate to the server that it told the SDK to display content, but it had not previously provided the SDK with that content.

@param aContentID Unique identifier of the content. This value is a random server generated string.
@param aCampaignID Identifies the campaign to which this content belongs. Contains targeting, metadata and bid information.
@param aScope Describes the point in the application which has been reached.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USUnrenderedContentEvent *)unrenderedContentEventWithContentID:(NSNumber *)aContentID
                                                       campaignID:(NSNumber *)aCampaignID
                                                            scope:(NSString *)aScope
                                                          pubData:(NSDictionary *)aPubData;

/** Creates an event to indicate that a specific point in the application has been reached. This may represent an action taken or progress made by the user, a particular line/region of code, or any other point of interest.

@param aScope Describes the point in the application which has been reached.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USMilestoneEvent *)milestoneEventForScope:(NSString *)aScope pubData:(NSDictionary *)aPubData;

/** Creates an event to mark the installation of the application.

@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USInstallEvent *)installEventWithPubData:(NSDictionary *)aPubData;

/** Creates an event that represents the purchase of virtual goods through an In App Purchase.

@param anInfo An object containing information about the purchase. Refer to the <USInAppPurchaseInfo>
class for more details.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USInAppPurchaseEvent *)inAppPurchaseEventWithIAPInfo:(USInAppPurchaseInfo *)anInfo pubData:(NSDictionary *)aPubData;

/** Creates an event whose properties are populated from a given event dictionary.

@param anEventDictionary A dictionary containing event properties, including type, upsight
data, pub data and a set of device identifiers that should be sent along with the event.
Here is an example of a dictionary with the `upsight.content.view` event:

    {
        "type": "upsight.content.view",
        "upsight_data": {
            "stream_start_ts": 1448379411,
            "scope": "rewcl",
            "content_id": 1252504,
            "stream_id": "d720da64364b4f70ab7d45a14d7f50dc"
        }
    }

*/
+ (USDynamicEvent *)dynamicEventWithEventDictionary:(NSDictionary *)anEventDictionary;

/** Creates an event that represents a monetary transaction, in which the user is paying the
app developer for goods or services.

@param anInfo An object containing information about the monetary transaction. Refer to the
<USMonetizationPurchaceInfo> class for more details.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USMonetizationEvent *)monetizationEventWithInfo:(USMonetizationPurchaseInfo *)anInfo pubData:(NSDictionary *)aPubData;

/** Creates an event indicating that the SDK configuration has expired.

@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USConfigurationRequest *)configurationRequestWithPubData:(NSDictionary *)aPubData;

/** Creates an event indicating that a new session has started.

The life-cycle of a session consists of three basic states, started, resumed and paused. When
the application starts for the first time a new session starts and `upsight.session.start`
event is sent to the server. When the application resigns its active status, the session transitions
to the paused state and `upsight.session.pause` is sent to the server. If the application resumes
its active status, or gets completely relaunched within a predefined session gap interval,
the session is resumed and `upsight.session.resume` event is sent to the server, otherwise if
the application becomes active past the session gap, a new session starts and `upsight.session.start`
gets sent.

When the application is launched as a result of an incoming push notification, it is always
followed with a new session start.

@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USSessionStartEvent *)sessionStartEventWithPubData:(NSDictionary *)aPubData;

/** Creates an event that indicates the application has been sent to the background.

The life-cycle of a session consists of three basic states, started, resumed and paused. When
the application starts for the first time a new session starts and `upsight.session.start`
event is sent to the server. When the application resigns its active status, the session transitions
to the paused state and `upsight.session.pause` is sent to the server. If the application resumes
its active status, or gets completely relaunched within a predefined session gap interval,
the session is resumed and `upsight.session.resume` event is sent to the server, otherwise if
the application becomes active past the session gap, a new session starts and `upsight.session.start`
gets sent.

When the application is launched as a result of an incoming push notification, it is always
followed with a new session start.

@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USSessionPauseEvent *)sessionPauseEventWithPubData:(NSDictionary *)aPubData;

/** Creates an event indicating that an existing session has been resumed.

The life-cycle of a session consists of three basic states, started, resumed and paused. When
the application starts for the first time a new session starts and `upsight.session.start`
event is sent to the server. When the application resigns its active status, the session transitions
to the paused state and `upsight.session.pause` is sent to the server. If the application resumes
its active status, or gets completely relaunched within a predefined session gap interval,
the session is resumed and `upsight.session.resume` event is sent to the server, otherwise if
the application becomes active past the session gap, a new session starts and `upsight.session.start`
gets sent.

When the application is launched as a result of an incoming push notification, it is always
followed with a new session start.

@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USSessionResumeEvent *)sessionResumeEventWithPubData:(NSDictionary *)aPubData;

#if !TARGET_OS_TV

/** Creates an event indicating that a push notification has been received.

@param aMessageID A unique identifier for this push notification.
@param aCampaignID If the push notification was sent as part of a campaign, the identifier for the campaign.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USPushReceivedEvent *)pushReceivedEventWithMessageID:(NSNumber *)aMessageID campaignID:(NSNumber *)aCampaignID pubData:(NSDictionary *)aPubData;

/** Creates an event that is used to register a device token to be able to send push notifications
from Upsight server.

@param aToken This is the APNS-generated push token passed to <[UIApplicationDelegate application:didRegisterForRemoteNotificationsWithDeviceToken:]>.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USPushRegistrationEvent *)pushRegistrationEventWithToken:(NSString *)aToken pubData:(NSDictionary *)aPubData;

/** Creates an event that is used to unregister from receiving push notifications.

@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USPushUnregistrationEvent *)pushUnregistrationEventWithPubData:(NSDictionary *)aPubData;

#endif

/** Creates an event that the SDK emits to send the UXM schema to the server.

@param aSchema An array containing description of UXM values defined in the application.
@param aPubData A dictionary with additional data provided by the publisher.
*/
+ (USUXMEnumerateEvent *)UXMEnumerateEventWithUXMSchema:(NSArray *)aSchema pubData:(NSDictionary *)aPubData;
@end
