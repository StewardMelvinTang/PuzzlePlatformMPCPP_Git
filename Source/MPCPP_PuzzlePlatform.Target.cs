// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MPCPP_PuzzlePlatformTarget : TargetRules
{
	public MPCPP_PuzzlePlatformTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MPCPP_PuzzlePlatform");
	}
}
