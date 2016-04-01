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
	
};
