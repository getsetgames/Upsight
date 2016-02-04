//
//  USPurchase.h
//  USBillboards
//
//  Created by Anton Fedorchenko on 1/19/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Abstracts Upsight purchase, an object that gets propagated from the server to the
application. When the application receives a purchase from the SDK it is expected to
perform in-app purchase procedure and pass the purchase to a user.*/
@protocol USPurchase <NSObject>
/** iTunes product identifier.*/
@property (nonatomic, readonly) NSString *productIdentifier;

/** Quantity of the items to purchase.*/
@property (nonatomic, readonly) NSUInteger quantity;
@end
