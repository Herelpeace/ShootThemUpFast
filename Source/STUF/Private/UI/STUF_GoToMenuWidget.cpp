// BGAT studio. All Rights Reserved. 


#include "UI/STUF_GoToMenuWidget.h"
#include "Components/Button.h"
#include "STUF_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUFGoToMenuWidget, All, All);

void USTUF_GoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &USTUF_GoToMenuWidget::OnGoToMenu);
	}
}

void USTUF_GoToMenuWidget::OnGoToMenu()
{
	if(!GetWorld()) return;

	const auto STUFGameInstance = GetWorld()->GetGameInstance<USTUF_GameInstance>();
	if(!STUFGameInstance) return;

	if (STUFGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOGFMT(LogSTUFGoToMenuWidget, Warning, "Level name is NONE");
		return;
	}

	UGameplayStatics::OpenLevel(this, STUFGameInstance->GetMenuLevelName());

}