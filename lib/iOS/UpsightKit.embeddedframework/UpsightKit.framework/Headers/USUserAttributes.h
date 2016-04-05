//
//  USUserAttributes.h
//  UpsightAnalytics
//
//  Created by Dana Smith on 2015-04-24.
//  Copyright (c) 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

/** User Attributes are properties you define which appear on every event sent to the Upsight
servers. You must first define the attributes in the Info section of your project's settings.
	
1. Add a new row to your project's Info list and name it `UpsightUserAttributes`
1. Set the new row's type to `Dictionary`
2. Click on the disclosure triangle to the left of `UpsightUserAttributes`
3. Add a new row for each of the User Attributes you want to include, providing a name, type,
and default value for each

Within your code you can retrieve and set values for the User Attributes you have created.
You access them by name. Assuming you used the preceding steps to create two attributes called
"myNumberAttribute" and "myStringAttribute" with type Number and String respectively, you
would retrieve their values with the following:

	NSNumber *aNumber = [USUserAttributes numberForKey:@"myNumberAttribute"];
	NSString *aString = [USUserAttributes stringForKey:@"myStringAttribute"];
	
This returns the default values as defined in the Info settings, unless you change the values,
like this:

	[USUserAttributes setNumber:@(10) forKey:@"myNumberAttribute"];
	[USUserAttributes setString:@"aString" forKey:@"myStringAttribute"];
	
Now, `NSNumber *aNumber = [USUserAttributes numberForKey:@"myNumberAttribute"];` will return
10 and `NSString *aString = [USUserAttributes stringForKey:@"myStringAttribute"];` will return
aString.

Note that you cannot programmatically add or remove User Attributes. They must be added and
removed through the Info settings. Adding and removing User Attributes will cause a discontinuity
in the data stored on Upsight's servers, so it is something you should do only with forethought
and planning.*/
@interface USUserAttributes : NSObject

/** Sets a number value for an attribute specified by aKey. Note the actual type of the user
attribute defined in your application plist file should be Number, otherwise this method has
no effect.

@param aNumber A new value for the user attribute indicated by aKey.
@param aKey Name of the user attribute that should be changed.
*/
+ (void)setNumber:(NSNumber *)aNumber forKey:(NSString *)aKey;

/** Accesses the value of a specified number user attribute. Returns the default value as defined in the application
plist file, unless you changed the values with <[USUserAttributes setNumber:forKey:]>

@param aKey Name of the user attribute whose value is to be returned.
*/
+ (NSNumber *)numberForKey:(NSString *)aKey;

/** Sets a string value for an attribute specified by aKey. Note the actual type of the user
attribute defined in your application plist file should be String, otherwise this method has
no effect.

@param aString A new value for the user attribute indicated by aKey.
@param aKey Name of the user attribute that should be changed.
*/
+ (void)setString:(NSString *)aString forKey:(NSString *)aKey;

/** Accesses the value of a specified string user attribute. Returns the default value as
defined in the application plist file, unless you changed the values with <[USUserAttributes setString:forKey:]>

@param aKey Name of the user attribute whose value is to be returned.
*/
+ (NSString *)stringForKey:(NSString *)aKey;

/** Accesses the dictionary representation of user attributes defined in the application. The
dictionary contains actual values, reflecting the changes made through the setters exposed
by the class.*/
+ (NSDictionary *)dictionaryRepresentation;

@end
