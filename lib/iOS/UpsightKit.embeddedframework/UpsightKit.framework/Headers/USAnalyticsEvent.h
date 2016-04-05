//
//  USAnalyticsEvent.h
//  Upsight
//
//  Created by Anton Fedorchenko on 6/27/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USEvent.h"

/** Type identifying storable objects of <USAnalyticsEvent> class. It is the same type as returned
by <[USAnalyticsEvent type]> property. The primary use of the constant is to pass it as a type
to methods declared in <UpsightDataStoreInterface> protocol to add/remove an observer for
specific type of storable objects.*/
FOUNDATION_EXTERN NSString *const USPubDataType;

/** Instances of this class represent events that happen within your application. An event
could be anything that is of some interest in your application, e.g. when a user clicks a
specific button, adds a friend, etc. You create event objects and send them to Upsight's server
by means of `-[USAnalyticsInterface record:]` to track those events on your dashboard.

`USAnalyticsEvent` objects should be created using the <USEventFactory> class.
*/
@interface USAnalyticsEvent : USEvent

/** Convenience class method for creating event objects.

@param aParameters Parameters of the event.
@param aName User-defined event name. You are free to assign any name to events to logically group them together. For example you can create events with "monetization" name to group together events related to monetization. Note that `.` is a special symbol that can be used within event name to create a compound name, where every `.` represents one level of hierarchy. For example, `my_store.weapons` and `my_store.armor` allows you to get metrics on `my_store` as well as `my_store.weapons` and `my_store.armor` using the Upsight Dashboard.
*/
+ (instancetype)analyticsEventWithParameters:(USEventParameters *)aParameters name:(NSString *)aName;

/** Constructs an event object that encapsulates data representing an event in your application.

@param aParameters Event parameters.
@param aName User-defined event name. You are free to assign any name to events to logically group them together. For example you can create events with "monetization" name to group together events related to monetization. Note that `.` is a special symbol that can be used within event name to create a compound name, where every `.` represents one level of hierarchy. For example, `my_store.weapons` and `my_store.armor` allows you to get metrics on `my_store` as well as `my_store.weapons` and `my_store.armor` using the Upsight Dashboard.
@return An event object.
*/
- (instancetype)initWithParameters:(USEventParameters *)aParameters name:(NSString *)aName NS_DESIGNATED_INITIALIZER;

/** Event name which is the same that is passed on event creation.*/
@property (nonatomic, strong, readonly) NSString *name;
@end
