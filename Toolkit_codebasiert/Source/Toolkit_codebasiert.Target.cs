// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Toolkit_codebasiertTarget : TargetRules
{
	public Toolkit_codebasiertTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Toolkit_codebasiert" } );
	}
}
