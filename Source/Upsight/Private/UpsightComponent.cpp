//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "UpsightPrivatePCH.h"
#include "CallbackDevice.h"

#if PLATFORM_IOS
#import <UpsightKit/UpsightKit.h>
#endif


UUpsightComponent::FUpsightBillboardDidDismissDelegate                    UUpsightComponent::BillboardDidDismissDelegate;
UUpsightComponent::FUpsightBillboardWillDismissDelegate                   UUpsightComponent::BillboardWillDismissDelegate;
UUpsightComponent::FUpsightBillboardDidAppearDelegate                     UUpsightComponent::BillboardDidAppearDelegate;
UUpsightComponent::FUpsightBillboardWillAppearDelegate                    UUpsightComponent::BillboardWillAppearDelegate;


#if PLATFORM_IOS

@interface UUpsightComponentDelegate : NSObject<USBillboardDelegate>
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
        // [RS] - TBD - There is an engine issue with registering for push notifications in applicationDidFinishLaunching currently
        //
        // [USPush registerForPushNotifications];
    }
}

-(UIViewController *)presentingViewControllerForBillboard:(id<USBillboard>)aBillboard
{
    UIViewController *topController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    while (topController.presentedViewController)
    {
        topController = topController.presentedViewController;
    }
    
    return topController;
}

@end

#endif

void UUpsightComponent::OnRegister()
{
	Super::OnRegister();
    
    const UUpsightSettings* settings = GetDefault<UUpsightSettings>();
    
    if (settings->IncludePushNotifications)
    {
        FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddUObject(this, &UUpsightComponent::ApplicationRegisteredForRemoteNotifications_Handler);
        FCoreDelegates::ApplicationRegisteredForUserNotificationsDelegate.AddUObject(this, &UUpsightComponent::ApplicationRegisteredForUserNotificationsDelegate_Handler);
        FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.AddUObject(this, &UUpsightComponent::ApplicationFailedToRegisterForRemoteNotifications_Handler);
        FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddUObject(this, &UUpsightComponent::ApplicationReceivedRemoteNotification_Handler);
    }
}

void UUpsightComponent::OnUnregister()
{
	Super::OnUnregister();
    
    const UUpsightSettings* settings = GetDefault<UUpsightSettings>();
    
    if (settings->IncludePushNotifications)
    {
        FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.RemoveAll(this);
        FCoreDelegates::ApplicationRegisteredForUserNotificationsDelegate.RemoveAll(this);
        FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.RemoveAll(this);
        FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.RemoveAll(this);
    }
void UUpsightComponent::BillboardDidAppearDelegate_Handler(const FString& scope)
{
    BillboardDidAppearDelegate.Broadcast(scope);
}

void UUpsightComponent::BillboardWillAppearDelegate_Handler(const FString& scope)
{
    BillboardWillAppearDelegate.Broadcast(scope);
}

void UUpsightComponent::BillboardDidDismissDelegate_Handler(const FString& scope)
{
    BillboardDidDismissDelegate.Broadcast(scope);
}

void UUpsightComponent::BillboardWillDismissDelegate_Handler(const FString& scope)
{
    BillboardWillDismissDelegate.Broadcast(scope);
}

}

void UUpsightComponent::ApplicationRegisteredForUserNotificationsDelegate_Handler(int32 inInt)
{
#if PLATFORM_IOS
    NSUInteger t = [[NSNumber numberWithInt:inInt] unsignedIntegerValue];
    
    UIUserNotificationSettings *s = [UIUserNotificationSettings settingsForTypes:t categories:nil];
    
    [USPush didRegisterUserNotificationSettings:s];
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
    if (Json.Len())
    {
        NSError      *error;
        NSData       *data = [Json.GetNSString() dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *d    = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
    
        if (!error)
        {
            [USPush pushBillboard].delegate = ucd;
            [USPush handleRemoteNotificationWithUserInfo:d];
        }
        else
        {
            //UE_LOG(LogUpsight, Log, TEXT("Error parsing JSON data: %s"), error);
        }
    }
#endif
    
    UE_LOG(LogUpsight, Log, TEXT("ApplicationReceivedRemoteNotification: %s"), *Json);
}

