// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KillerWave : ModuleRules
{
	public KillerWave(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MIDIDevice" });
        PrivateDependencyModuleNames.AddRange(new string[] { "MIDIDevice" });
        PrivateIncludePathModuleNames.AddRange(new string[] { "MIDIDevice" });
        PublicIncludePathModuleNames.AddRange(new string[] { "MIDIDevice" });

    }
}
