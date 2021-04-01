// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MinesweeperLibEd : ModuleRules
	{
		public MinesweeperLibEd(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"InputCore",
					"MainFrame",
					"AssetTools",
					"AppFramework",
					"PropertyEditor",
					"RHI",
					"RenderCore",
					"Projects"
					// "MinesweeperLibCore",
					// "MinesweeperLibUE4"
				}
			);
			PrivateDependencyModuleNames.AddRange(
				new[]
				{
					"UnrealEd",
					"Slate",
					"SlateCore",
					"EditorStyle"
				}
			);
		}
	}
}
