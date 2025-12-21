// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void USTUF_PauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUF_PauseWidget::OnClearPause);
	}

}

void USTUF_PauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode() ) return;

	// снимаем игру с паузы
	GetWorld()->GetAuthGameMode()->ClearPause();

}