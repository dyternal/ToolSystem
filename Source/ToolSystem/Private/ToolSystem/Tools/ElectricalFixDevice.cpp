// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSystem/Tools/ElectricalFixDevice.h"
#include "MinigameSystem/MinigameWidgetBase.h"

void AElectricalFixDevice::StartTool()
{
	Super::StartTool();
	
}

void AElectricalFixDevice::InitializeMinigame(UMinigameBase* Minigame)
{
	Super::InitializeMinigame(Minigame);
	MinigameInstance->MinigameWidgetClass = MinigameWidgetClass;
}


void AElectricalFixDevice::OnMinigameStateChanged(EMinigameState NewState)
{
	Super::OnMinigameStateChanged(NewState);
}

void AElectricalFixDevice::OnMinigameFinished(EMinigameState FinalState)
{
	Super::OnMinigameFinished(FinalState);
}
