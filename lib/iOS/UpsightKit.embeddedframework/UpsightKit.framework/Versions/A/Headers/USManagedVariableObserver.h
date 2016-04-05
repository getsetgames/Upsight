//
//  USManagedVariableObserver.h
//  USBillboards
//
//  Created by Anton Fedorchenko on 10/29/15.
//  Copyright © 2015 Upsight. All rights reserved.
//

@import Foundation;

@protocol USManagedVariableObserverDelegate;

/** Abstracts an observer receiving events related to managed variables also referred to as UXM values.
The observer forwards events to its delegate, for more details see methods declared in <USManagedVariableObserverDelegate> protocol.*/
@protocol USManagedVariableObserver <NSObject>
/** Accessor to the receiver's delegate.*/
@property (nonatomic, weak, nullable) id<USManagedVariableObserverDelegate> delegate;
@end

/** Represents interface of <USManagedVariableObserver>'s delegate.*/
@protocol USManagedVariableObserverDelegate <NSObject>
@optional

/** Requests confirmation that pending Managed Variable updates should be applied.
 
 @param anObserver An observer that observed the event.
 @returns YES if the pending UXM changes should be applied, NO otherwise.
 */
- (BOOL)observerShouldSynchronizeManagedVariables:(nonnull id<USManagedVariableObserver>)anObserver;

/** Notifies the delegate of the end of variables synchronization. At the time this method is
called, the system has finished variables synchronization which is a good point to access new
values through <USManagedVariable> class methods.

@param anObserver An observer that observed the event.
@param updatedVariableTags Tags of UXM variables that were updated during synchronization.
*/
- (void)observer:(nonnull id<USManagedVariableObserver>)anObserver didSynchronizeManagedVariables:(nonnull NSArray *)updatedVariableTags;
@end
