// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MinesweeperLibUE4 : ModuleRules
	{
		public MinesweeperLibUE4(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					"Slate",
					"SlateCore",
					"InputCore",
					"EditorStyle",
					"NansCoreHelpers",
					"MinesweeperLibCore"
					// ... add other public dependencies that you statically link with here ...
				}
			);
		}
	}
}
