// BGAT studio. All Rights Reserved. 

using UnrealBuildTool;
using System.Collections.Generic;

public class STUFEditorTarget : TargetRules
{
	public STUFEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "STUF" } );
	}
}
