#include "PGameModeBase.h"

#include "EngineUtils.h"
#include "MPingPong.h"
#include "PPawnArea.h"

APGameModeBase::APGameModeBase()
	: ScorePlayerFirst(), ScorePlayerSecond()
{}

void APGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FString Msg = FString::Printf(TEXT("P1: %d, P2: %d"), ScorePlayerFirst, ScorePlayerSecond);
	LogOnScreen(this, Msg, FColor::White, 0);
}


void APGameModeBase::IncreaseScore(FString PlayerId)
{
	if (PlayerId.Equals(FString("Player 1"))) {
		ScorePlayerFirst += 1;
	}
	else if(PlayerId.Equals(FString("Player 2"))) {
		ScorePlayerSecond += 1;
	}

	FString Msg = FString::Printf(TEXT("%s scored a point."), *PlayerId);
	LogOnScreen(this, Msg);
}

