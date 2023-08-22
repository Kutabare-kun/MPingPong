// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPawnArea.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;

UCLASS()
class MPINGPONG_API APPawnArea : public APawn
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;
	
	UPROPERTY(BlueprintReadOnly, Category = "Client")
	FString Id;

	UPROPERTY(ReplicatedUsing = "OnRep_NewLocation");
	FVector NewLocation;

	UFUNCTION()
	void OnRep_NewLocation();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float Speed;

public:
	
	APPawnArea();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_MoveRight(float Value);

	void MoveRight(float Value);
	
	// UFUNCTION(Client, Reliable, BlueprintCallable)
	// void Client_MoveRight(float Value);
	//
	// UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	// void Multicast_MoveRight(float Value);

	virtual void PossessedBy(AController* NewController) override;

	float GetSpeed() const
	{
		return Speed;
	}
};
