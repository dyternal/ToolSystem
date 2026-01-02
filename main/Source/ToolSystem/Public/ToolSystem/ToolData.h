#pragma once
#include "MinigameSystem/MinigameBase.h"

#include "ToolData.generated.h"

USTRUCT(BlueprintType)
struct FToolData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	FText Name = FText::FromString("None");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	FString Description = "Unknown Tool";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool", meta = (Bitmask, BitmaskEnum = "EToolTypes"))
	int32 ToolType = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	TSubclassOf<UMinigameBase> MinigameClass = nullptr;
	
	
	//===============================================
	//				IN NEXT PATCHES
	//===============================================
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	UTexture2D* Icon = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	TSubclassOf<class AToolBase> Class = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	float Durability = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	float PowerMultiplier = 1.f;*/ 
	

};