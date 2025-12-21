#pragma once
#include "Player/STUF_PlayerState.h"

// #include "STUUtils.h"

// получаем классы компонетов USTUF_HealthComponent, USTUF_WeaponComponent 
class STUUtils
{
public:
	template<typename T>
	static T* GetSTUFPlayerComponent(AActor* PlayerPawn)
	{
		// получаем доступ к компоненту 
		if(!PlayerPawn) return nullptr;
		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return  Cast<T>(Component);
	}

	bool static AreEnwmies(AController * Controller1, AController * Controller2)
	{
		if(!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const auto PlayerState1 = Cast<ASTUF_PlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<ASTUF_PlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();

	}

	// for STUF_GameOverWidget.h
	// преобразует int -> String -> text

	static FText TextFromInt(int32 Number) {return FText::FromString(FString::FromInt(Number));}


};






// функции до создания одной шаблонной функции
/*

USTUF_WeaponComponent* USTUF_PlayerHUDWidget::GetWeaponComponent() const
{
	// получаем доступ к компоненту 
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTUF_WeaponComponent::StaticClass());

	const auto WeaponComponent = Cast<USTUF_WeaponComponent>(Component);

	return WeaponComponent;
}
	
USTUF_HealthComponent* USTUF_PlayerHUDWidget::GetHealthComponent() const
{
	// получаем доступ к компоненту 
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return nullptr;

	const auto Component = Player->GetComponentByClass(USTUF_HealthComponent::StaticClass());

	const auto HealthComponent = Cast<USTUF_HealthComponent>(Component);

	return HealthComponent;
}
*/
//

