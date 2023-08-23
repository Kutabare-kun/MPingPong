// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PBoardPlayer.generated.h"


class UPScore_Widget;
class UScoreComponent;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;


UCLASS()
class MPINGPONG_API APBoardPlayer : public APawn
{
	GENERATED_BODY()

public:
	
	APBoardPlayer();

protected:
	
	static int32 NextPlayerNumber;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPScore_Widget> PScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UPScore_Widget* PScoreWidget;
	
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString PlayerId;
	
	UPROPERTY(ReplicatedUsing = "OnRep_PlayerNumber")
	int32 PlayerNumber;

	UFUNCTION()
	void OnRep_PlayerNumber();
	
	UFUNCTION()
	void OnRep_NewLocation();
	
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnScoreChanged(UScoreComponent* OwningComp, int32 NewScore, int32 Delta);
	
public:

	FString GetPlayerId() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_MoveRight(float Value);

	void MoveRight(float Value);

	virtual void PossessedBy(AController* NewController) override;

	UPScore_Widget* GetScoreWidget() const
	{
		return PScoreWidget;
	}

	float GetSpeed() const
	{
		return Speed;
	}
};
