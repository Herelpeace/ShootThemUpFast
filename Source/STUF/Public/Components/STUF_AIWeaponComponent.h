// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/STUF_WeaponComponent.h"
#include "STUF_AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API USTUF_AIWeaponComponent : public USTUF_WeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
	
};
