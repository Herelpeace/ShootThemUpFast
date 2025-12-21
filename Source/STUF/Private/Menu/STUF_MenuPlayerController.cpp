// BGAT studio. All Rights Reserved. 


#include "Menu/STUF_MenuPlayerController.h"

void ASTUF_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}
