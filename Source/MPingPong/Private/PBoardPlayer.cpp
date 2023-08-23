// Fill out your copyright notice in the Description page of Project Settings.


#include "PBoardPlayer.h"


#include "EngineUtils.h"
#include "PGateActor.h"
#include "ScoreComponent.h"
#include "PScore_Widget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MPingPong/MPingPong.h"
#include "Net/UnrealNetwork.h"

int32 APBoardPlayer::NextPlayerNumber = 1;

// Sets default values
APBoardPlayer::APBoardPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	RootComponent = BoxComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	ScoreComp = CreateDefaultSubobject<UScoreComponent>("ScoreComp");

	Speed = 400.0f;
}


void APBoardPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ScoreComp->OnScoreChanged.AddDynamic(this, &APBoardPlayer::OnScoreChanged);
}


void APBoardPlayer::OnScoreChanged(UScoreComponent* OwningComp, int32 NewScore, int32 Delta)
{
	if (Delta < 0.0f)
	{
		ScoreComp->ApplyGoal(Delta);
	}
}


FString APBoardPlayer::GetPlayerId() const
{
	return PlayerId;
}


void APBoardPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PlayerNumber = NextPlayerNumber++;
		
		OnRep_PlayerNumber();
	}

	float MinDistance = FLT_MAX;

	APGateActor* Gate = nullptr;
	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		APGateActor* MyGate = Cast<APGateActor>(*It);
		if (MyGate)
		{
			if (MyGate->GetOwnerGate())
			{
				continue;
			}
			
			float Distance = FVector::Distance(MyGate->GetActorLocation(), GetActorLocation());
			if (Distance < MinDistance)
			{
				Gate = MyGate;
			}
		}
	}

	if (Gate)
	{
		if (HasAuthority())
		{
			Gate->Server_OwnerPlayer(this);
		}
		else
		{
			Gate->Multicast_OwnerPlayer(this);
		}
	}
}


void APBoardPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NewController)
	{
		Controller = NewController;
	}
}

// Called every frame
void APBoardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ScoreWidgetClass && ScoreWidget == nullptr)
	{
		ScoreWidget = CreateWidget<UPScore_Widget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport();
	}

	FString Msg = FString::Printf(TEXT("Widget: %s"), *GetNameSafe(ScoreWidget));
	LogOnScreen(this, Msg, FColor::Orange, 0);
	
	Msg = FString::Printf(TEXT("%s, Score: %d"), *PlayerId, ScoreComp->GetScore());
	LogOnScreen(this, Msg, FColor::Orange, 0);
}


void APBoardPlayer::MoveRight(float Value)
{
	Server_MoveRight(Value);
}

// NewLocation is changed on Server
void APBoardPlayer::Server_MoveRight_Implementation(float Value)
{
	if (Value != 0.0f)
	{
		FRotator Rot = GetActorRotation();
		Rot.Pitch = 0.0f;
		Rot.Roll = 0.0f;
		
		FVector RightVector = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);
			
		NewLocation = GetActorLocation() + (RightVector * Speed * GetWorld()->GetDeltaSeconds() * Value); 

		OnRep_NewLocation();
	}
}


void APBoardPlayer::OnRep_PlayerNumber()
{
	if (PlayerNumber == 1)
	{
		PlayerId = FString("Player 1");
	}
	else if (PlayerNumber == 2)
	{
		PlayerId = FString("Player 2");
	}
}

// Server: Must be use function in body where variable(NewLocation) is changed
// Client: Automatic use this function when variable(NewLocation) is changed
void APBoardPlayer::OnRep_NewLocation()
{
	SetActorLocation(NewLocation, true);
}


void APBoardPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APBoardPlayer, NewLocation);
	DOREPLIFETIME(APBoardPlayer, PlayerNumber);
}


