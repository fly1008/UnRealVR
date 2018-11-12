// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HowTo_PlayerInputEditorTarget : TargetRules
{
	public HowTo_PlayerInputEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "HowTo_PlayerInput" } );
	}
}
