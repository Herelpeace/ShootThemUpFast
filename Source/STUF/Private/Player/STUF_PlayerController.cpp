// BGAT studio. All Rights Reserved. 


#include "Player/STUF_PlayerController.h"
#include "Components/STUF_RespawnComponent.h"
#include "STUF_GameModeBase.h"
#include "STUF_GameInstance.h"


ASTUF_PlayerController::ASTUF_PlayerController()
{
	// создаем компонент RespawnComponent
	RespawnComponent = CreateDefaultSubobject<USTUF_RespawnComponent>("STUF_ARespawnComponent");

}

void ASTUF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUF_PlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUF_PlayerController::OnMuteSound);

}


void ASTUF_PlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause( this);
}

void ASTUF_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUF_GameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUF_PlayerController::OnMatchStateChanged);
		}
	}
}

void ASTUF_PlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASTUF_PlayerController::OnMuteSound()
{
	if(!GetWorld()) return;
	const auto STUF_GameInstance = GetWorld()->GetGameInstance<USTUF_GameInstance>();

	if(!STUF_GameInstance) return;

	STUF_GameInstance->ToggleVolume();

}


/*

void ASTUF_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess( InPawn);

	OnNewPawn.Broadcast(InPawn);
}
*/