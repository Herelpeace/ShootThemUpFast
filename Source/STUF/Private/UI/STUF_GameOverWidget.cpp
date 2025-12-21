// BGAT studio. All Rights Reserved. 


#include "UI/STUF_GameOverWidget.h"
#include "STUF_GameModeBase.h"
#include "Player/STUF_PlayerState.h"
#include "UI/STUF_PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"

bool USTUF_GameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUF_GameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USTUF_GameOverWidget::OnMatchStateChanged);
		}
	}

	return Super::Initialize();
}

void USTUF_GameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void USTUF_GameOverWidget::UpdatePlayersStat()
{
	PlayerStatBox->ClearChildren();		// удаляем все строки которые есть в виджете

	if(!GetWorld() || !PlayerStatBox ) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto PlayerState = Cast<ASTUF_PlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<USTUF_PlayerStatRowWidget>(GetWorld(),PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathNum()));
		PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());	//

		PlayerStatBox->AddChild(PlayerStatRowWidget);

	}

}