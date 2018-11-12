// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowTo_PlayerInputTarget : TargetRules
{
	public HowTo_PlayerInputTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "HowTo_PlayerInput" } );
	}
}
