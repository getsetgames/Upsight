//
//  USMilestoneEvent.h
//  UpsightAnalytics
//
//  Created by Anton Fedorchenko on 10/31/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import "USEvent.h"

/** Type identifying storable objects of <USMilestoneEvent> class. It is the same type as returned
by <[USMilestoneEvent type]> property. The primary use of the constant is to pass it as a type
to methods declared in <UpsightDataStoreInterface> protocol to add/remove an observer for
specific type of storable objects.*/
FOUNDATION_EXTERN NSString *const USMilestoneEventDataType;

@class USEventParameters;

/** An event indicating that a specific point in the application has been reached. This may represent an action taken or progress made by the user, a particular line/region of code, or any other point of interest.*/
@interface USMilestoneEvent : USEvent

/** Convenience method for creating a milestone event. Events should be created using <USEventFactory> class.

@param aParameters Parameters of the event.
@param aScope The scope describes the point in the application which has been reached.
*/
+ (instancetype)milestoneEventWithParameters:(USEventParameters *)aParameters scope:(NSString *)aScope;

/** Accessor to the scope passed at event creation time.*/
@property (nonatomic, readonly) NSString *scope;
@end
