//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "UpsightSettings.h"
#include "UpsightPrivatePCH.h"

UUpsightSettings::UUpsightSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer),
ApplicationToken(""),
PublicKey(""),
IncludeAnalytics(false),
IncludeManagedVariables(false),
IncludeMarketing(false),
IncludeAdvertisingId(false),
IncludePushNotifications(false),
PushNotificationSenderID(""),
EnableLogging(false)
{
}
