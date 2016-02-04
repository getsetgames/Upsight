//
//  USMonetizationEvent.h
//  UpsightAnalytics
//
//  Created by Anton Fedorchenko on 8/4/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import "USEvent.h"

@class USMonetizationPurchaseInfo;
@class USEventParameters;

/** Event representing a monetary transaction, in which the user is paying the app developer for
goods or services.
*/
@interface USMonetizationEvent : USEvent
/** Convenience method for creating a monetization event. Events should be created using <USEventFactory> class.

@param aParameters Parameters of the event.
@param anInfo An object containing information about the monetary transaction. Refer to the
<USMonetizationPurchaceInfo> class for more details.
@return An initialized event.
*/
+ (instancetype)monetizationEventWithWithParameters:(USEventParameters *)aParameters info:(USMonetizationPurchaseInfo *)anInfo;

/** Accessor to the monetary information passed at event creation time.*/
@property (nonatomic, strong, readonly) USMonetizationPurchaseInfo *info;
@end
