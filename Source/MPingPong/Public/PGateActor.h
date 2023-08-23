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

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(Replicated)
	APawn* Player;
	
	virtual void BeginPlay() override;

public:

	APGateActor();
	
	UFUNCTION(BlueprintCallable)
	APawn* GetOwnerGate() const;

	UFUNCTION(Server, Reliable)
	void Server_OwnerPlayer(APawn* PlayerOwner);
	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OwnerPlayer(APawn* PlayerOwner);

	virtual void Tick(float DeltaTime) override;

};
