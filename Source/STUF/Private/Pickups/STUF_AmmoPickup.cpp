// BGAT studio. All Rights Reserved. 


#include "Pickups/STUF_AmmoPickup.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup,All,All);

bool ASTUF_AmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOGFMT(LogAmmoPickup,Warning, "Ammo wat taken!!");

	return true;
}