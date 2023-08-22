#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MPINGPONG_API APGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int ScorePlayerFirst;
	int ScorePlayerSecond;

public:
	
	APGameModeBase();

	virtual void Tick(float DeltaSeconds) override;

	void IncreaseScore(FString PlayerId);
	
};
