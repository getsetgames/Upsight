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
    if (Keys.Num() != Values.Num())
    {
        return false;
    }
    
    return true;
}

#if PLATFORM_IOS
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

#if PLATFORM_ANDROID
void CreateJavaKeyValueArrays(JNIEnv *Env, jobjectArray &jKeysArray, jobjectArray &jValuesArray, TArray<FString> keys, TArray<FString> values)
{
    for (uint32 Param = 0; Param < keys.Num(); Param++)
    {
        jstring StringValue = Env->NewStringUTF(TCHAR_TO_UTF8(*keys[Param]));
        
        Env->SetObjectArrayElement(jKeysArray, Param, StringValue);
        Env->DeleteLocalRef(StringValue);
        
        StringValue = Env->NewStringUTF(TCHAR_TO_UTF8(*values[Param]));
        
        Env->SetObjectArrayElement(jValuesArray, Param, StringValue);
        Env->DeleteLocalRef(StringValue);
    }
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
        UE_LOG(LogUpsight, Log, TEXT("UUpsightFunctions::UpsightRecordAnalyticsEventWithName - event: %s"), *eventName);
        
        if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
        {
            static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                               FJavaWrapper::GameActivityClassID,
                                                               "AndroidThunkJava_UpsightRecordAnalyticsEventWithName",
                                                               "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V",
                                                               false);
            
            jobjectArray jKeys   = (jobjectArray)Env->NewObjectArray(eventKeys.Num(),   FJavaWrapper::JavaStringClass, NULL);
            jobjectArray jValues = (jobjectArray)Env->NewObjectArray(eventValues.Num(), FJavaWrapper::JavaStringClass, NULL);
            
            CreateJavaKeyValueArrays(Env, jKeys, jValues, eventKeys, eventValues);
            
            jstring jEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*eventName));
            
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jEventName, jKeys, jValues);
            
            Env->DeleteLocalRef(jKeys);
            Env->DeleteLocalRef(jValues);
            Env->DeleteLocalRef(jEventName);
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
        UE_LOG(LogUpsight, Log, TEXT("UUpsightFunctions::UpsightRecordMilestoneEventForScope - scope: %s"), *scope);
        
        if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
        {
            static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                               FJavaWrapper::GameActivityClassID,
                                                               "AndroidThunkJava_UpsightRecordMilestoneEventForScope",
                                                               "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V",
                                                               false);

            jobjectArray jKeys   = (jobjectArray)Env->NewObjectArray(eventKeys.Num(),   FJavaWrapper::JavaStringClass, NULL);
            jobjectArray jValues = (jobjectArray)Env->NewObjectArray(eventValues.Num(), FJavaWrapper::JavaStringClass, NULL);
            
            CreateJavaKeyValueArrays(Env, jKeys, jValues, eventKeys, eventValues);
            
            jstring jEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*scope));
            
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jEventName, jKeys, jValues);
            
            Env->DeleteLocalRef(jKeys);
            Env->DeleteLocalRef(jValues);
            Env->DeleteLocalRef(jEventName);
        }
#endif
    }
    else
    {
        UE_LOG(LogUpsight, Log, TEXT("keys and/or value arguments are empty or nil"));
    }
}

void UUpsightFunctions::UpsightRecordMonetizationEvent(int resolution, FString productID, int quantity, FString currency, float price, TArray<FString> keys, TArray<FString> values)
{
#if PLATFORM_IOS
    NSDictionary *p = CreateNSDictionary(keys, values);
    
    [Upsight recordMonetizationEventWithResolution:(USPurchaseResolution)resolution
                                          currency:currency.GetNSString()
                                          quantity:quantity
                                           product:productID.GetNSString()
                                             price:price
                                        properties:p];

#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_UpsightRecordMonetizationEvent",
                                                           "(ILjava/lang/String;ILjava/lang/String;F[Ljava/lang/String;[Ljava/lang/String;)V",
                                                           false);

        jobjectArray jKeys   = (jobjectArray)Env->NewObjectArray(keys.Num(),   FJavaWrapper::JavaStringClass, NULL);
        jobjectArray jValues = (jobjectArray)Env->NewObjectArray(values.Num(), FJavaWrapper::JavaStringClass, NULL);
        
        CreateJavaKeyValueArrays(Env, jKeys, jValues, keys, values);
        
        jint     jResolution = (jint)resolution;
        jstring  jProductID  = Env->NewStringUTF(TCHAR_TO_UTF8(*productID));
        jint     jQuantity   = (jint)quantity;
        jstring  jCurrency   = Env->NewStringUTF(TCHAR_TO_UTF8(*currency));
        jfloat   jPrice      = (jfloat)price;
        
        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jResolution, jProductID, jQuantity, jCurrency, jPrice, jKeys, jValues);
        
        Env->DeleteLocalRef(jKeys);
        Env->DeleteLocalRef(jValues);
        
        Env->DeleteLocalRef(jProductID);
        Env->DeleteLocalRef(jCurrency);
    }
