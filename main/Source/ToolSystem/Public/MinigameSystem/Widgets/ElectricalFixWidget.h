// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "MinigameSystem/MinigameWidgetBase.h"
#include "ElectricalFixWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSYSTEM_API UElectricalFixWidget : public UMinigameWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	UImage* FirstSkillCheckImage;
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* FirstArrow;
	
	UPROPERTY(meta=(BindWidget))
	UImage* SecondSkillCheckImage;
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* SecondArrow;
	
	UPROPERTY(meta=(BindWidget))
	UImage* ThirdSkillCheckImage;
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* ThirdArrow;
	
	int32 CurrentSkillCheckIndex = 0;
	
	float SkillCheckRotations[3];
	float SuccessThreshold = 35.0f;
	
	
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	virtual void NativeConstruct() override;
	void SetSkillCheckRotations();
	void RotateArrow(UCanvasPanel* SkillCheck, float DeltaTime);
	UCanvasPanel* GetCurrentArrowPanel(int32 index) const;
	
protected:
	float CurrentAngle = 0.0f;
	float RotationSpeed = 380.0f; // degrees per second
	
public:
	void TriggerSkillCheck();
};
