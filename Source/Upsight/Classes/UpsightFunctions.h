//
//  Created by Derek van Vliet on 2014-12-10.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UpsightFunctions.generated.h"

UCLASS(NotBlueprintable)
class UUpsightFunctions : public UObject {
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static void UpsightRecordAnalyticsEventWithName(FString eventName, TArray<FString> eventKeys, TArray<FString> eventValues);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static void UpsightRecordMilestoneEventForScope(FString scope, TArray<FString> eventKeys, TArray<FString> eventValues);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static void UpsightRecordMonetizationEvent(int resolution, FString productID, int quantity, FString currency, float price, TArray<FString> keys, TArray<FString> values);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static void UpsightRecordMonetizationEventWithTotalPrice(int resolution, FString productID,  int quantity, FString currency, float price, float totalPrice, TArray<FString> keys, TArray<FString> values);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static void UpsightRecordInAppPurchaseEventWithResolution(int resolution, FString productID, int quantity, FString currency, float price, float totalPrice, FString store, FString bundle, FString transactionIdentifier, TArray<FString> keys, TArray<FString> values);

    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static bool UpsightClientValidateInAppPurchase(FString receiptData);
    
};
