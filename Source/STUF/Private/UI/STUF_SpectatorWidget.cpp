// BGAT studio. All Rights Reserved. 


#include "UI/STUF_SpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STUF_RespawnComponent.h"

bool USTUF_SpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = STUUtils::GetSTUFPlayerComponent<USTUF_RespawnComponent> (GetOwningPlayer());
	if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}