// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharmingCraftEditorTarget : TargetRules
{
	public CharmingCraftEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("CharmingCraft");
	}
}