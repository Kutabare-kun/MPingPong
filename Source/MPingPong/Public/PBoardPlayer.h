// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PBoardPlayer.generated.h"


class UScoreComponent;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;


UCLASS()
class MPINGPONG_API APBoardPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APBoardPlayer();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UScoreComponent* ScoreComp;

	UPROPERTY(ReplicatedUsing = "OnRep_NewLocation");
	FVector NewLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float Speed;
	
	UFUNCTION()
	void OnRep_NewLocation();
	
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnScoreChanged(UScoreComponent* OwningComp, int NewScore, int Delta);
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ServerId")
	FString PlayerId;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_MoveRight(float Value);

	void MoveRight(float Value);

	virtual void PossessedBy(AController* NewController) override;

	float GetSpeed() const
	{
		return Speed;
	}
};
