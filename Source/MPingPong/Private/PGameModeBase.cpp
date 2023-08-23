#include "PGameModeBase.h"

#include "PBallActor.h"


APGameModeBase::APGameModeBase()
	: ScorePlayerFirst(), ScorePlayerSecond(), BallSpawn_Delay(5.0f)
{}


void APGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Spawn ball when second player is logged in
	if (GetNumPlayers() >= 2)
	{
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "SpawnGameBall", BallLocation, BallRotation);
		
		GetWorld()->GetTimerManager().SetTimer(BallSpawn, Delegate, BallSpawn_Delay, false);
	}
}


void APGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}


void APGameModeBase::IncreaseScore(FString PlayerId)
{
	if (PlayerId.Equals(FString("Player 1"))) {
		ScorePlayerFirst += 1;
	}
	else if(PlayerId.Equals(FString("Player 2"))) {
		ScorePlayerSecond += 1;
	}
}


void APGameModeBase::SpawnGameBall(FVector Location, FRotator Rotator)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	GetWorld()->SpawnActor<APBallActor>(BallClass, Location, Rotator, SpawnParams);
}


FVector APGameModeBase::GetBallSpawnLocation() const
{
	return BallLocation;
}
