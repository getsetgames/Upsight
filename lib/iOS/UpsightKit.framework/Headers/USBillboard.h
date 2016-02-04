//
//  USBillboard.h
//  USBillboards
//
//  Created by Anton Fedorchenko on 11/10/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol USBillboardDelegate;
@protocol USReward;
@protocol USPurchase;

/** An abstraction representing place for presenting marketing content such as an interstitial,
opt-in data collection, more games widget, in-app store, etc..

Each billboard is associated with a scope - a unique identifier of the billboard. Only
content with the same scope can be presented in the billboard.
*/
@protocol USBillboard <NSObject>
@required
/** A scope associated with the billboard. This is a string used for targeting of marketing
content from the Upsight Dashboard.
*/
@property (copy, readonly) NSString *scope;

/** A flag indicating if the billboard is busy presenting contents.*/
@property (readonly, getter=isPresenting) BOOL presenting;
/** The billboard's delegate.

To be able to see contents in the billboard, you must assign a delegate to the billboard
and provide a presenting view controller so that the billboard could incorporate its
contents in the view controllers hierarchy.
*/
@property (weak) id<USBillboardDelegate> delegate;

/** Indicates if there is content available for this billboard.

If there is content available for the billboard, it can be presented right away by assigning
a delegate to the receiver and providing a presenting view controller. For more details on
the content presentation see <[USBillboardDelegate presentingViewControllerForBillboard:]> method.
*/
@property (readonly, getter = isContentReady) BOOL contentReady;
@end

/** <USBillboardDelegate> provides ability to control <USBillboard> presentation and react
to related events.
*/
@protocol USBillboardDelegate <NSObject>
@required
/** A delegate method that must be implemented to see contents in the billboard.

This method get's called each time the billboard receives contents it can present. If the
delegate it not interested in seeing billboard's contents, it should return nil.

@param aBillboard A billboard requesting a presentation controller to stick its contents
into view controllers hierarchy. The presenting view controller is expected to be the one
that is currently presented on screen.
*/
- (UIViewController *)presentingViewControllerForBillboard:(id<USBillboard>)aBillboard;

@optional
/** A delegate method that is called when the billboard is about to present its contents.

@param aBillboard A billboard that is about to present its contents.
*/
- (void)billboardWillAppear:(id<USBillboard>)aBillboard;

/** A delegate method that is called right after the billboard presents its contents.

@param aBillboard A billboard who's content was presented.
*/
- (void)billboardDidAppear:(id<USBillboard>)aBillboard;

/** A delegate method that is called when the billboard is about to dismiss its contents.

@param aBillboard A billboard that is about to dismiss its contents.
*/
- (void)billboardWillDismiss:(id<USBillboard>)aBillboard;

/** A delegate method that is called right after the billboard dismisses its contents.

@param aBillboard A billboard who's content was dismissed.
*/
- (void)billboardDidDismiss:(id<USBillboard>)aBillboard;

/** A delegate method that is called when a content presented in the billboard unlocks a
reward.

It is up to an application developer to figure out what exactly needs to be done to unlock
that reward. The billboard just initiates the process and your app is responsible for
ensuring that the reward ends up in the right place.

@param aBillboard A billboard that received a reward.
@param aReward A reward object that is associated with the contents currently presented in
the billboard.
*/
- (void)billboard:(id<USBillboard>)aBillboard didReceiveReward:(id<USReward>)aReward;

/** A delegate method that is called when a content presented in the billboard initiates a
purchase process, usually as a result of user interaction with the presented content.

It is up to an application developer to start in-app purchase procedure by creating
SKProductsRequest with subsequent payment. Once the purchase process is completed you
should send in-app purchase (IAP) event to the Upsight server by calling
<+[Upsight recordInAppPurchaseEventWithResolution:product:quantity:price:currency:transactionIdentifier:properties:]>.

@param aBillboard A billboard that received a purchase.
@param aPurchase A purchase object that is associated with the contents currently presented
in the billboard.
*/
- (void)billboard:(id<USBillboard>)aBillboard didReceivePurchase:(id<USPurchase>)aPurchase;
@end
