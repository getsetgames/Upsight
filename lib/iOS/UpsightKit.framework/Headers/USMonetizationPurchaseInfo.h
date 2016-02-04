//
//  USMonetizationPurchaseInfo.h
//  UpsightAnalytics
//
//  Created by Tolik Shevchenko on 4/16/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USPurchaseInfo.h"

/** A specialization of <USPurchaseInfo> that provides initializers appropriate for use when
creating USMonetizationEvent objects.
*/
@interface USMonetizationPurchaseInfo : USPurchaseInfo

/** Convenience method for creating monetization information object.

@param resolution Represents type of monetary transaction that took place. Refer to the
<USPurchaseResolution> enumeration or more details.
@param totalPrice The total price of the transaction, including fractional amounts of the currency, before
store fees have been taken into account.
@param currency The currency as a 3-character ISO 4217 code.
@param product Unique identifier of the product.
*/
+ (instancetype)infoWithResolution:(USPurchaseResolution)resolution
                        totalPrice:(float)totalPrice
                          currency:(NSString *)currency
                           product:(NSString *)product;

/** Convenience method for creating monetization information object. The total price for the
transaction is calculated internally by multiplying the quantity and unit price.

@param resolution Represents type of monetary transaction that took place. Refer to the
<USPurchaseResolution> enumeration or more details.
@param currency The currency as a 3-character ISO 4217 code.
@param quantity The number of goods purchased.
@param product Unique identifier of the product.
@param price The price per unit in local currency.
*/
+ (instancetype)infoWithResolution:(USPurchaseResolution)resolution
                          currency:(NSString *)currency
                          quantity:(NSUInteger)quantity
                           product:(NSString *)product
                             price:(float)price;

/** Designated initializer for restoring information object from its dictionary representation.

@param aDictionary Dictionary representation of the receiver.
*/
- (instancetype)initWithDictionaryRepresentation:(NSDictionary *)aDictionary NS_DESIGNATED_INITIALIZER;

/** The total price of the transaction, including fractional amounts of the currency, before
store fees have been taken into account.*/
@property (nonatomic, assign, readwrite) float totalPrice;

/** The currency as a 3-character ISO 4217 code.*/
@property (nonatomic, strong, readwrite) NSString *currency;

/** Unique identifier of the product.*/
@property (nonatomic, strong, readwrite) NSString *product;
@end
