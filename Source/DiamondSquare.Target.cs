// Copyright (c) 2017, Vadim Petrov - MIT License

using UnrealBuildTool;
using System.Collections.Generic;

public class DiamondSquareTarget : TargetRules
{
	public DiamondSquareTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "DiamondSquare" } );
	}
}
