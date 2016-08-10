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
    static void UpsightTrackPurchase(int resolution, FString productID,  int quantity, FString currency, float price, TArray<FString> eventKeys, TArray<FString> eventValues);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
    static void UpsightTrackPurchaseWithTransactionID(int resolution, FString productID, int quantity, float price, FString currency, FString transactionId, TArray<FString> eventKeys, TArray<FString> eventValues);
};
