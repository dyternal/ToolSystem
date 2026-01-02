// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSystem/Tools/ElectricalFixDevice.h"
#include "MinigameSystem/MinigameWidgetBase.h"

void AElectricalFixDevice::StartTool()
{
	Super::StartTool();
	
}

void AElectricalFixDevice::InitializeMinigame(UMinigameBase* minigame)
{
	Super::InitializeMinigame(MinigameInstance);
	
	MinigameInstance->MinigameWidgetClass = MinigameWidgetClass;
}
