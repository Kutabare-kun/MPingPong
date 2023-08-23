// Fill out your copyright notice in the Description page of Project Settings.


#include "PScore_Widget.h"

#include "Components/TextBlock.h"
#include "MPingPong/MPingPong.h"

void UPScore_Widget::SetTextFisrtPlayer(const FString& Text)
{
	ScoreFirstPlayer->SetText(FText::FromString(Text));

	FString Msg = FString::Printf(TEXT("P1, Scored changed: %s"), *Text);
	LogOnScreen(this, Msg);
}


void UPScore_Widget::SetTextSecondPlayer(const FString& Text)
{
	ScoreSecondPlayer->SetText(FText::FromString(Text));
	FString Msg = FString::Printf(TEXT("P2, Scored changed: %s"), *Text);
	LogOnScreen(this, Msg);
}
