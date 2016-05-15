//
//  Created by Robert Segal on 2016-02-04.
//  Copyright (c) 2015 Get Set Games Inc. All rights reserved.
//

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class Upsight : ModuleRules
	{
		public Upsight(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Upsight/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine"
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
				);
				
			PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"Settings"
			}
			);


			if (Target.Platform == UnrealTargetPlatform.IOS) {
				PublicAdditionalFrameworks.Add( 
					new UEBuildFramework( 
						"UpsightKit",
						"../../lib/iOS/UpsightKit.embeddedframework.zip"
					)
				); 

				PublicFrameworks.AddRange( 
					new string[] 
					{ 
						"CoreData",
						"SystemConfiguration",
						"CoreTelephony",
						"AdSupport"
					}
				);
			}
			else if(Target.Platform == UnrealTargetPlatform.Android)
			{
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "Upsight_APL.xml")));
			}
		}
	}
}
