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

int validateData(const void* data, const int dataLength, unsigned char bID[128], unsigned char bVersion[16], void **dOpaque, void **dHash)
{
    // iOS receipt validation based off code detailed at https://www.objc.io/issues/17-security/receipt-validation/
    //
    
    char isValid = 0;
    
    
    return isValid;
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

bool UUpsightFunctions::UpsightClientValidateInAppPurchase(FString receiptData)
{
#if PLATFORM_IOS
    unsigned char bundleId[128]     = { 0 };
    unsigned char bundleVersion[16] = { 0 };
    
    void *opaque = NULL;
    void *hash   = NULL;
    
    NSString *receipt = receiptData.GetNSString();
    
    const int result = validateData([receipt bytes], (int)[receipt length], bundleId, bundleVersion, &opaque, &hash);
    return result == 0;
#else
    return true;
#endif
}


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
        
        jint    jResolution = (jint)resolution;
        jstring jProductID  = Env->NewStringUTF(TCHAR_TO_UTF8(*productID));
        jint    jQuantity   = (jint)quantity;
        jstring jCurrency   = Env->NewStringUTF(TCHAR_TO_UTF8(*currency));
        jfloat  jPrice      = (jfloat)price;
        
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

        jint    jResolution = (jint)resolution;
        jstring jProductID  = Env->NewStringUTF(TCHAR_TO_UTF8(*productID));
        jint    jQuantity   = (jint)quantity;
        jstring jCurrency   = Env->NewStringUTF(TCHAR_TO_UTF8(*currency));
        jfloat  jPrice      = (jfloat)price;
        jfloat  jTotalPrice = (jfloat)totalPrice;

        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jResolution, jProductID, jQuantity, jCurrency, jPrice, jTotalPrice, jKeys, jValues);
        
        Env->DeleteLocalRef(jKeys);
        Env->DeleteLocalRef(jValues);
        Env->DeleteLocalRef(jProductID);
        Env->DeleteLocalRef(jCurrency);
    }
#endif
}

void UUpsightFunctions::UpsightRecordInAppPurchaseEventWithResolution(int resolution, FString productID, int quantity, FString currency, float price, FString bundle, FString transactionIdentifier, TArray<FString> keys, TArray<FString> values)
{
#if PLATFORM_IOS
    NSDictionary *p = CreateNSDictionary(keys, values);
    
    [Upsight recordInAppPurchaseEventWithResolution:(USPurchaseResolution)resolution
                                            product:productID.GetNSString()
                                           quantity:quantity
                                              price:price
                                           currency:currency.GetNSString()
                              transactionIdentifier:transactionIdentifier.GetNSString()
                                         properties:p];
    
#elif PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        static jmethodID Method = FJavaWrapper::FindMethod(Env,
                                                           FJavaWrapper::GameActivityClassID,
                                                           "AndroidThunkJava_UpsightRecordInAppPurchaseEvent",
                                                           "(ILjava/lang/String;ILjava/lang/String;FLjava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V",
                                                           false);
        
        jobjectArray jKeys   = (jobjectArray)Env->NewObjectArray(keys.Num(),   FJavaWrapper::JavaStringClass, NULL);
        jobjectArray jValues = (jobjectArray)Env->NewObjectArray(values.Num(), FJavaWrapper::JavaStringClass, NULL);
        
        CreateJavaKeyValueArrays(Env, jKeys, jValues, keys, values);
        
        jint    jResolution = (jint)resolution;
        jstring jProductID  = Env->NewStringUTF(TCHAR_TO_UTF8(*productID));
        jint    jQuantity   = (jint)quantity;
        jstring jCurrency   = Env->NewStringUTF(TCHAR_TO_UTF8(*currency));
        jfloat  jPrice      = (jfloat)price;
        jstring jBundle     = Env->NewStringUTF(TCHAR_TO_UTF8(*bundle));

        FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, jResolution, jProductID, jQuantity, jCurrency, jPrice, jBundle, jKeys, jValues);
        
        Env->DeleteLocalRef(jKeys);
        Env->DeleteLocalRef(jValues);
        
        Env->DeleteLocalRef(jBundle);
        Env->DeleteLocalRef(jProductID);
        Env->DeleteLocalRef(jCurrency);
    }
#endif
}




