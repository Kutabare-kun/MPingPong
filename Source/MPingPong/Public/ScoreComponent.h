// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreChanged, UScoreComponent*, OwningComp, int, NewValue, int, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MPINGPONG_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	static UScoreComponent* GetScoreComponent(AActor* FromActor);

	UScoreComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Player|Score")
	int PlayerScore;
	
	virtual void BeginPlay() override;

public:

	UFUNCTION(NetMulticast, Reliable)
	void MulticastScoreChanged(int NewScore, int Delta);
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnScoreChanged OnScoreChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyGoal(int Delta);
	
};
