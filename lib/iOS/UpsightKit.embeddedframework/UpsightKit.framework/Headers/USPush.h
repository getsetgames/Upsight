//
//  USPush.h
//  USPush
//
//  Created by Tolik Shevchenko on 12/11/14.
//  Copyright (c) 2014 - 2015 Upsight. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol USBillboard;

/** `USPush` class provides the ability to register for remote notifications sent through Apple
Push Notification Service.

To integrate push, you must:

1. Add the USBillboardDelegate protocol to your App Delegate and implement `presentingViewControllerForBillboard:`
1. Register for push by calling `[USPush registerForPushNotifications]` in your App Delegate's `didFinishLaunchingWithOptions:` method.
1. Call the USPush API method `didRegisterUserNotificationSettings:` in your App Delegate's `application:didRegisterUserNotificationSettings:` method.
1. Call the USPush API method `registerPushToken:` from `application:didRegisterForRemoteNotificationsWithDeviceToken:`
1. When a remote notification is received, set the USPush billboard's delegate to be your App Delegate class and call the USPush interface's `handleRemoteNotificationWithUserInfo:` method.
1. If you plan to start downloading content when a push notification arrives, which is referred to as "silent" push notifications, check 'Remote notifications' from the list of Background Modes in the Capabilities section of your target's settings.

Here is a sample AppDelegate implementation that properly integrates Push

	@interface AppDelegate () <USBillboardDelegate>
	@end
	
	@implementation AppDelegate	
	
	- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
	{
	    [Upsight setDefaultLogLevel:UpsightLoggerLevelDebug];
	
	    // Override point for customization after application launch.
	    [USPush registerForPushNotifications];
	    
	    return YES;
	}
	
	- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
	{
	    [USPush didRegisterUserNotificationSettings:notificationSettings];
	}
	
	- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
	{
	    [USPush registerPushToken:deviceToken];
	}
	
	- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
	{
	    [USPush pushBillboard].delegate = self;
	    [USPush handleRemoteNotificationWithUserInfo:userInfo];

        if (NULL != completionHandler) {
            completionHandler(UIBackgroundFetchResultNoData);
        }
	}
	
	#pragma mark - Billboard delegate
	
	- (UIViewController *)presentingViewControllerForBillboard:(id<USBillboard>)aBillboard
	{
	    UIViewController *topController = [UIApplication sharedApplication].keyWindow.rootViewController;
	    
	    while (topController.presentedViewController) {
	        topController = topController.presentedViewController;
	    }
	    
	    return topController;
	}
	
	@end
*/
@interface USPush : NSObject

/** Starts the push notification registration procedure. This method should be called from your
implementation of App Delegate `didFinishLaunchingWithOptions:` method. Shortly after this
call the system should invoke your App Delegate's `application:didRegisterUserNotificationSettings:`
method to pass the settings the user has granted to the application. Your implementation of that
method must forward the settings to <[USPush didRegisterUserNotificationSettings:]> to continue
the registration procedure.
*/
+ (void)registerForPushNotifications;

/** Unregisters the application from receiving remote notifications.*/
+ (void)unregisterForPushNotifications;

/** This method should be called from your implementation of `application:didRegisterForRemoteNotificationsWithDeviceToken:`
application delegate method to complete the registration procedure.

@param aToken A device token passed by the system to the application delegate.
*/
+ (void)registerPushToken:(NSData *)aToken;

/** Call this method from your implementation of `application:didRegisterUserNotificationSettings:`
application delegate method to continue the registration procedure after the user confirmed the
types of notifications that can be received by the app.

@param aNotificationSettings Settings the user has granted to the application.
*/
+ (void)didRegisterUserNotificationSettings:(UIUserNotificationSettings *)aNotificationSettings;

/** Call this method from your implementation of `application:didReceiveRemoteNotification:`
application delegate method to let the receiver process a notification.

@param aUserInfo A dictionary that contains information related to the remote notification
that is passed from the system to your application delegate.
*/
+ (void)handleRemoteNotificationWithUserInfo:(NSDictionary *)aUserInfo;
+ (void)extractMessageID:(NSNumber **)messageID campaignID:(NSNumber **)campaignID userInfo:(NSDictionary *)aUserInfo;

/** Push notifications sent from Upsight Dashboard can be associated with different content,
such as announcement, virtual goods promotion, etc. A push billboard is used to present
contents associated with a push notification when users navigates to your app by tapping on
the push notification banner.

To be able to see pushed content in your app you must implement required method from <USBillboardDelegate>
protocol and assign a delegate to the billboard.
*/
+ (id<USBillboard>)pushBillboard;

@end
