//
//  USManagedVariable.h
//  USBillboards
//
//  Created by Tolik Shevchenko on 7/22/15.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol USManagedString, USManagedInteger, USManagedFloat, USManagedBoolean;

/** Represents interface for accessing UXM variables. If a variable was never changed on
the dashboard, the returned object will have a default value as it is defined in the variable's
schema, in UpsightUXMVariables.plist.*/
@interface USManagedVariable : NSObject
/** Accessor to variables of string type.

@param aTag Unique tag identifying variable that is to be accessed.
*/
+ (id<USManagedString>)managedStringWithTag:(NSString *)aTag;

/** Accessor to variables of integer type.

@param aTag Unique tag identifying variable that is to be accessed.
*/
+ (id<USManagedInteger>)managedIntegerWithTag:(NSString *)aTag;

/** Accessor to variables of floating type.

@param aTag Unique tag identifying variable that is to be accessed.
*/
+ (id<USManagedFloat>)managedFloatWithTag:(NSString *)aTag;

/** Accessor to variables of boolean type.

@param aTag Unique tag identifying variable that is to be accessed.
*/
+ (id<USManagedBoolean>)managedBooleanWithTag:(NSString *)aTag;
@end
