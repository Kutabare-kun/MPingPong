// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MPINGPONG_API APPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	

	UFUNCTION(BlueprintCallable)
	void MovePawnRight(float Value);

	virtual void SetupInputComponent() override;

public:
	
	APPlayerController();
	
};
