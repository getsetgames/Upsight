//
//  UpsightStoreInterface.h
//  Upsight
//
//  Created by Dana Smith on 2014-05-13.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UpsightStorableObject.h"

/** UpsightObservableAction
 
 These are the actions that will trigger an observer to be called. The observer will be informed which action triggered it.
 
 */
typedef NS_ENUM(NSUInteger, UpsightObservableAction) {
    /// An object was added to the observed UpsightDataStore.
    UpsightObservableActionStore,
    /// An object in the observed UpsightDataStore was updated.
    UpsightObservableActionUpdate,
    /// An object was removed from the observed UpsightDataStore.
    UpsightObservableActionDelete
};

/** This block type defines the callback block that is provided to a variety of the UpsightDataStore methods.
 
 @param error   If there is a failure in the data operation method to which this block is passed, error will 
                describe the problem. Otherwise it is nil.
 @param object  This is the object that was provided to the operation method that is calling the block.
 
 @return None.
 */
typedef void (^UpsightDataStoreCompletion)(NSError *error, UpsightStorableObject *object);

/** This block type defines the callback block that is provided to a UpsightDataStore methods that operate on multiple objects.
 
 @param error   If there is a failure in the data operation method to which this block is passed, error will
 describe the problem. Otherwise it is nil.
 @param object  This is the object that was provided to the operation method that is calling the block.
 
 @return None.
 */
typedef void (^UpsightDataStoreObjectsCompletion)(NSError *error, NSArray *objects);

/**
 * This protocol defines the interface to the UpsightDataStore.
 * The UpsightDataStore is a class that stores arbitrary data objects, each with its own type.
 * It also provides an interface by which observer methods are registered against those types.
 * The data store calls the observers when data of the specified type is stored, removed, or updated.
 *
 * The UpsightDataStore with it's store/observe mechanism is the basis of the Upsight platform.
 */

@protocol UpsightDataStoreInterface <NSObject>

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** addObserver:selector:type
 
 Registers a method of an object so that when data of the specified type is stored in, changed in, or removed from the data store, that method is called on a background queue.
 
 @param observer    The object that implements the selector.
 @param selector    A method with two parameters: an id which is the object that was stored/changed/removed and an UpsightObservableAction which indicates the reason for calling the observer.
 @param type        When data of this type is stored, removed, or updated, the selector message is sent to observer.
 @return None.
 */
- (void)addObserver:(NSObject *)observer selector:(SEL)selector type:(NSString *)type;

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** addObserver:observer:selector:type:queue
 
 Registers a method of an object so that when data of the specified type is stored in, changed in, or removed removed from the data store, that method is called on the specified queue.
 
 @param observer    The object that implements the selector.
 @param selector    A method with two parameters: an id which is the object that was stored/changed/removed and an UpsightObservableAction which indicates the reason for calling the observer.
 @param type        When data of this type is stored, removed, or updated, the selector message is sent to observer.
 @param queue       The NSOperationQueue on which the selector should be called.
 @return None.
 */
- (void)addObserver:(NSObject *)observer selector:(SEL)selector type:(NSString *)type queue:(NSOperationQueue *)queue;

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** addObserver:observer:selector:type:queue:predicate
 
 Registers a method of an object so that when data of the specified type is stored in, updated in or removed from the data store, that method is called on the specified queue.
 
 @param observer    The object that implements the selector.
 @param selector    A method with two parameters: an id which is the object that was stored/changed/removed and an UpsightObservableAction which indicates the reason for calling the observer.
 @param type        When data of this type is stored, removed, or updated, the selector message is sent to observer.
 @param queue       The NSOperationQueue on which the selector should be called.
 @param predicate   Only objects for which the predicate evaluates to TRUE will be sent to the observer. This evaluation is in addition to matching the type.
 @return None.
 */
- (void)addObserver:(NSObject *)observer selector:(SEL)selector type:(NSString *)type queue:(NSOperationQueue *)queue predicate:(NSPredicate *)predicate;

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** addDefaultObserver:observer:selector:
 
 Registers a method of an object that will be called whenever an object is stored, updated, or removed, but no other observer matches the object's type and predicate.
 
 @param observer    The object that implements the selector.
 @param selector    A method with two parameters: an id which is the object that was stored/changed/removed and an UpsightObservableAction which indicates the reason for calling the observer.
 @return None.
 */
