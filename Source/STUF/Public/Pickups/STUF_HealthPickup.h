// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUF_BasePickup.h"
#include "STUF_HealthPickup.generated.h"

UCLASS()
class STUF_API ASTUF_HealthPickup : public ASTUF_BasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"));
	float HealthAmount = 100.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};


  