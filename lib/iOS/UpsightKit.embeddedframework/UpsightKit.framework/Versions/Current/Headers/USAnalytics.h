//
//  USAnalytics.h
//  USAnalytics
//
//  Created by Anton Fedorchenko on 7/3/14.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USAnalyticsInterface.h"

@class USAnalyticsEvent;
@protocol UpsightDataStoreInterface;

/** Concrete implementation of the <USAnalyticsInterface> protocol.*/
@interface USAnalytics : NSObject <USAnalyticsInterface>
@end
