#include "PPlayerController.h"

#include "PBoardPlayer.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameStateBase.h"
#include "../MPingPong.h"


APPlayerController::APPlayerController()
{
}


void APPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	this->InputComponent->BindAxis("Turn", this, &APPlayerController::MovePawnRight);
}


void APPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass && ScoreWidget == nullptr)
	{
		ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport();
	}
}


void APPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	WaitingClient();
}


void APPlayerController::MovePawnRight(float Value)
{
	if (Value != 0.f)
	{
		APBoardPlayer* ControlledPawn = GetPawn<APBoardPlayer>();

		if (ControlledPawn)
		{
			ControlledPawn->MoveRight(Value);
		}
	}
}


void APPlayerController::WaitingClient()
{
	UWorld* World = GetWorld();
	if(World == nullptr)
	{
		return;
	}
    
	AGameStateBase* GameState = World->GetGameState();
	if(GameState == nullptr)
	{
		return;
	}

	AGameModeBase* GameMode = GameState->AuthorityGameMode;
	if(GameMode == nullptr)
	{
		return;
	}

	int UniquePlayers = GameMode->GetNumPlayers();
	int MaxPlayerToPlay{2};
	
	if (UniquePlayers < MaxPlayerToPlay)
	{
		FString Msg = FString::Printf(TEXT("Wainting a new Client. Current Unique Client: %d"), UniquePlayers);
		LogOnScreen(this, Msg, FColor::White, 0);
	}
}

