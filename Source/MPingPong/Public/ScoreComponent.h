// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreChanged, UScoreComponent*, OwningComp, int32, NewValue, int32, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MPINGPONG_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	static UScoreComponent* GetScoreComponent(AActor* FromActor);

	UScoreComponent();

protected:

	UPROPERTY(EditDefaultsOnly, ReplicatedUsing = "OnRep_PlayerScore", Category = "Player|Score")
	int32 PlayerScore;

	UFUNCTION()
	void OnRep_PlayerScore();
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(NetMulticast, Reliable)
	void MulticastScoreChanged(int32 NewScore, int32 Delta);
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnScoreChanged OnScoreChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyGoal(int32 Delta);
	
};
