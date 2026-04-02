// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FFTest : ModuleRules
{
	public FFTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate",
			"MassEntity",
			"MassCommon",
			"MassMovement",
			"MassActors",
			"MassSpawner",
			"MassAIBehavior",
			"MassNavigation",
			"MassSignals",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] {
			"FFTest",
			"FFTest/Variant_Strategy",
			"FFTest/Variant_Strategy/UI",
			"FFTest/Variant_TwinStick",
			"FFTest/Variant_TwinStick/AI",
			"FFTest/Variant_TwinStick/Gameplay",
			"FFTest/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
