// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class YigsoftSample : ModuleRules
{
    public YigsoftSample(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks", "GASCombatHelper", "GASUtils" });

    }
}
