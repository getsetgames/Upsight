//
//  USManagedFloat.h
//  USBillboards
//
//  Created by Tolik Shevchenko on 7/23/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import "USManagedType.h"

/** Represents interface for UXM variables of floating type.*/
@protocol USManagedFloat <USManagedType>
/** Accessor to the actual value of the UXM variable.*/
@property (nonatomic, assign, readonly) float floatValue;
@end
