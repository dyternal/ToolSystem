#pragma once

#include "ToolTypes.generated.h"

// I don't develop ToolType logic now, I'll leave it as a basic structure, maybe in next patch

UENUM(BlueprintType, meta = (Bitflags))
enum class EToolTypes : uint8
{
	None                = 0 UMETA(DisplayName = "None"),
	TerminalHack    = 1 << 0 UMETA(DisplayName = "Terminal Hack"),
	ElectricalRepair    = 1 << 1 UMETA(DisplayName = "Electrical Repair"),
	DiagnosticScan      = 1 << 2 UMETA(DisplayName = "Diagnostic Scan") // maybe in next patch
};
ENUM_CLASS_FLAGS(EToolTypes);