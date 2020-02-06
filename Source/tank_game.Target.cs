// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class tank_gameTarget : TargetRules
{
	public tank_gameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;


		ExtraModuleNames.AddRange( new string[] { "tank_game" } );
	}
}
