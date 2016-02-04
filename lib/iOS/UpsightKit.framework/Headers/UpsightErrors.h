//
//  UpsightErrors.h
//  Upsight
//
//  Created by Dana Smith on 2014-05-21.
//  Copyright (c) 2014 Upsight. All rights reserved.
//
#import <Foundation/Foundation.h>

extern NSString * const UpsightErrorDomain;

/** Following are the error codes from the UpsightErrorDomain
 */
typedef NS_ENUM(NSUInteger, UpsightError) {
    /// An attempt was made to update a read-only object. The objects delivered to observers are read-only
    UpsightDataStoreReadOnlyObject = 0,
    
    /// The UpsightStorableObject could not be represented as an NSDictionary
    UpsightDataStoreNoDictionaryRepresentation,
    
    /// The UpsightStorableObject could not be converted to a JSON representation
    UpsightDataStoreNoJSONRepresentation,
    
    /// An attempt was made to remove an UpsightStorableObject that isn't in the data store
    UpsightDataStoreObjectNotPreviouslyStored,
    
    /// The Upsight server responded with an error when an UpsightStorableObject was delivered to it
    USDispatcherServerError,
    
    /// The framework encountered an HTTP error when attempting to deliver data to the Upsight server
    USDispatcherHTTPError,
    
    /// An action in an action map failed to execute
    UpsightErrorCannotExecuteAction
};
