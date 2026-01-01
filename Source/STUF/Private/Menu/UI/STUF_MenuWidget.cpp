// BGAT studio. All Rights Reserved. 


#include "Menu/UI/STUF_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUF_GameInstance.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUFMenuWidget, All, All);

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
	if(!GetWorld()) return;

	const auto STUFGameInstance = GetWorld()->GetGameInstance<USTUF_GameInstance>();
	if(!STUFGameInstance) return;

	if (STUFGameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOGFMT(LogSTUFMenuWidget, Warning, "Level name is NONE");
		return;
	}

	UGameplayStatics::OpenLevel(this, STUFGameInstance->GetStartupLevelName());
}