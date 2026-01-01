// BGAT studio. All Rights Reserved. 


#include "Menu/STUF_MenuPlayerController.h"
#include "STUF_GameInstance.h"

void ASTUF_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	GetWorld()->GetGameInstance<USTUF_GameInstance>()->TestString = "Menu level Hello!";


}
