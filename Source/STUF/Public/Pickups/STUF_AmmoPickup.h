// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUF_BasePickup.h"
#include "STUF_AmmoPickup.generated.h"

class ASTUF_BaseWeapon;

UCLASS()
class STUF_API ASTUF_AmmoPickup : public ASTUF_BasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0",ClampMax = "10.0"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ASTUF_BaseWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
