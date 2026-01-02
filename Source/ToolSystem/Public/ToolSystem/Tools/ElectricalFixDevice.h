// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolSystem/ToolBase.h"
#include "ElectricalFixDevice.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSYSTEM_API AElectricalFixDevice : public AToolBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="ToolSystem | Tool")
	TSubclassOf<class UMinigameWidgetBase> MinigameWidgetClass;
	
	virtual void StartTool() override;
	virtual void InitializeMinigame(UMinigameBase* minigame) override;
	
};
