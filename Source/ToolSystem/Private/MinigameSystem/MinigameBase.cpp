// Fill out your copyright notice in the Description page of Project Settings.

#include "MinigameSystem/MinigameBase.h"

void UMinigameBase::StartMinigame()
{
	if (CurrentState != EMinigameState::NotStarted) return;
	SetState(EMinigameState::InProgress);
	
	_StartMinigame();
}

void UMinigameBase::CancelMinigame()
{
	SetState(EMinigameState::Canceled);
}

void UMinigameBase::CompleteMinigame(EMinigameState State)
{
	SetState(State);
}

void UMinigameBase::SetState(EMinigameState NewState)
{
	if (CurrentState == NewState) return;

	CurrentState = NewState;
	OnStateChanged.Broadcast(CurrentState);
	
	if (CurrentState == EMinigameState::Success || CurrentState == EMinigameState::Failed || CurrentState == EMinigameState::Canceled)
	{
		OnMinigameFinished.Broadcast(CurrentState);
	}
}

