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

	UE_LOG(LogTemp, Log, TEXT("[%s]"), HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"));

	// bool bSpawnBallIsRunning = GetWorld()->GetTimerManager().IsTimerActive(BallSpawn);
	// if (bSpawnBallIsRunning && !BallActor && HasAuthority() && GetNumPlayers() >= 2)
	// {
	// 	FTimerDelegate Delegate;
	// 	Delegate.BindUFunction(this, "SpawnGameBall", BallLocation, BallRotation);
	// 	
	// 	GetWorld()->GetTimerManager().SetTimer(BallSpawn, Delegate, BallSpawn_Delay, false);
	// }
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
