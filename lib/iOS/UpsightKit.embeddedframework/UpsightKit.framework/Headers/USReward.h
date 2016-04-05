//
//  USReward.h
//  USBillboards
//
//  Created by Anton Fedorchenko on 1/19/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Abstracts Upsight reward, an object that gets propagated from the server to the
application and eventually is expected to be passed to a user.*/
@protocol USReward <NSObject>
/** Unique identifier of a reward.

It is up to application developer to define what rewards make sense in their app and how
they are presented to a user. An example of a reward could be "golden coins", etc..
*/
@property (nonatomic, readonly) NSString *productIdentifier;

/** Property representing the number of reward items.

As an example a reward object can represent 100 "golden coins".
*/
@property (nonatomic, readonly) NSUInteger quantity;

/** Property containing an NSData object that can be used locally or on a server to validate that a given reward and quantity originated on the Upsight server
 */
@property (nonatomic, readonly) NSData *signatureData;

@end
