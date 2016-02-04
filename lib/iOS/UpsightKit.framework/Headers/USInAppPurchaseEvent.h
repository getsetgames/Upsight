//
//  USInAppPurchaseEvent.h
//  UpsightAnalytics
//
//  Created by Tolik Shevchenko on 12/10/14.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import "USEvent.h"

@class USInAppPurchaseInfo;
@class USEventParameters;

/** An event representing a purchase of virtual goods through an In App Purchase.*/
@interface USInAppPurchaseEvent : USEvent

/** Convenience method for creating an in-app purchase event. Events should be created using <USEventFactory> class.

@param aParameters Parameters of the event.
@param anInfo Information object encapsulating data about the purchase. Refer to the
<USInAppPurchaseInfo> class for more details.
*/
+ (instancetype)inAppPurchaseEventWithParameters:(USEventParameters *)aParameters IAPInfo:(USInAppPurchaseInfo *)anInfo;

/** Accessor to the information object passed to the initializer.*/
@property (nonatomic, strong, readonly) USInAppPurchaseInfo *info;
@end
