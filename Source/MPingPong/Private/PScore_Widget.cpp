// Fill out your copyright notice in the Description page of Project Settings.


#include "PScore_Widget.h"

#include "Components/TextBlock.h"

void UPScore_Widget::SetTextFisrtPlayer(const FString& Text)
{
	ScoreFirstPlayer->SetText(FText::FromString(Text));
}


void UPScore_Widget::SetTextSecondPlayer(const FString& Text)
{
	ScoreSecondPlayer->SetText(FText::FromString(Text));
}
