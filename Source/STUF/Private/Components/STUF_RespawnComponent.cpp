// BGAT studio. All Rights Reserved. 


#include "Components/STUF_RespawnComponent.h"
#include "STUF_GameModeBase.h"

USTUF_RespawnComponent::USTUF_RespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUF_RespawnComponent::Respawn(int32 RespawnTime)
{
	if(!GetWorld()) return;
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTUF_RespawnComponent::RespawnTimerUpdate, 1.0f, true);

}


void USTUF_RespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if(!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<ASTUF_GameModeBase>(GetWorld()->GetAuthGameMode());
		if(!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));

	}
}

