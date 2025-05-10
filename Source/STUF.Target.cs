// BGAT studio. All Rights Reserved. 

using UnrealBuildTool;
using System.Collections.Generic;

public class STUFTarget : TargetRules
{
	public STUFTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "STUF" } );
	}
}
