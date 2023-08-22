// Fill out your copyright notice in the Description page of Project Settings.


#include "PPawnArea.h"

#include "MPingPong.h"
#include "NavigationSystemTypes.h"
#include "PPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APPawnArea::APPawnArea()
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

	Speed = 400.0f;
}

void APPawnArea::BeginPlay()
{
	Super::BeginPlay();

	if (GetController() == GetWorld()->GetFirstPlayerController())
	{
		this->Id = FString("Player 1");
	}
	else
	{
		this->Id = FString("Player 2");
	}
}


void APPawnArea::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NewController)
	{
		Controller = NewController;
	}
}


void APPawnArea::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FString Msg = FString::Printf(TEXT("Location: %s, Player: %s"), *GetActorLocation().ToString(), *Id);
	
	LogOnScreen(this, Msg, FColor::Orange, 0);
}


void APPawnArea::MoveRight(float Value)
{
	Server_MoveRight(Value);
}

// NewLocation is changed on Server
void APPawnArea::Server_MoveRight_Implementation(float Value)
{
	if (Value != 0.0f)
	{
		FRotator Rot = GetActorRotation();
		Rot.Pitch = 0.0f;
		Rot.Roll = 0.0f;
		
		FVector RightVector = FRotationMatrix(Rot).GetScaledAxis(EAxis::Y);
			
		NewLocation = GetActorLocation() + (RightVector * Speed * GetWorld()->GetDeltaSeconds() * Value); 
		
		LogOnScreen(this, NewLocation.ToString(), FColor::Blue, 0);

		OnRep_NewLocation();
	}
}

// Server: Must be use function in body where variable(NewLocation) is changed
// Client: Automatic use this function when variable(NewLocation) is changed
void APPawnArea::OnRep_NewLocation()
{
	SetActorLocation(NewLocation, true);
}


void APPawnArea::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APPawnArea, NewLocation);
}
