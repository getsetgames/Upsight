//
//  Created by Robert Segal on 2014-04-01.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "UpsightPrivatePCH.h"
#include "UpsightSettings.h"
#include "ISettingsModule.h"

DEFINE_LOG_CATEGORY(LogUpsight);

#define LOCTEXT_NAMESPACE "Upsight"

class FUpsight : public IUpsight
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FUpsight, Upsight )

void FUpsight::StartupModule()
{
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Upsight",
										 LOCTEXT("RuntimeSettingsName", "Upsight"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the Upsight plugin"),
										 GetMutableDefault<UUpsightSettings>()
										 );
	}
}


void FUpsight::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
