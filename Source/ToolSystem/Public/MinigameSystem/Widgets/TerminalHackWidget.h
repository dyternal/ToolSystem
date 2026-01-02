// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "MinigameSystem/MinigameWidgetBase.h"
#include "TerminalHackWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSYSTEM_API UTerminalHackWidget : public UMinigameWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DesiredHackText;
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* InputText;
	UPROPERTY(meta=(BindWidget))
	UButton* SendButton;
	UPROPERTY(meta=(BindWidget))
	UButton* CloseButton;
	
	virtual void NativeConstruct() override;
	void SetDesiredHackText() const;
	UFUNCTION()
	void OnSendButtonClick();
	UFUNCTION()
	void OnCloseButtonClick();
};
