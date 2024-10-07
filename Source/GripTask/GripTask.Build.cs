// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GripTask : ModuleRules
{
	public GripTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
