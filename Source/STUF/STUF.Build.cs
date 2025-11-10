// BGAT studio. All Rights Reserved. 

using UnrealBuildTool;

public class STUF : ModuleRules
{
	public STUF(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
            "GameplayTasks",
            "NavigationSystem",
            "PhysicsCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] { 
			"STUF/Public/Player", 
			"STUF/Public/Components", 
			"STUF/Public/Dev",
            "STUF/Public/Weapon",
            "STUF/Public/UI",
            "STUF/Public/Animations",
            "STUF/Public/Pickups",
            "STUF/Public/Weapon/Components",
            "STUF/Public/AI",
            "STUF/Public/AI/Tasks",
            "STUF/Public/AI/EQS",
            "STUF/Public/AI/Decorators"

                                                 });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
