// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolData.h"
#include "GameFramework/Actor.h"
#include "MinigameSystem/MinigameBase.h"
#include "ToolBase.generated.h"

UCLASS()
class TOOLSYSTEM_API AToolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToolBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;
	
	void OnMinigameStateChanged(EMinigameState NewState);
	void OnMinigameFinished(EMinigameState FinalState);
	
public:		
	//=============================================================
	//							DATA
	//=============================================================
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tool")
	FName ToolID = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tool")
	int32 ToolType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tool")
	FName SocketName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tool")
	TSubclassOf<UMinigameBase> MinigameClass;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Tool")
	UMinigameBase* MinigameInstance = nullptr;
	
	virtual void Initialize(UDataTable* ToolDataTable);
	virtual void InitializeMinigame(UMinigameBase* minigame);
	virtual void StartTool();
	virtual void FinishTool();

};
