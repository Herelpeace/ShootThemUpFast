// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PlayerHUDWidget.h"
#include "Components/STUF_HealthComponent.h"
#include "Components/STUF_WeaponComponent.h"

float USTUF_PlayerHUDWidget::GetHealthPercent() const
{
	// �������� ������ � ���������� HealthComponent � ������� � ���� ������� ��������� �������� � ���������
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USTUF_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<USTUF_HealthComponent>(Component);

	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUF_PlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	// �������� ������ � ���������� HealthComponent � ������� � ���� ������� ��������� �������� � ���������
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return false;

	const auto Component = Player->GetComponentByClass(USTUF_WeaponComponent::StaticClass());

	const auto WeaponComponent = Cast<USTUF_WeaponComponent>(Component);

	if(!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);

}