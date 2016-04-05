//
//  USBillboardManager.h
//  USBillboards
//
//  Created by Anton Fedorchenko on 11/13/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "USBillboard.h"

/** Represents interface of a class managing billboards.*/
@protocol USBillboardManager <NSObject>
/** Provides access to billboards by their associated scope.

@param aScope A unique scope used to find associated billboard.
@return A billboard with the requested scope.
*/
- (id<USBillboard>)billboardForScope:(NSString *)aScope;
@end
