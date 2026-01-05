#pragma once

#include "MinigameStates.generated.h"

UENUM()
enum class EMinigameState : uint8
{
	NotStarted	UMETA(DisplayName = "Not Started"),
	InProgress	UMETA(DisplayName = "In Progress"),
	Success		UMETA(DisplayName = "Success"),
	Cancelled	UMETA(DisplayName = "Cancelled"),
	Failed		UMETA(DisplayName = "Failed")
};
