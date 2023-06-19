// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MPCPP_PuzzlePlatformEditorTarget : TargetRules
{
	public MPCPP_PuzzlePlatformEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MPCPP_PuzzlePlatform");
	}
}