#endif
}

void UUpsightFunctions::UpsightRecordMonetizationEventWithTotalPrice(int resolution, FString productID, int quantity, FString currency, float price, float totalPrice, TArray<FString> keys, TArray<FString> values)
{
#if PLATFORM_IOS
    NSDictionary *p = CreateNSDictionary(keys, values);
    
    [Upsight recordMonetizationEventWithResolution:(USPurchaseResolution)resolution totalPrice:totalPrice currency:currency.GetNSString() product:productID.GetNSString() properties:p];
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_UpsightRecordMonetizationEventWithTotalPrice",
                                                           "(ILjava/lang/String;ILjava/lang/String;FF[Ljava/lang/String;[Ljava/lang/String;)V",
                                                           false);

        jobjectArray jKeys   = (jobjectArray)Env->NewObjectArray(keys.Num(),   FJavaWrapper::JavaStringClass, NULL);
        jobjectArray jValues = (jobjectArray)Env->NewObjectArray(values.Num(), FJavaWrapper::JavaStringClass, NULL);
        
        CreateJavaKeyValueArrays(Env, jKeys, jValues, keys, values);

        jint     jResolution = (jint)resolution;
        jstring  jProductID  = Env->NewStringUTF(TCHAR_TO_UTF8(*productID));
        jint     jQuantity   = (jint)quantity;
        jstring  jCurrency   = Env->NewStringUTF(TCHAR_TO_UTF8(*currency));
        jfloat   jPrice      = (jfloat)price;
        jfloat   jTotalPrice = (jfloat)totalPrice;

        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jResolution, jProductID, jQuantity, jCurrency, jPrice, jTotalPrice, jKeys, jValues);
        
        Env->DeleteLocalRef(jKeys);
        Env->DeleteLocalRef(jValues);
        
        Env->DeleteLocalRef(jProductID);
        Env->DeleteLocalRef(jCurrency);
    }
#endif
}

void UUpsightFunctions::UpsightRecordInAppPurchaseEventWithResolution(int resolution, FString productID, int quantity, FString currency, float price, float totalPrice, FString store, FString bundle, FString transactionIdentifier, TArray<FString> keys, TArray<FString> values)
{
     UE_LOG(LogUpsight, Log, TEXT("UpsightRecordInAppPurchaseEventWithResolution - resolution: %d, productId: %s, quantity: %d, currency: %s, price: %f, totalPrice: %f, store: %s, bundle: %s, transactionId: %s"), resolution, *productID, quantity, *currency, price, totalPrice, *store, *bundle, *transactionIdentifier);

#if PLATFORM_IOS
    NSDictionary *p = CreateNSDictionary(keys, values);
    
    NSString *nsProductId     = productID.GetNSString();
    NSString *nsCurrencyId    = currency.GetNSString();
    NSString *nsTransactionId = transactionIdentifier.GetNSString();
    
    [Upsight recordInAppPurchaseEventWithResolution:(USPurchaseResolution)resolution
                                            product:nsProductId
                                           quantity:quantity
                                              price:price
                                           currency:nsCurrencyId
                              transactionIdentifier:nsTransactionId
                                         properties:p];
    
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_UpsightRecordInAppPurchaseEvent",
                                                           "(ILjava/lang/String;ILjava/lang/String;FFLjava/lang/String;Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V",
                                                           false);

        jobjectArray jKeys   = (jobjectArray)Env->NewObjectArray(keys.Num(),   FJavaWrapper::JavaStringClass, NULL);
        jobjectArray jValues = (jobjectArray)Env->NewObjectArray(values.Num(), FJavaWrapper::JavaStringClass, NULL);
        
        CreateJavaKeyValueArrays(Env, jKeys, jValues, keys, values);
        
        jint    jResolution = (jint)resolution;
        jstring jProductID  = Env->NewStringUTF(TCHAR_TO_UTF8(*productID));
        jint    jQuantity   = (jint)quantity;
        jstring jCurrency   = Env->NewStringUTF(TCHAR_TO_UTF8(*currency));
        jfloat  jPrice      = (jfloat)price;
        jfloat  jTotalPrice = (jfloat)totalPrice;
        jstring jStore      = Env->NewStringUTF(TCHAR_TO_UTF8(*store));
        jstring jBundle     = Env->NewStringUTF(TCHAR_TO_UTF8(*bundle));

        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jResolution, jProductID, jQuantity, jCurrency, jPrice, jTotalPrice, jStore, jBundle, jKeys, jValues);
        
        Env->DeleteLocalRef(jKeys);
        Env->DeleteLocalRef(jValues);
        
        Env->DeleteLocalRef(jStore);
        Env->DeleteLocalRef(jBundle);
        Env->DeleteLocalRef(jProductID);
        Env->DeleteLocalRef(jCurrency);
    }
#endif
}

void UUpsightFunctions::UpsightRegisterForPushNotifications()
{
#if PLATFORM_IOS
    [USPush registerForPushNotifications];
#endif
}




