// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUF_PlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);

}

void USTUF_PlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);

}

void USTUF_PlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);

}

void USTUF_PlayerStatRowWidget::SetTeam(const FText& Text)
{
	if(!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void USTUF_PlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if(!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

}

void USTUF_PlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if(!TeamImage) return;
	TeamImage->SetColorAndOpacity(Color);
}