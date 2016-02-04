//
//  UpsightCore.h
//  Upsight
//
//  Created by Dana Smith on 2014-05-13.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UpsightDataStoreInterface.h"

/** This class provides a CoreData based implementation of <UpsightDataStoreInterface> */
@interface UpsightDataStore : NSObject <UpsightDataStoreInterface>

@property (nonatomic, strong, readonly) NSURL *dataStoreURL;

/** This method always returns the same data store object. If you wisht to create a new instance of UpsightDataStore use one of the init methods rather than using the shared object. */
+ (id<UpsightDataStoreInterface>)defaultStore;

/** Returns an object that implements the <UpsightDataStoreInterface> protocol using CoreData
 
 @param directoryURL An NSURL pointing to the folder where you would like the SQLite file to be saved
 @param prefix The .sqlite will be added to this string and the result used as the name of the data base file
 @returns And object conforming to the UpsightDataStoreInterface protocol
 */
- (id)initWithDatabaseDirectoryURL:(NSURL *)directoryURL fileNamePrefix:(NSString *)prefix;

/** Returns an object that implements the <UpsightDataStoreInterface> protocol using CoreData
 
 @param aDataStoreURL An NSURL identifying the full path and name of the file in which the datastore should be saved
 */
- (id)initWithDataStoreURL:(NSURL *)aDataStoreURL  NS_DESIGNATED_INITIALIZER;
@end
