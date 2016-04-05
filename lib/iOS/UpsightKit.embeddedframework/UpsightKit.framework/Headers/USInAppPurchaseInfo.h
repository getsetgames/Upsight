//
//  USInAppPurchaseInfo.h
//  UpsightAnalytics
//
//  Created by Tolik Shevchenko on 12/12/14.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USPurchaseInfo.h"

/** Encapsulates the data associated with in-app purchases.*/
@interface USInAppPurchaseInfo : USPurchaseInfo

/** Convenience method for creating in-app purchase information object.

@param resolution Represents the type of monetary transaction that took place.
@param currency The currency as a 3-character ISO 4217 code. This can be retrieved from an `SKProduct` object.
@param quantity The number of goods purchased. This should be taken from the `SKPayment` object.
@param product Unique identifier of the product. This should be taken from the `SKPayment` object.
@param price The price per unit in local currency. This can be retrieved from an `SKProduct` object.
@param transactionIdentifier Identifier of the transaction returned by `-[SKPaymentTransaction transactionIdentifier]`
*/
+ (instancetype)IAPInfoWithResolution:(USPurchaseResolution)resolution
                             currency:(NSString *)currency
                             quantity:(NSUInteger)quantity
                              product:(NSString *)product
                                price:(float)price
                transactionIdentifier:(NSString *)transactionIdentifier;

/** Designated initializer for restoring information object from its dictionary representation.

@param aDictionary Dictionary representation of the receiver.
*/
- (instancetype)initWithDictionaryRepresentation:(NSDictionary *)aDictionary NS_DESIGNATED_INITIALIZER;

@property (nonatomic, assign, readonly) USPurchaseResolution resolution;
@property (nonatomic, strong, readonly) NSString *product;
@property (nonatomic, assign, readonly) NSUInteger quantity;
@property (nonatomic, strong, readonly) NSString *transactionIdentifier;
@property (nonatomic, strong) NSString *currency;
@property (nonatomic, assign) float price;
@property (nonatomic, assign) float totalPrice;

/** Accessor for dictionary representation of the receiver.*/
@property (nonatomic, strong, readonly) NSDictionary *dictionaryRepresentation;
@end
