// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MinigameSystem/MinigameStates.h"
#include "MinigameBase.generated.h"

class UMinigameWidgetBase;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMinigameStateChanged, EMinigameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMinigameFinished, EMinigameState);

UCLASS(Abstract)
class TOOLSYSTEM_API UMinigameBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void StartMinigame();
	virtual void CancelMinigame();
	virtual void CompleteMinigame(EMinigameState CompletionState);
	
	EMinigameState GetState() const { return CurrentState; }
	
	FOnMinigameStateChanged OnStateChanged;
	FOnMinigameFinished OnMinigameFinished;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MinigameWidgetClass;
	
	UPROPERTY()
	UMinigameWidgetBase* MinigameWidgetInstance = nullptr;

protected:
	
	UPROPERTY(VisibleAnywhere)
	EMinigameState CurrentState = EMinigameState::NotStarted;
	
	void SetState(EMinigameState NewState);
	virtual void _StartMinigame() PURE_VIRTUAL(UMinigameBase::StartMinigame, );

};
