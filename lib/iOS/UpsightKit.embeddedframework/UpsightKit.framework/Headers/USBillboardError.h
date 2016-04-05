//
//  USBillboardError.h
//  USBillboardManager
//
//  Created by Anton Fedorchenko on 10/2/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Predefined domain for errors from APIs defined in USBillboards library.
FOUNDATION_EXTERN NSString *const USBillboardErrorDomain;

/// Error codes indicating specific errors from USBillboards library.
typedef NS_ENUM(NSUInteger, USBillboardError)
{
    /// Indicates that the SDK is not able to pass context to a content unit web view.
    USBillboardErrorLoadContext = 1000
};
