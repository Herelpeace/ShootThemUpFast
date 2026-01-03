// BGAT studio. All Rights Reserved. 


#include "UI/STUF_GameDataWidget.h"
#include "STUF_GameModeBase.h"
#include "Player/STUF_PlayerState.h"


int32 USTUF_GameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTUF_GameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTUF_GameDataWidget::GetRoundSecondRemaining() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASTUF_GameModeBase* USTUF_GameDataWidget::GetSTUGameMode() const
{
	return GetWorld() ? Cast<ASTUF_GameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUF_PlayerState* USTUF_GameDataWidget::GetSTUPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTUF_PlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
