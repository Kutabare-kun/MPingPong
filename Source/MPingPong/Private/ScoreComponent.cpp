// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}


void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


int UScoreComponent::GetScore() const
{
	return PlayerScore;
}


bool UScoreComponent::ApplyGoal(int Delta)
{
	int OldScore = PlayerScore;
	int NewScore = PlayerScore + Delta;

	int ActualDelta = NewScore - OldScore;
	
	if (GetOwner()->HasAuthority())
	{
		PlayerScore = NewScore;

		if (ActualDelta != 0)
		{
			MulticastScoreChanged(NewScore, ActualDelta);
		}
	}

	return ActualDelta != 0;
}


void UScoreComponent::MulticastScoreChanged_Implementation(int NewScore, int Delta)
{
	OnScoreChanged.Broadcast(this, NewScore, Delta);
}


UScoreComponent* UScoreComponent::GetScoreComponent(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UScoreComponent>(FromActor->GetComponentByClass(UScoreComponent::StaticClass()));
	}

	return nullptr;
}


void UScoreComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UScoreComponent, PlayerScore);
}
