#pragma once

#include "MinigameStates.generated.h"

UENUM()
enum class EMinigameState : uint8
{
	NotStarted	UMETA(DisplayName = "Not Started"),
	InProgress	UMETA(DisplayName = "In Progress"),
	Success		UMETA(DisplayName = "Success"),
	Canceled	UMETA(DisplayName = "Canceled"),
	Failed		UMETA(DisplayName = "Failed")
};
