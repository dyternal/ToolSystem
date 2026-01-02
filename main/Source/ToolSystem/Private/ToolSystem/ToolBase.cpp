// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolSystem/ToolBase.h"
#include "ToolSystem.h"
#include "MinigameSystem/MinigameWidgetBase.h"

// Sets default values
AToolBase::AToolBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(Root);

	
	StaticMeshComp->SetVisibility(true);

}

// Called when the game starts or when spawned
void AToolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AToolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToolBase::OnMinigameStateChanged(EMinigameState NewState)
{
	// maybe i will use it later
}

void AToolBase::OnMinigameFinished(EMinigameState FinalState)
{
	const UEnum* EnumPtr = StaticEnum<EMinigameState>();
	FString StateName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)FinalState) : TEXT("Invalid");
	FString DebugMsg = FString::Printf(TEXT("Minigame Final State: %s"), *StateName);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, DebugMsg);
	switch (FinalState)
	{
		case EMinigameState::Success:
			FinishTool();
			break;
		case EMinigameState::Failed:
			FinishTool();
			break;
		case EMinigameState::Canceled:
			FinishTool();
			break;
		default:
			break;
	}
}

void AToolBase::Initialize(UDataTable* ToolDataTable)
{
	if (!ToolDataTable || ToolID.IsNone())
	{
		this->Destroy();
		UE_LOG(LogToolSystem, Error, TEXT("The tool can't be loaded."));
		return;
	}
	
	const FToolData* Row = ToolDataTable->FindRow<FToolData>(ToolID, ToolID.ToString());
	
	ToolType = Row->ToolType;
	MinigameClass = Row->MinigameClass;
}

void AToolBase::InitializeMinigame(UMinigameBase* minigame)
{
	minigame->OnStateChanged.AddUObject(this, &AToolBase::OnMinigameStateChanged);
	minigame->OnMinigameFinished.AddUObject(this, &AToolBase::OnMinigameFinished);
}


void AToolBase::StartTool()
{
	if (!MinigameClass) return;
	if (MinigameInstance) return;
	MinigameInstance = NewObject<UMinigameBase>(this, MinigameClass);
	InitializeMinigame(MinigameInstance);
	MinigameInstance->StartMinigame();
}

void AToolBase::FinishTool()
{
	if (MinigameInstance)
	{
		if (MinigameInstance->MinigameWidgetInstance)
		{
			MinigameInstance->MinigameWidgetInstance->RemoveFromParent();
			MinigameInstance->MinigameWidgetInstance = nullptr;
		}
		MinigameInstance->OnStateChanged.Clear();
		MinigameInstance->OnMinigameFinished.Clear();
		MinigameInstance = nullptr;
	}
}
