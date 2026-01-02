// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSystem/Tools/TerminalHackDevice.h"
#include "MinigameSystem/MinigameWidgetBase.h"

void ATerminalHackDevice::StartTool()
{
	Super::StartTool();
}

void ATerminalHackDevice::InitializeMinigame(UMinigameBase* minigame)
{
	Super::InitializeMinigame(minigame);
	
	MinigameInstance->MinigameWidgetClass = MinigameWidgetClass;
}
