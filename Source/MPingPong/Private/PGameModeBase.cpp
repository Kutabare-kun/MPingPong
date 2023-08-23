#include "PGameModeBase.h"

#include "PBallActor.h"


APGameModeBase::APGameModeBase()
	: BallSpawn_Delay(5.0f)
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
