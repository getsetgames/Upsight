//
//  USAnalyticsInterface.h
//  UpsightAnalytics
//
//  Created by Dana Smith on 2014-07-13.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

@class USEvent, CLLocation;
@protocol UpsightDataStoreInterface;

/** `USAnalyticsInterface` represents a service providing ability to "record" analytics events
that happen within an application. The service is responsible for guaranteed delivery of events
to a server by recording given events in a persistent data base and then sending them to a
designated server; all network and event queue management tasks are automatic.
*/
@protocol USAnalyticsInterface <NSObject>

/** Initializes and returns a new instance of an object conforming to the USAnalyticsInterface protocol.

@param aDataStore A data store instance that is to be used by the newly created analytics
service to record data. If you pass nil, the analytics service will use the
default instance of the data store.

@return A new instance of analytics service.
*/
- (instancetype)initWithDataStore:(id<UpsightDataStoreInterface>)aDataStore;

/** Stores a given object in the data store that was passed during service instantiation. Once the
object is stored in the data base it is automatically scheduled for delivery to the server.

@param anEvent An event object than can be stored in the data base. For more information
on objects of USAnalyticsEvent class, refer to USAnalyticsEvent header documentation.
*/
- (void)record:(USEvent *)anEvent;
@end
