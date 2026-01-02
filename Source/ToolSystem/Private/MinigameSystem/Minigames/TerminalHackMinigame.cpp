// Fill out your copyright notice in the Description page of Project Settings.


#include "MinigameSystem/Minigames/TerminalHackMinigame.h"
#include "ToolSystem.h"
#include "Blueprint/UserWidget.h"
#include "MinigameSystem/MinigameWidgetBase.h"

void UTerminalHackMinigame::_StartMinigame()
{
	UE_LOG(LogToolSystem, Log, TEXT("Terminal Hack Minigame has been started."));
	
	MinigameWidgetInstance = CreateWidget<UMinigameWidgetBase>(
		GetWorld()->GetFirstPlayerController(),
		MinigameWidgetClass
	);
	if (MinigameWidgetInstance)
	{
		MinigameWidgetInstance->MinigameInstance = this;
		MinigameWidgetInstance->AddToViewport();
		MinigameWidgetInstance->OnMinigameStarted();
	}
}
