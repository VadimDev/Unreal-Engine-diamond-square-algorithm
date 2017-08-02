// Copyright (c) 2017, Vadim Petrov - MIT License

using UnrealBuildTool;

public class DiamondSquare : ModuleRules
{
	public DiamondSquare(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.Default;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
