#include "PPlayerController.h"

#include "MPingPong.h"
#include "PPawnArea.h"


APPlayerController::APPlayerController()
{
}


void APPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	this->InputComponent->BindAxis("Turn", this, &APPlayerController::MovePawnRight);
}


void APPlayerController::MovePawnRight(float Value)
{
	FString Msg = FString::Printf(TEXT("Value: %f"), Value);
	LogOnScreen(this, Msg, FColor::White, 0);
	
	if (Value != 0.f)
	{
		APPawnArea* ControlledPawn = GetPawn<APPawnArea>();

		if (ControlledPawn)
		{
			ControlledPawn->MoveRight(Value);
		}
	}
}

