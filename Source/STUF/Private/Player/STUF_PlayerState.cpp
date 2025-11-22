// BGAT studio. All Rights Reserved. 


#include "Player/STUF_PlayerState.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUFPlayerState, All, All);

void ASTUF_PlayerState::LogInfo()
{
	UE_LOGFMT(LogSTUFPlayerState,Warning,"TeamID: {0}, Kills: {1}, Death: {2} ", TeamID, KillsNum, DeathNum);
}