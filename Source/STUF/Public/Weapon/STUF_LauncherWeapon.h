// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "STUF_LauncherWeapon.generated.h"

class ASTUF_Projectiles;


UCLASS()
class STUF_API ASTUF_LauncherWeapon : public ASTUF_BaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASTUF_Projectiles> ProjectileClass;

	virtual void MakeShot()  override;
	
};
