// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PlayerHUDWidget.h"
#include "Components/STUF_HealthComponent.h"
#include "Components/STUF_WeaponComponent.h"
#include "STUUtils.h"

float USTUF_PlayerHUDWidget::GetHealthPercent() const
{
	// �������� ������ � ���������� HealthComponent � ������� � ���� ������� ��������� �������� � ���������

	const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(GetOwningPlayerPawn());

	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUF_PlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTUFPlayerComponent<USTUF_WeaponComponent>(GetOwningPlayerPawn());

	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUF_PlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTUFPlayerComponent<USTUF_WeaponComponent>(GetOwningPlayerPawn());

	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}


bool  USTUF_PlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(GetOwningPlayerPawn());

	return HealthComponent && !HealthComponent->IsDead();
}

bool  USTUF_PlayerHUDWidget::IsPlayerSpectating() const
{
	// �������� ���������� ������
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}


// ������� �� �������� ����� ��������� �������
/*

USTUF_WeaponComponent* USTUF_PlayerHUDWidget::GetWeaponComponent() const
{
	// �������� ������ � ���������� 
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTUF_WeaponComponent::StaticClass());

	const auto WeaponComponent = Cast<USTUF_WeaponComponent>(Component);

	return WeaponComponent;
}
	
USTUF_HealthComponent* USTUF_PlayerHUDWidget::GetHealthComponent() const
{
	// �������� ������ � ���������� 
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTUF_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<USTUF_HealthComponent>(Component);

	return HealthComponent;
}
*/
//


