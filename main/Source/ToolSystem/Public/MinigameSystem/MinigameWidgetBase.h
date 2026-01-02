// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinigameStates.h"
#include "Blueprint/UserWidget.h"
#include "MinigameWidgetBase.generated.h"

class UMinigameBase;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TOOLSYSTEM_API UMinigameWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Minigame Started"))
	void OnMinigameStarted();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Minigame Finished"))
	void OnMinigameFinished(EMinigameState Result);
	
	UPROPERTY()
	UMinigameBase* MinigameInstance = nullptr;	
};
