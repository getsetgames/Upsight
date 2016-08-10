//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "UpsightPrivatePCH.h"

#if PLATFORM_IOS
#import <UpsightKit/UpsightKit.h>
#elif PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"
#endif

bool ValidateValues(TArray<FString> &Keys, TArray<FString> &Values)
{
    const int32 kNumKeys   = Keys.Num();
    const int32 kNumValues = Values.Num();
    
    if (kNumKeys == 0 || kNumValues == 0)
    {
        return false;
    }
    
    if (kNumKeys != kNumValues)
    {
        return false;
    }
    
    return true;
}

#if __OBJC__
NSDictionary* CreateNSDictionary(TArray<FString> &Keys, TArray<FString> &Values)
{
    const int32 kNumKeys = Keys.Num();
    
    NSMutableDictionary* d = [NSMutableDictionary dictionaryWithCapacity:kNumKeys];
    
    for (uint32 i = 0; i < kNumKeys; i++)
    {
        FString &k = Keys[i];
        FString &v = Values[i];
        
        d[k.GetNSString()] = v.GetNSString();
    }
    
    return d;
}
#endif

void UUpsightFunctions::UpsightRecordAnalyticsEventWithName(FString eventName, TArray<FString> eventKeys, TArray<FString> eventValues)
{
    if ( ValidateValues(eventKeys, eventValues) )
    {
#if PLATFORM_IOS
        NSDictionary *p = CreateNSDictionary(eventKeys, eventValues);
    
        [Upsight recordAnalyticsEventWithName:eventName.GetNSString() properties: p];
    
#elif PLATFORM_ANDROID
        if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
        {
            static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                               FJavaWrapper::GameActivityClassID,
                                                               "AndroidThunkJava_UpsightRecordAnalyticsEventWithName",
                                                               "()Ljava/lang/String;[java/lang/String;[java/lang/String;",
                                                               false);
            
            FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
        }
#endif
    }
    else
    {
        UE_LOG(LogUpsight, Log, TEXT("keys and/or value arguments are empty or nil"));
    }
}

void UUpsightFunctions::UpsightRecordMilestoneEventForScope(FString scope, TArray<FString> eventKeys, TArray<FString> eventValues)
{
    if ( ValidateValues(eventKeys, eventValues) )
    {
#if PLATFORM_IOS
        NSDictionary *p = CreateNSDictionary(eventKeys, eventValues);
    
        [Upsight recordMilestoneEventForScope:scope.GetNSString() properties:p];
    
#elif PLATFORM_ANDROID
        
        if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
        {
            static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                               FJavaWrapper::GameActivityClassID,
                                                               "AndroidThunkJava_UpsightRecordMilestoneEventForScope",
                                                               "()Ljava/lang/String;[java/lang/String;[java/lang/String;",
                                                               false);
            
            FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
        }
#endif
    }
    else
    {
        UE_LOG(LogUpsight, Log, TEXT("keys and/or value arguments are empty or nil"));
    }
}

void UUpsightFunctions::UpsightTrackPurchase(int resolution, FString productID,  int quantity, FString currency, float price, TArray<FString> keys, TArray<FString> values)
{
#if PLATFORM_IOS
    NSDictionary *p = CreateNSDictionary(keys, values);
    
    
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_UpsightTrackPurchase",
                                                           "",
                                                           false);
        
        FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
    }
#endif
}

void UUpsightFunctions::UpsightTrackPurchaseWithTransactionID(int resolution, FString productID, int quantity, float price, FString currency, FString transactionIdentifier, TArray<FString> keys, TArray<FString> values)
{
#if PLATFORM_IOS
    NSDictionary *p = CreateNSDictionary(keys, values);
    
    
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_UpsightTrackPurchaseWithTransactionID",
                                                           "",
                                                           false);
        
        FJavaWrapper::CallObjectMethod(Env, FJavaWrapper::GameActivityThis, Method);
    }
#endif
}



