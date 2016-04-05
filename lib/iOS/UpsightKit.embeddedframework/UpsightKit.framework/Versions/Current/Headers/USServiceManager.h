//
//  USServiceManager.h
//  USServiceManager
//
//  Created by Dana Smith on 2014-07-10.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol UpsightDataStoreInterface;
@protocol USAnalyticsInterface;
@protocol USBillboardManager;
@protocol USActionMapManagerInterface;
@class USInstallationTracker;

@interface USServiceManager : NSObject

+ (instancetype)sharedServiceManager;
+ (id<USAnalyticsInterface>)analyticsForStore:(id<UpsightDataStoreInterface>)datastore;
+ (id<USBillboardManager>)billboardManagerForStore:(id<UpsightDataStoreInterface>)datastore;
+ (id<USActionMapManagerInterface>)actionMapManagerForStore:(id<UpsightDataStoreInterface>)datastore;

+ (USInstallationTracker *)installationTracker;

@end
