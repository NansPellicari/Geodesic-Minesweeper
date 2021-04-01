// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MinesweeperEditorTarget : TargetRules
{
	public MinesweeperEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"Minesweeper", "MinesweeperLibEd"});
	}
}
