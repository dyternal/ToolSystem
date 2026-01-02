// Fill out your copyright notice in the Description page of Project Settings.


#include "MinigameSystem/Widgets/ElectricalFixWidget.h"
#include "MinigameSystem/MinigameBase.h"

void UElectricalFixWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if (!GetCurrentArrowPanel(CurrentSkillCheckIndex)) return;
	RotateArrow(GetCurrentArrowPanel(CurrentSkillCheckIndex), DeltaTime);
}

void UElectricalFixWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetSkillCheckRotations();
}

void UElectricalFixWidget::SetSkillCheckRotations()
{
	for (int32 i = 0; i < 3; i++)
	{
		SkillCheckRotations[i] = FMath::FRandRange(0.f, 360.f);
	}
	FirstSkillCheckImage->SetRenderTransformAngle(SkillCheckRotations[0]);
	SecondSkillCheckImage->SetRenderTransformAngle(SkillCheckRotations[1]);
	ThirdSkillCheckImage->SetRenderTransformAngle(SkillCheckRotations[2]);
}

void UElectricalFixWidget::RotateArrow(UCanvasPanel* Arrow, float DeltaTime)
{
	CurrentAngle += RotationSpeed * DeltaTime * -1; // -1 for reverse
	Arrow->SetRenderTransformAngle(CurrentAngle);
	
}

UCanvasPanel* UElectricalFixWidget::GetCurrentArrowPanel(int32 index) const
{
	switch (index)
	{
		case 0:
			return FirstArrow;
		case 1:
			return SecondArrow;
		case 2:
			return ThirdArrow;
		default:
			return nullptr;
	}
}

void UElectricalFixWidget::TriggerSkillCheck()
{
	float NormalizedArrow = FRotator::NormalizeAxis(CurrentAngle);
	float NormalizedSkillCheck = FRotator::NormalizeAxis(SkillCheckRotations[CurrentSkillCheckIndex]);
	
	float AngleDiff = FMath::Abs(FRotator::NormalizeAxis(NormalizedArrow - NormalizedSkillCheck));
	
	if (AngleDiff <= (SuccessThreshold))
	{
		CurrentSkillCheckIndex++;
		if (CurrentSkillCheckIndex >= 3)
		{
			MinigameInstance->CompleteMinigame(EMinigameState::Success);
		}
	}
	else
	{
		MinigameInstance->CompleteMinigame(EMinigameState::Failed);
	}
}

