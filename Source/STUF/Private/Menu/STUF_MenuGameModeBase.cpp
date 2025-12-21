// BGAT studio. All Rights Reserved. 


#include "Menu/STUF_MenuGameModeBase.h"
#include "Menu/STUF_MenuPlayerController.h"
#include "Menu/UI/STUF_MenuHUD.h"

ASTUF_MenuGameModeBase::ASTUF_MenuGameModeBase()
{
	PlayerControllerClass = ASTUF_MenuPlayerController::StaticClass();
	HUDClass = ASTUF_MenuHUD::StaticClass();
}