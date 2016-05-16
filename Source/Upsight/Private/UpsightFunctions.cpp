//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "UpsightPrivatePCH.h"

#include "Android/AndroidJNI.h"
#include "AndroidApplication.h"

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

#if __OBJC__
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
#if PLATFORM_IOS

#endif
