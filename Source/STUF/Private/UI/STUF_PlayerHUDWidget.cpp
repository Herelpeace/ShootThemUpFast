// BGAT studio. All Rights Reserved. 


#include "UI/STUF_PlayerHUDWidget.h"
#include "Components/STUF_HealthComponent.h"
#include "Components/STUF_WeaponComponent.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"
#include "Player/STUF_PlayerState.h"


void USTUF_PlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this,&USTUF_PlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void USTUF_PlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	// получаем доступ к компоненту HealthComponent и вызывем у него функцию получения здоровья в процентах

	const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(NewPawn);

	if (HealthComponent && !HealthComponent->OnHealtChange.IsBoundToObject(this ))
	{
		HealthComponent->OnHealtChange.AddUObject(this, &USTUF_PlayerHUDWidget::OnHealthChanged);
	}

	UpdateHealthBar();
}


void USTUF_PlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();

		if (!IsAnimationPlaying(DamageAnimation))
		{
			PlayAnimation(DamageAnimation); 
		}
	}

	UpdateHealthBar();
}


float USTUF_PlayerHUDWidget::GetHealthPercent() const
{
	// получаем доступ к компоненту HealthComponent и вызывем у него функцию получения здоровья в процентах

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
	// получаем контроллер игрока
	const auto Controller = GetOwningPlayer();

	return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 USTUF_PlayerHUDWidget::GetKillsNum() const
{
	// получаем контроллер игрока
	const auto Controller = GetOwningPlayer();
	if(!Controller) return 0;

	const auto PlayerState = Cast<ASTUF_PlayerState>(Controller->PlayerState);
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

void USTUF_PlayerHUDWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorTreshold ? GoodColor : BadColor);
	}
}

FString USTUF_PlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
	const int32 MaxLen = 3;
	const TCHAR PrefixSymbol = '0';

	auto BulletStr = FString::FromInt(BulletsNum);
	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

	if (SymbolsNumToAdd > 0)
	{
		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
	}

	return BulletStr;
}


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


