// BGAT studio. All Rights Reserved. 


#include "Pickups/STUF_HealthPickup.h"
#include "Logging/StructuredLog.h"
#include "Components/STUF_HealthComponent.h"
#include "STUUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup,All,All);

bool ASTUF_HealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(PlayerPawn);
	if(!HealthComponent) return false;
	return HealthComponent->TryToAddHealth(HealthAmount);
}


