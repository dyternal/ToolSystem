// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MinigameSystem/MinigameBase.h"
#include "TerminalHackMinigame.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSYSTEM_API UTerminalHackMinigame : public UMinigameBase
{
	GENERATED_BODY()
	
protected:
	virtual void _StartMinigame() override;
	
public:
	TArray<FText> HackWord = {
		FText::FromString(TEXT("#include <iostream>")),
		FText::FromString(TEXT("for (int i = 0; i < n; i++)")),
		FText::FromString(TEXT("while (true) { }")),
		FText::FromString(TEXT("console.log(\"Hello World\");")),
		FText::FromString(TEXT("SELECT * FROM users;")),
		FText::FromString(TEXT("int main() { return 0; }")),
		FText::FromString(TEXT("if (x > y) { return x; } else { return y; }")),
		FText::FromString(TEXT("void nonReturnFunction() { }"))
	};
};
