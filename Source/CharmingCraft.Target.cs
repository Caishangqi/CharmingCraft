// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharmingCraftTarget : TargetRules
{
	public CharmingCraftTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("CharmingCraft");
	}
}