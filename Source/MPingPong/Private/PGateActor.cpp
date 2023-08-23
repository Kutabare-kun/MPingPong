// Fill out your copyright notice in the Description page of Project Settings.


#include "PGateActor.h"

#include "PBoardPlayer.h"
#include "MPingPong/MPingPong.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APGateActor::APGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APGateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APGateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


APawn* APGateActor::GetOwnerGate() const
{
	return Player;
}


void APGateActor::Server_OwnerPlayer_Implementation(APawn* PlayerOwner)
{
	Player = PlayerOwner;
}


void APGateActor::Multicast_OwnerPlayer_Implementation(APawn* PlayerOwner)
{
	Player = PlayerOwner;
}


void APGateActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APGateActor, Player);
}
