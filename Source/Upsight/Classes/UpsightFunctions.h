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
};
