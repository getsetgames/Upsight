//
//  Upsight.h
//  UpsightKit
//
//  Created by Dana Smith on 2015-01-29.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USInAppPurchaseResolution.h"
#import "UpsightLoggerLevel.h"

@protocol UpsightDataStoreInterface;
@protocol USManagedVariableObserver;
@protocol USBillboard;
@class CLLocation;

/** This is the main class you use to interface with the Upsight framework. It has a number of class methods you use to send events,
get status information or display content.
 
For more details about adding the framework to your application, see the [integration instructions](http://help.upsight.com/api_sdk_reference/ios/#integration).
 */
@interface Upsight : NSObject

/** Provides read-only access to the app token you set in your app's Info.plist. This value is supplied on your application's dashboard. */
+ (NSString *)token;

/** Provides read-only access to the public key you set in your app's Info.plist. This value is supplied on your applicaiton's dashboard. */
+ (NSString *)publicKey;

/** Sends information to the Upsight server representing events that happen within your application. An event
 could be anything that is of some interest in your application, e.g. when a user clicks a
 specific button, adds a friend, etc.
 
 @param name User-defined event name. You are free to assign any name to events to logically group them together. For example you can create events with "monetization" name to group together events related to monetization. Note that `.` is a special symbol that can be used within event name to create a compound name, where every `.` represents one level of hierarchy. For example, `my_store.weapons` and `my_store.armor` allows you to get metrics on `my_store` as well as `my_store.weapons` and `my_store.armor` using the Upsight Dashboard.
 @param properties A dictionary containing any information you would like to associate with this event.
 */
+ (void)recordAnalyticsEventWithName:(NSString *)name properties:(NSDictionary *)properties;

/** Event representing a monetary transaction, in which the user is paying you for
 goods or services.
 
 @param resolution Represents type of monetary transaction that took place. Refer to the
 <USPurchaseResolution> enumeration or more details.
 @param totalPrice The total price of the transaction, including fractional amounts of the currency, before
 store fees have been taken into account.
 @param currency The currency as a 3-character ISO 4217 code.
 @param product Unique identifier of the product.
 @param properties A dictionary containing any information you would like to associate with this event.
 @param properties A dictionary containing any information you would like to associate with this event.
 */
+ (void)recordMonetizationEventWithResolution:(USPurchaseResolution)resolution
                                   totalPrice:(float)totalPrice
                                     currency:(NSString *)currency
                                      product:(NSString *)product
                                   properties:(NSDictionary *)properties;

/** Event representing a monetary transaction, in which the user is paying you for
 goods or services. The total price for the transaction is calculated internally 
 by multiplying the quantity and unit price.
 
 @param resolution Represents type of monetary transaction that took place. Refer to the
 <USPurchaseResolution> enumeration or more details.
 @param currency The currency as a 3-character ISO 4217 code.
 @param quantity The number of goods purchased.
 @param product Unique identifier of the product.
 @param price The price per unit in local currency.
 @param properties A dictionary containing any information you would like to associate with this event.
 */
+ (void)recordMonetizationEventWithResolution:(USPurchaseResolution)resolution
                                     currency:(NSString *)currency
                                     quantity:(NSUInteger)quantity
                                      product:(NSString *)product
                                        price:(float)price
                                   properties:(NSDictionary *)properties;

/** An event representing the purchase of virtual goods through an In App Purchase. These events are subject to
 verification by the Upsight server.
 
 @param resolution Represents the type of monetary transaction that took place. Refer to the
 <USPurchaseResolution> enumeration or more details.
 @param currency The currency as a 3-character ISO 4217 code. This can be retrieved from an `SKProduct` object.
 @param quantity The number of goods purchased. This should be taken from the `SKPayment` object.
 @param product Unique identifier of the product. This should be taken from the `SKPayment` object.
 @param price The price per unit in local currency. This can be retrieved from an `SKProduct` object.
 @param transactionIdentifier Identifier of the transaction returned by `-[SKPaymentTransaction transactionIdentifier]`
 @param properties A dictionary containing any information you would like to associate with this event.
 */
+ (void)recordInAppPurchaseEventWithResolution:(USPurchaseResolution)resolution
                                       product:(NSString *)product
                                      quantity:(NSUInteger)quantity
                                         price:(float)price
                                      currency:(NSString *)currency
                         transactionIdentifier:(NSString *)transactionIdentifier
                                    properties:(NSDictionary *)properties;

/** An event indicating that a specific point in the application has been reached. This may represent an action taken or progress made by the user, a particular line/region of code, or any other point of interest.
 
 @param scope An NSString that uniquely identifies the point of interest that has been reached.
 */
+ (void)recordMilestoneEventForScope:(NSString *)scope;

/** An event indicating that a specific point in the application has been reached. This may represent an action taken or progress made by the user, a particular line/region of code, or any other point of interest.
 
 @param scope An NSString that uniquely identifies the point of interest that has been reached.
 @param properties A dictionary containing any information you would like to associate with this event.
 */
+ (void)recordMilestoneEventForScope:(NSString *)scope properties:(NSDictionary *)properties;

/** Retrieves the <USBillboard> object associated with a specific point of interest within the application. Setting a delegate on the billboard
 allows you to control the display of any content associated with the scope.

 @param scope An NSString that uniquely identifies a point of interest in your application.
 */
+ (id<USBillboard>)billboardForScope:(NSString *)scope;

/** If setLocation is called, the provided location will be attached to all events that are sent until the location is updated, or the application is put in the background for long.
 enough that the current session is considered finished.
 
 @param location A CLLocation object retrieved from one of Appple's location services.
 */
+ (void)setLocation:(CLLocation *)location;

/** Provides read-only access to the current state of the Opt Out flag. */
+ (BOOL)optOutStatus;

/** Allows you to set the Opt Out flag. For a description of the effect of the Opt Out flag, see
 the Upsight document regarding [COPPA Compliance](http://help.upsight.com/api_sdk_reference/ios/#coppa)
 
 @param optOut The new value for the Opt Out flag.
 */
+ (void)setOptOutStatus:(BOOL)optOut;

/** Provides read-only access to the current log level used for reporting all log messages. */
+ (UpsightLoggerLevel)defaultLogLevel;

/** Allows you to set the log level. Any message with a log level equal to or above the level you set will be
 displayed in the debug output window. For example, setting a value of `UpsightLoggerLevelError` will display all messages logged with a level of `UpsightLoggerLevelError` or `UpsightLoggerLevelCritical`
 It is recommended that you begin your integration with `UpsightLoggerLevelDebug` until you get the integration working, at which point you can change the level to `UpsightLoggerLevelError` (which is the default).
 
 @param level The new filter level for log messages. See <UpsightLoggerLevel> for details.
 */
+ (void)setDefaultLogLevel:(UpsightLoggerLevel)level;

/** You set a delegate on the Managed Variable Observer if you wish to control the timing of updates to Managed Variables. */
+ (id<USManagedVariableObserver>)variableObserver;

@end
