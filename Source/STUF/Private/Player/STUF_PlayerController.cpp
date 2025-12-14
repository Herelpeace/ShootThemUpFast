// BGAT studio. All Rights Reserved. 


#include "Player/STUF_PlayerController.h"
#include "Components/STUF_RespawnComponent.h"

ASTUF_PlayerController::ASTUF_PlayerController()
{
	// создаем компонент RespawnComponent
	RespawnComponent = CreateDefaultSubobject<USTUF_RespawnComponent>("STUF_ARespawnComponent");

}

/*

void ASTUF_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess( InPawn);

	OnNewPawn.Broadcast(InPawn);
}
*/