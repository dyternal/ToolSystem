// Fill out your copyright notice in the Description page of Project Settings.


#include "MinigameSystem/Widgets/TerminalHackWidget.h"
#include "MinigameSystem/MinigameBase.h"
#include "MinigameSystem/Minigames/TerminalHackMinigame.h"

void UTerminalHackWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetDesiredHackText();
	FInputModeUIOnly inputModeUIOnly;
	inputModeUIOnly.SetWidgetToFocus(InputText->TakeWidget());
	GetWorld()->GetFirstPlayerController()->SetInputMode(inputModeUIOnly);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	SendButton->OnClicked.AddDynamic(this, &UTerminalHackWidget::OnSendButtonClick);
	CloseButton->OnClicked.AddDynamic(this, &UTerminalHackWidget::OnCloseButtonClick);
}

void UTerminalHackWidget::SetDesiredHackText() const
{
	UTerminalHackMinigame* MinigameInstanceCast = Cast<UTerminalHackMinigame>(MinigameInstance);
	if (!MinigameInstanceCast) MinigameInstance->CompleteMinigame(EMinigameState::Failed);
	int32 randomIndex = FMath::RandRange(0, MinigameInstanceCast->HackWord.Num() - 1);
	DesiredHackText->SetText(MinigameInstanceCast->HackWord[randomIndex]);
}

void UTerminalHackWidget::OnSendButtonClick()
{
	if (!MinigameInstance) return;
	if (!(InputText->GetText().EqualTo( DesiredHackText->GetText()))) return;
	MinigameInstance->CompleteMinigame(EMinigameState::Success);
}

void UTerminalHackWidget::OnCloseButtonClick()
{
	if (!MinigameInstance) return;
	MinigameInstance->CancelMinigame();
}
