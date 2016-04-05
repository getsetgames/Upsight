//
//  UpsightStorableObject.h
//  Upsight
//
//  Created by Dana Smith on 2014-06-17.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import <CoreData/CoreData.h>

/** UpsightStorableObject is the base class for all objects that can be stored in the UpsightDataStore.
 In addition to the requirement that objects are derived from UpsightStorableObject, custom objects ideally
 have properties of type NSString, NSNumber, NSArray, or NSDictionary. This guarantees that the data can be
 transferred to the Upsight servers, if necessary.
 */
@interface UpsightStorableObject : NSObject

/** A string that identifies a group of objects with identical properties. For example, you could use the class's name. This is
 used during subscription to identify the set of objects you wish to observe. Objects with the same type must also have the same
 set of properties.
*/
@property (nonatomic, copy, readonly) NSString *type;

/** The version of the object's definition. In combination with the type, this value is used to identify the set of properties
 stored for a particular object type. You should increment the version whenever you add, remove, or change one of the properties defined for the class.
 */
@property (nonatomic, readonly) NSNumber *version;

/** An identifier unique to each instance of this object type.
 */
@property (nonatomic, readonly) NSString *ID;

/** Creates an unversioned instance of an UpsightStorableObject with the specified type.
 @param type A string that uniquely identifies the object's class. In combination with the version, this value is used by the system to determine which properties are available on this object.
 @returns An unversioned instance of an UpsightStorableObject or a derived class.
 */
- (instancetype)initWithType:(NSString *)type;

/** Creates an instance of an UpsightStorableObject with the specified type.
 @param type A string that uniquely identifies the object's class. In combination with the version, this value is used by the system to determine which properties are available on this object.
 @param aVersion A string that identifies the version of the storable's class. In combination with the type, this value is used by the system to determine which properties are available on this object. Passing nil will create an unversioned instance. You should increment the version whenever you add, remove, or change one of the properties defined for the class.
 @param anID A string that uniquely identifies the returned instance. Passing nil will cause the system to generate a unique ID for the instance
 @returns An instance of an UpsightStorableObject or a derived class.
 */
- (instancetype)initWithType:(NSString *)type version:(NSNumber *)aVersion ID:(NSString *)anID NS_DESIGNATED_INITIALIZER;

/** Creates an instance of an UpsightStorableObject from the data contained in an NSDictionary.
 @param dictionaryRepresentation An NSDictionary whose keys correspond to the properties of the class to be instanced, and whose values will be used to set the values of the properties.
 @returns An instance of an UpsightStorableObject or a derived class whose properties are initialized with the values stored in the dictionary.
 */
- (instancetype)initWithDictionaryRepresentation:(NSDictionary *)dictionaryRepresentation;

/** Generates a dictionary whose keys are the property names of the receiver, and whose values are the current values of the receiever's properties
 @param error Contains a description of the error if an NSDictionary cannot be created from the receiver.
 @returns An NSDictionary whose keys are the names of the receiver's properties and whose values are the current values of the receiver's properties.
 */
- (NSDictionary *)dictionaryRepresentation:(NSError * __autoreleasing *)error;

@end
