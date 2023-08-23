// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PBallActor.generated.h"


class USphereComponent;


UCLASS()
class MPINGPONG_API APBallActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* SphereComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Speed;

	UPROPERTY(ReplicatedUsing = "OnRep_BallLocation")
	FVector BallLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Score")
	int GoalScore;

	UFUNCTION()
	void OnRep_BallLocation();

	UFUNCTION(Server, Reliable)
	void Server_MoveBall(float DeltaTime);
	
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	
	APBallActor();

	virtual void Tick(float DeltaTime) override;

};
