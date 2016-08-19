//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UpsightSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UUpsightSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UUpsightSettings(const FObjectInitializer& ObjectInitializer);
	
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Application Token"))
    FString ApplicationToken;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Public Key"))
    FString PublicKey;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Include Analytics"))
    bool IncludeAnalytics;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Include Managed Variables"))
    bool IncludeManagedVariables;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Include Marketing"))
    bool IncludeMarketing;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Include Advertising ID"))
    bool IncludeAdvertisingId;
};
