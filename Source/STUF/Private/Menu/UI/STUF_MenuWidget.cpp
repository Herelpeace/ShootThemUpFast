// BGAT studio. All Rights Reserved. 


#include "Menu/UI/STUF_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUF_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUF_MenuWidget::OnStartGame);
	}

}

void USTUF_MenuWidget::OnStartGame()
{
	const FName StartupLevelName = "TestLevel";
	UGameplayStatics::OpenLevel(this, StartupLevelName );
}