//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "UpsightFunctions.h"
#include "UpsightComponent.generated.h"

UCLASS(ClassGroup=Advertising, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UUpsightComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	void OnRegister() override;
	void OnUnregister() override;
	
private:
    void ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token);
    void ApplicationRegisteredForUserNotificationsDelegate_Handler(int32 inInt);
    void ApplicationFailedToRegisterForRemoteNotifications_Handler(FString RegisterError);
    void ApplicationReceivedRemoteNotification_Handler(FString Json);

};