- (void)addDefaultObserver:(NSObject *)observer selector:(SEL)selector;

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** removeObserver:type
 
 Removes an object's selector from the list of selectors that will be called when objects of the specified type are stored, removed, or updated.
 
 @param observer    An object previously registered as an observer with one of the addObserver methods.
 @param type        The type for which the observer was previously registered. It was supplied as the type parameter in the call to the addObserver method.
 @return None.
 */
- (void)removeObserver:(NSObject *)observer type:(NSString *)type;

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** removeObserver:type:predicate
 
 Removes an object's selector from the list of selectors that will be called when objects of the specified type and matching the predicate are stored, removed, or updated.

 
 @param observer    An object previously registered as an observer with one of the addObserver methods.
 @param type        The type that was supplied when the observer was registered with the addObserver method.
 @param predicate   The predicate that was supplied when the observer was registered with the addObserver method.
 @return None
 */
- (void)removeObserver:(NSObject *)observer type:(NSString *)type predicate:(NSPredicate *)predicate;

/**---------------------------------
 * @name Managing Observers
 *  --------------------------------
 */

/** removeDefaultObserver:
 
 Removes an object's selector from the list of selectors that will be called in case an object is stored, removed, or updated and no other observers match its type or predicate.
 
 @param observer An object previously registered as a default observer using the addDefaultObserver:observer:selector method.
 @return None.
 */
- (void)removeDefaultObserver:(NSObject *)observer;

/**---------------------------------
 * @name Working with Data
 *  --------------------------------
 */

/** store:completion
 
 Persists an object. Registered observers will be called if they are watching this object's type and optionally have a predicate that evaluates to TRUE for this object.
 
 @param object      An instance of a class derived from UpsightStorableObject. This object will be stored and kept until removed.
 @param completionBlock  A block that will be executed once the object is stored. If there was a problem storing the object it will be reported in the error provided. Do not add or remove observers within this block.
 @return None.
 */
- (void)store:(UpsightStorableObject *)object completion:(UpsightDataStoreCompletion)completionBlock;

/**---------------------------------
 * @name Working with Data
 *  --------------------------------
 */

/** remove:completion
 
 Removes the provided object from persistent storage. Note that it is an error to call remove with an object that was never passed to the store method.
 
 @param object The object to be removed from storage.
 @param completionBlock  A block that will be executed once the object is removed. If there was a problem removing the object it will be reported in the error provided. Do not add or remove observers within this block.
 @return None.
 */
- (void)remove:(UpsightStorableObject *)object completion:(UpsightDataStoreCompletion)completionBlock;

/**---------------------------------
 * @name Working with Data
 *  --------------------------------
 */

/** removeObjects:completion
 
 Removes the provided list of objects from persistent storage. Note that it is an error to call remove with an object that was never passed to the store method.
 
 @param objects An NSArray of the objects to be removed from storage.
 @param completionBlock  A block that will be executed once the object is removed. If there was a problem removing the object it will be reported in the error provided. If you attempt to remove an object that has not been stored, you will receive an UpsightDataStoreObjectNotPreviouslyStored error. The userInfo in the error will contain the unstored object in the key "unstoredObject". Do not add or remove observers within this block.
 @return None.
 */
- (void)removeObjects:(NSArray *)objects completion:(UpsightDataStoreObjectsCompletion)completionBlock;

/**---------------------------------
 * @name Working with Data
 *  --------------------------------
 */

/** queryObjects:predicate
 
 Returns an array of all objects that match the type and for which the predicate evaluates to TRUE. The method synchronously performs data store query blocking the calling thread.
 
 @param type        The type of object to be returned in list.
 @param predicate   A set of conditions to be met by the objects returned. May be nil.
 @return An array of all the objects of the specified type for which the predicate evaluates to TRUE.
 */
- (NSArray *)queryObjects:(NSString *)type predicate:(NSPredicate *)predicate;


@end
