// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PlayerHUDWidget.h"
#include "Components/STUF_HealthComponent.h"

float USTUF_PlayerHUDWidget::GetHealthPercent() const
{
	// получаем доступ к компоненту HealthComponent и вызывем у него функцию получения здоровья в процентах
	const auto Player = GetOwningPlayerPawn();

	const auto Component = Player->GetComponentByClass(USTUF_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<USTUF_HealthComponent>(Component);

	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}