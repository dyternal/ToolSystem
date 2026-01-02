// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinigameSystem/MinigameBase.h"
#include "ElectricalMinigame.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSYSTEM_API UElectricalMinigame : public UMinigameBase
{
	GENERATED_BODY()
	
protected:
	virtual void _StartMinigame() override;
};
