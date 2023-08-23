// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PScore_Widget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MPINGPONG_API UPScore_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ScoreFirstPlayer;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ScoreSecondPlayer;

public:

	UFUNCTION(BlueprintCallable, Category = "Text Widget")
	void SetTextFisrtPlayer(const FString& Text);

	UFUNCTION(BlueprintCallable, Category = "Text Widget")
	void SetTextSecondPlayer(const FString& Text);
};
