// Fill out your copyright notice in the Description page of Project Settings.


#include "PBallActor.h"

#include "../MPingPong.h"
#include "PGateActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

class APGateActor;
// Sets default values
APBallActor::APBallActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	Speed = 600.0f;

	SetReplicates(true);
}


void APBallActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &APBallActor::OnHit);
}

// Called when the game starts or when spawned
void APBallActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void APBallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Server_MoveBall(DeltaTime);
}


void APBallActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	APGateActor* Gate = Cast<APGateActor>(OtherActor);

	FString Msg = FString::Printf(TEXT("Collided with: %s"), *GetNameSafe(OtherActor));
	LogOnScreen(this, Msg, FColor::Green, 10);
		
	if (Gate)
	{
		// TODO: Logic where gate is collided with Gate
	}
	else 
	{
		FVector ForwardVec = GetActorForwardVector();
			
		FVector ProjNorm = UKismetMathLibrary::ProjectVectorOnToVector(ForwardVec, Hit.ImpactNormal);
		 
		FVector DesiredForwardVec = ForwardVec - 2 * ProjNorm;

		SetActorRotation(DesiredForwardVec.Rotation());
	}
}


void APBallActor::Server_MoveBall_Implementation(float DeltaTime)
{
	FVector Location = GetActorLocation();
	FVector Direction = GetActorForwardVector();

	BallLocation = Location + (Direction * Speed * DeltaTime);
	
	OnRep_BallLocation();
}


void APBallActor::OnRep_BallLocation()
{
	SetActorLocation(BallLocation, true);
}


void APBallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APBallActor, BallLocation);
}
