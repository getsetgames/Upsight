//
//  USEvent.h
//  USDispatcher
//
//  Created by Anton Fedorchenko on 7/14/14.
//  Copyright (c) 2014 Upsight. All rights reserved.
//

#import "UpsightStorableObject.h"

FOUNDATION_EXTERN NSString *const kUSEventType;

@class USEventParameters;

@interface USEvent : UpsightStorableObject <NSCoding>
- (instancetype)initWithType:(NSString *)aStorableType parameters:(USEventParameters *)aParameters NS_DESIGNATED_INITIALIZER;
@property (nonatomic, strong, readonly) USEventParameters *parameters;
@end
