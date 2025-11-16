// BGAT studio. All Rights Reserved. 


#include "STUF_GameModeBase.h"
#include "Player/STUF_Character.h"
#include "Player/STUF_PlayerController.h"
#include "UI/STUF_GameHUD.h"
#include "AIController.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUFGameModeBase, All, All);

ASTUF_GameModeBase::ASTUF_GameModeBase () 
{
	DefaultPawnClass = ASTUF_Character::StaticClass();

	PlayerControllerClass = ASTUF_PlayerController::StaticClass();

	HUDClass = ASTUF_GameHUD::StaticClass();

}

// функция вызывается до BeginPlay Game модв, и до всех остальных. самамя первая
void ASTUF_GameModeBase::StartPlay()
{
	Super::StartPlay();
	SpawnBots();

	CurrentRound = 1;
	StartRound();
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
	UE_LOGFMT(LogSTUFGameModeBase,Warning,"Time: {0} / Round: {1}/{2} ",RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			StartRound();
		}
		else
		{
			UE_LOGFMT(LogSTUFGameModeBase,Warning,"======== Game Over ========" );
		}
	}
}