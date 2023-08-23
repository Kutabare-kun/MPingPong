// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreComponent.h"

#include "PBoardPlayer.h"
#include "PScore_Widget.h"
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


bool UScoreComponent::ApplyGoal(int32 Delta)
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

		OnRep_PlayerScore();
	}

	return ActualDelta != 0;
}


void UScoreComponent::OnRep_PlayerScore()
{
	APBoardPlayer* BoardPlayer = Cast<APBoardPlayer>(GetOwner());
	UPScore_Widget* ScoreWidget = BoardPlayer->GetScoreWidget();
	FString ScoreText = FString::FromInt(PlayerScore);

	if (BoardPlayer->GetPlayerId().Equals(FString("Player 1")))
	{
		if (ScoreWidget)
		{
			ScoreWidget->SetTextFisrtPlayer(ScoreText);
		}
	}
	else if (BoardPlayer->GetPlayerId().Equals(FString("Player 2")))
	{
		if (ScoreWidget)
		{
			ScoreWidget->SetTextSecondPlayer(ScoreText);
		}
	}
}


void UScoreComponent::MulticastScoreChanged_Implementation(int32 NewScore, int32 Delta)
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
