//
//  USInAppPurchaseResolution.h
//  UpsightAnalytics
//
//  Created by Dana Smith on 2015-01-30.
//  Copyright (c) 2015 Upsight. All rights reserved.
//
#import <Foundation/Foundation.h>

/** Represents the type of monetary transaction that took place. To create events of the <USInAppPurchaseEvent> class use the following mapping between the `USPurchaseResolution` and `SKPaymentTransaction` enumerations:

- `SKErrorPaymentCancelled` - IAP with resolution USPurchaseResolutionCancel
- `SKErrorPaymentInvalid` - IAP with resolution USPurchaseResolutionCancel
- `SKErrorPaymentNotAllowed` - IAP with resolution USPurchaseResolutionCancel
- `SKErrorClientInvalid` - no IAP
- `SKErrorStoreProductNotAvailable` - no IAP
- `SKErrorUnknown` - no IAP
*/
typedef NS_ENUM(NSUInteger, USPurchaseResolution)
{
    /** A 'buy' represents a purchase was made.*/
    USPurchaseResolutionBuy = 0,
    /** A 'cancel' indicates that the user cancelled the transaction before making the purchase.*/
    USPurchaseResolutionCancel,
    /** A 'fraud' indicates that a fraud was detected in the purchase workflow. The SDK doesn't set the resolution to fraud, but the server might.*/
    USPurchaseResolutionFraud,
    /** A 'refund' would be issued after the purchase, reversing it.*/
    USPurchaseResolutionRefund
};
