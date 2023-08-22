// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGateActor.generated.h"

UCLASS()
class MPINGPONG_API APGateActor : public AActor
{
	GENERATED_BODY()

protected:

	UStaticMeshComponent* MeshComp;
	
	virtual void BeginPlay() override;

public:

	APGateActor();

	virtual void Tick(float DeltaTime) override;

};
