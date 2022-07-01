// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Candy : ModuleRules
{
	public Candy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
