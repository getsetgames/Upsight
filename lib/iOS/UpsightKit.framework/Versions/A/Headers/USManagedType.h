//
//  USManagedType.h
//  USBillboards
//
//  Created by Tolik Shevchenko on 7/23/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Base interface for objects representing UXM variables, dynamic values controlled from
the dashboard and propagated to the application when as it runs.*/
@protocol USManagedType <NSObject>
/** Tag is an unique string that is used to identify UXM variables.*/
@property (nonatomic, strong, readonly) NSString *tag;
@end
