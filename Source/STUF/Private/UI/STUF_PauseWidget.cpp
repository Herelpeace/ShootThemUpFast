// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool USTUF_PauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUF_PauseWidget::OnClearPause);
	}

	return InitStatus;

}

void USTUF_PauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode() ) return;

	// снимаем игру с паузы
	GetWorld()->GetAuthGameMode()->ClearPause();

}