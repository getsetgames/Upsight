//
//  USPurchaseInfo.h
//  UpsightAnalytics
//
//  Created by Tolik Shevchenko on 4/16/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USInAppPurchaseResolution.h"

/** Represents information about monetary transactions.*/
@interface USPurchaseInfo : NSObject <NSCoding>

/** Represents type of monetary transaction that took place.*/
@property (nonatomic, assign, readonly) USPurchaseResolution resolution;

/** Unique identifier of the product.*/
@property (nonatomic, strong, readonly) NSString *product;

/** The number of goods purchased.*/
@property (nonatomic, assign, readonly) NSUInteger quantity;

/** The currency as a 3-character ISO 4217 code.*/
@property (nonatomic, strong, readonly) NSString *currency;

/** The price per unit in local currency.*/
@property (nonatomic, assign, readonly) float price;

/** The total price of the transaction, including fractional amounts of the currency, before
store fees have been taken into account.*/
@property (nonatomic, assign, readonly) float totalPrice;

/** Accessor to dictionary representation of the receiver.*/
@property (nonatomic, strong, readonly) NSDictionary *dictionaryRepresentation;
@end
