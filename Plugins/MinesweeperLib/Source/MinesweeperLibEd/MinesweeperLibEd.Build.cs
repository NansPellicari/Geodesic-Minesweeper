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
					"Core"
					// ... add other public dependencies that you statically link with here ...
				}
			);
		}
	}
}
