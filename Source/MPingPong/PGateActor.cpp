// Fill out your copyright notice in the Description page of Project Settings.


#include "PGateActor.h"

// Sets default values
APGateActor::APGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
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
