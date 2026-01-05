// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSystem/Tools/TerminalHackDevice.h"
#include "MinigameSystem/MinigameWidgetBase.h"

void ATerminalHackDevice::StartTool()
{
	Super::StartTool();
}

void ATerminalHackDevice::InitializeMinigame(UMinigameBase* Minigame)
{
	Super::InitializeMinigame(Minigame);
	
	MinigameInstance->MinigameWidgetClass = MinigameWidgetClass;
}

void ATerminalHackDevice::OnMinigameStateChanged(EMinigameState NewState)
{
	Super::OnMinigameStateChanged(NewState);
}

void ATerminalHackDevice::OnMinigameFinished(EMinigameState FinalState)
{
	Super::OnMinigameFinished(FinalState);
}
