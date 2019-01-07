// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Toolkit_codebasiertEditorTarget : TargetRules
{
	public Toolkit_codebasiertEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Toolkit_codebasiert" } );
	}
}
