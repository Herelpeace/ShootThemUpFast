#pragma once

// #include "STUUtils.h"

// �������� ������ ���������� USTUF_HealthComponent, USTUF_WeaponComponent 
class STUUtils
{
public:
	template<typename T>
	static T* GetSTUFPlayerComponent(APawn* PlayerPawn)
	{
		// �������� ������ � ���������� 
		if(!PlayerPawn) return nullptr;
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return  Cast<T>(Component);

	}
};


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

