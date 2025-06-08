// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "STUF_RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API ASTUF_RifleWeapon : public ASTUF_BaseWeapon
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float TimerBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float BulletSpread = 1.5f;

	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;

};
