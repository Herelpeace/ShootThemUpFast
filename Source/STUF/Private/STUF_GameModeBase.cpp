// BGAT studio. All Rights Reserved. 


#include "STUF_GameModeBase.h"
#include "Player/STUF_Character.h"
#include "Player/STUF_PlayerController.h"
#include "UI/STUF_GameHUD.h"

ASTUF_GameModeBase::ASTUF_GameModeBase () 
{
	DefaultPawnClass = ASTUF_Character::StaticClass();

	PlayerControllerClass = ASTUF_PlayerController::StaticClass();

	HUDClass = ASTUF_GameHUD::StaticClass();

}