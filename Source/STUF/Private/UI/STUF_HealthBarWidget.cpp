// BGAT studio. All Rights Reserved. 


#include "UI/STUF_HealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUF_HealthBarWidget::SetHealthPercent(float Percent)
{
	if(!HealthProgressBar) return;

	const auto HealthBarVisibility = (Percent> PercentVisibilityTreshold || FMath::IsNearlyZero(Percent))	//
		? ESlateVisibility::Hidden : ESlateVisibility::Visible;

	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorTreshold ? GoodColor : BadColor;

	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);

	

}