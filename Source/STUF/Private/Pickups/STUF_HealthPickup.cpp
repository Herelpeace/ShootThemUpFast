// BGAT studio. All Rights Reserved. 


#include "Pickups/STUF_HealthPickup.h"
#include "Logging/StructuredLog.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup,All,All);

bool ASTUF_HealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOGFMT(LogHealthPickup,Warning, "Health wat taken!!");

	return true;
}


