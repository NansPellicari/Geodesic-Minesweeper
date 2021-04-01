// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class MinesweeperLibCore : ModuleRules
	{
		public MinesweeperLibCore(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
				new[]
				{
					"Core",
					"CoreUObject",
					"NansCoreHelpers"
					// ... add other public dependencies that you statically link with here ...
				}
			);
		}
	}
}
