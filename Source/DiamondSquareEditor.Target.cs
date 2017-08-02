// Copyright (c) 2017, Vadim Petrov - MIT License

using UnrealBuildTool;
using System.Collections.Generic;

public class DiamondSquareEditorTarget : TargetRules
{
	public DiamondSquareEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "DiamondSquare" } );
	}
}
