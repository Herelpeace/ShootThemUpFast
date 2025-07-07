// BGAT studio. All Rights Reserved. 


#include "Pickups/STUF_AmmoPickup.h"
#include "Logging/StructuredLog.h"
#include "Components/STUF_HealthComponent.h"
#include "Components/STUF_WeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup,All,All);

bool ASTUF_AmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(PlayerPawn);

	if (!HealthComponent|| HealthComponent->IsDead()) return false;

	const auto WeaponComponent = STUUtils::GetSTUFPlayerComponent<USTUF_WeaponComponent>(PlayerPawn);

	if(!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);

	UE_LOGFMT(LogAmmoPickup,Warning, "Ammo wat taken!!");

	return true;
}