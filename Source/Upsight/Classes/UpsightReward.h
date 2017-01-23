//
//  Created by Robert Segal on 2017-01-23.
//  Copyright (c) 2017 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UpsightReward.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UUpsightReward : public UObject
{
    GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, meta = (Keywords = "upsight analytics"), Category = "Upsight")
	FString	Name;

	UPROPERTY(EditAnywhere, meta = (Keywords = "upsight analytics"), Category = "Upsight")
	int	Quantity;

	UPROPERTY(EditAnywhere, meta = (Keywords = "upsight analytics"), Category = "Upsight")
	FString	SignatureData;

	UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
	FORCEINLINE FString GetName() { return Name; };

	UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
	FORCEINLINE int GetQuantity() { return Quantity; };

	UFUNCTION(BlueprintCallable, meta = (Keywords = "upsight analytics"), Category = "Upsight")
	FORCEINLINE FString GetSignatureData() { return SignatureData; };
};
