// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MPCPP_PuzzlePlatform : ModuleRules
{
	public MPCPP_PuzzlePlatform(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
