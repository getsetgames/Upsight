//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "UpsightPrivatePCH.h"
#include "CallbackDevice.h"

#if PLATFORM_IOS
#import <UpsightKit/UpsightKit.h>
#endif

#if PLATFORM_IOS

@interface UUpsightComponentDelegate <USBillboardDelegate>
-(UIViewController *)presentingViewControllerForBillboard:(id<USBillboard>)aBillboard;
@end

static UUpsightComponentDelegate* ucd;

@implementation UUpsightComponentDelegate

+(void)load
{
    if (!ucd)
    {
        ucd = [[UUpsightComponentDelegate alloc] init];
    }
}

-(id)init
{
    self = [super init];
    
    if (self)
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(applicationDidFinishLaunching:)
                                                     name:UIApplicationDidFinishLaunchingNotification
                                                   object:nil];
    }
    
    return self;
}

-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

-(void)applicationDidFinishLaunching:(NSNotification *)n
{
    NSDictionary *dLaunchOptionsUrl = n.userInfo[@"UIApplicationLaunchOptionsURLKey"];
    
    if (!dLaunchOptionsUrl)
    {
        [USPush registerForPushNotifications];
    }
}

-(UIViewController *)presentingViewControllerForBillboard:(id<USBillboard>)aBillboard
{
    UIViewController *topController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    while (topController.presentedViewController) {
        topController = topController.presentedViewController;
    }
    
    return topController;
}

@end

#endif

void UUpsightComponent::OnRegister()
{
	Super::OnRegister();
    
    FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddUObject(this, &UUpsightComponent::ApplicationRegisteredForRemoteNotifications_Handler);

    FCoreDelegates::ApplicationRegisteredForUserNotificationsDelegate.AddUObject(this, &UUpsightComponent::ApplicationRegisteredForUserNotificationsDelegate_Handler);
    
    FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.AddUObject(this, &UUpsightComponent::ApplicationFailedToRegisterForRemoteNotifications_Handler);
    
    FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddUObject(this, &UUpsightComponent::ApplicationReceivedRemoteNotification_Handler);
}

void UUpsightComponent::OnUnregister()
{
	Super::OnUnregister();
}

void UUpsightComponent::ApplicationRegisteredForUserNotificationsDelegate_Handler(int32 inInt)
{
#if PLATFORM_IOS
    UIUserNotificationSettings *notificationSettings = (UIUserNotificationSettings *)types;
    
    [USPush didRegisterUserNotificationSettings:notificationSettings];
#endif
}

void UUpsightComponent::ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token)
{
#if PLATFORM_IOS
    NSData* TokenData = [NSData dataWithBytes:Token.GetData() length:Token.Num()];
    
    [USPush registerPushToken:TokenData];
#endif
}

void UUpsightComponent::ApplicationFailedToRegisterForRemoteNotifications_Handler(FString RegisterError)
{
    UE_LOG(LogUpsight, Error, TEXT("ApplicationFailedToRegisterForRemoteNotifications: %s"), *RegisterError);
}

void UUpsightComponent::ApplicationReceivedRemoteNotification_Handler(FString Json)
{
#if PLATFORM_IOS
    [USPush pushBillboard].delegate = ucd;
    
    NSDictionary *userInfo = @{ @"message" : Json };
    
    [USPush handleRemoteNotificationWithUserInfo:userInfo];
#endif
    
    UE_LOG(LogUpsight, Log, TEXT("ApplicationReceivedRemoteNotification: %s"), *Json);
}

