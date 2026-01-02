#pragma once

#include "ToolTypes.generated.h"

UENUM(BlueprintType, meta = (Bitflags))
enum class EToolTypes : uint8
{
	None                = 0 UMETA(DisplayName = "None"),
	MechanicalRepair    = 1 << 0 UMETA(DisplayName = "Terminal Hack"),        // Wrench, Screwdriver
	ElectricalRepair    = 1 << 1 UMETA(DisplayName = "Electrical Repair"),        // Fuse Tool, Wire Cutter
	DiagnosticScan      = 1 << 2 UMETA(DisplayName = "Diagnostic Scan")          // Analyzer, Scanner
};
ENUM_CLASS_FLAGS(EToolTypes);