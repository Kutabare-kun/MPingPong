#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameModeBase.generated.h"

class APBallActor;
/**
 * 
 */
UCLASS()
class MPINGPONG_API APGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Ball|Transform")
	FVector BallLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Ball|Transform")
	FRotator BallRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Ball")
	TSubclassOf<AActor> BallClass;

	FTimerHandle BallSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Ball|Timer")
	float BallSpawn_Delay;

public:
	
	APGameModeBase();

	UFUNCTION()
	void SpawnGameBall(FVector Location, FRotator Rotator);

	FVector GetBallSpawnLocation() const;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Tick(float DeltaSeconds) override;

	// void IncreaseScore(FString PlayerId);
	
};
