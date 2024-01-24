// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEHandDemo : ModuleRules
{
	public UEHandDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent",
			"GeometryFramework",
			"GeometryCore",
			"DynamicMesh"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
 
	}
}