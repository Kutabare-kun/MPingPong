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

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UUserWidget* ScoreWidget;

	UFUNCTION(BlueprintCallable)
	void MovePawnRight(float Value);

	void WaitingClient();

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	
	APPlayerController();
	
};
