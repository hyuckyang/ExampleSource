// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UE4PS : ModuleRules
{
	public UE4PS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // https://answers.unrealengine.com/questions/429455/link-errors-in-ubttasknode-classes.html 참조 . GameplayTasks 추가 안하면 에러 떨어짐.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "GameplayTasks" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
