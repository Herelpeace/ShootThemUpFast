// BGAT studio. All Rights Reserved. 


#include "STUF_GameModeBase.h"
#include "Player/STUF_Character.h"
#include "Player/STUF_PlayerController.h"
#include "UI/STUF_GameHUD.h"
#include "AIController.h"
#include "Logging/StructuredLog.h"
#include "Player/STUF_PlayerState.h"
#include "STUUtils.h"
#include "Components/STUF_RespawnComponent.h"
#include "EngineUtils.h"
#include "STUF_GameInstance.h"
#include "Components/STUF_WeaponComponent.h"
#include "STUF_RifleWeapon.h"


DEFINE_LOG_CATEGORY_STATIC(LogSTUFGameModeBase, All, All);

//constexpr static int32 MinRoundTimeForRespawn = 10;

ASTUF_GameModeBase::ASTUF_GameModeBase () 
{
	DefaultPawnClass = ASTUF_Character::StaticClass();

	PlayerControllerClass = ASTUF_PlayerController::StaticClass();

	HUDClass = ASTUF_GameHUD::StaticClass();

	PlayerStateClass = ASTUF_PlayerState::StaticClass();

}

// функция вызывается до BeginPlay Game модв, и до всех остальных. самамя первая
void ASTUF_GameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();

	SetMatchState(ESTUMatchState::InProgress);
}

UClass* ASTUF_GameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


void ASTUF_GameModeBase::SpawnBots()
{
	if(!GetWorld()) return;

	for (int32 i =0; i<GameData.PlayersNum-1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUAIController);
	}
}

void ASTUF_GameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUF_GameModeBase::GameTimerUpdate, 1.0f, true);


}


void ASTUF_GameModeBase::GameTimerUpdate()
{
	//UE_LOGFMT(LogSTUFGameModeBase,Warning,"Time: {0} / Round: {1}/{2} ",RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

// вызывается каждый раз в начале раунда, вызывает функцию ResetOnePlayer
void ASTUF_GameModeBase::ResetPlayers()
{
	if(!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}

}

// делает destroy всех акторов, заново спавнит их
void ASTUF_GameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		if (auto Character = Cast<ASTUF_Character>(Controller->GetPawn()))
		{
			if(auto WeaponComp = Character->FindComponentByClass<USTUF_WeaponComponent>() )
			{
				WeaponComp->ResetWeaponState();
			}
		}

		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTUF_GameModeBase::CreateTeamsInfo()
{
	if(!GetWorld()) return;

	int32 TeamID = 1;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTUF_PlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? " Player " : " Bot ");
		SetPlayerColor(Controller);

		TeamID = TeamID==1?2:1;
	}
}


FLinearColor ASTUF_GameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColor.Num())
	{
		return GameData.TeamColor[TeamID-1];
	}
	
	return GameData.DefaultTeamColor;

}

void ASTUF_GameModeBase::SetPlayerColor(AController* Controller)
{
	if(!Controller) return;

	const auto Character = Cast<ASTUF_Character>(Controller->GetPawn());
	if(!Character) return;

	const auto PlayerState = Cast <ASTUF_PlayerState>(Controller->PlayerState);
	if(!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());

	
}

void ASTUF_GameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<ASTUF_PlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ASTUF_PlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(VictimController);

}

void ASTUF_GameModeBase::LogPlayerInfo()
{
	if(!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTUF_PlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void ASTUF_GameModeBase::StartRespawn(AController* Controller)
{
	// если до конца раунда осталось секунд меньше чем необходимо то респавн не делаем
	const auto RespawnAvailable = RoundCountDown > GameData.MinTimeAcceptRespawn+GameData.RespawnTime;
	if(!RespawnAvailable) return;

	const auto RespawnComponent = STUUtils::GetSTUFPlayerComponent<USTUF_RespawnComponent>(Controller);
	if(!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);

}

void ASTUF_GameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

void ASTUF_GameModeBase::GameOver()
{
	//UE_LOGFMT(LogSTUFGameModeBase,Warning,"======== Game Over ========" );
	LogPlayerInfo();

	for(auto Pawn: TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(ESTUMatchState::GameOver);
}

// Состояние игры
//----------------------------------------------------------------------------------------------------------

void ASTUF_GameModeBase::SetMatchState(ESTUMatchState State)
{
	if(MatchState == State) return;

	MatchState = State;

	// оповещаем всех подписавшихся об изменении состояния игры
	OnMatchStateChanged.Broadcast(MatchState);
}

// устанавлиавем паузу
bool ASTUF_GameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate )
{
	const auto PauseSet = Super::SetPause( PC,  CanUnpauseDelegate);

	if (PauseSet)
	{
		SetMatchState(ESTUMatchState::Pause);
	}
	
	return PauseSet;
}

// снимаем с паузы
bool ASTUF_GameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(ESTUMatchState::InProgress);
	}
	return PauseCleared;
}