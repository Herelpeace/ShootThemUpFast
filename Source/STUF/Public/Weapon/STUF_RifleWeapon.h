// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "STUF_RifleWeapon.generated.h"

class USTU_WeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class STUF_API ASTUF_RifleWeapon : public ASTUF_BaseWeapon
{
	GENERATED_BODY()
	
public:
	ASTUF_RifleWeapon();
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float TimerBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float DamageAmount = 10.0f;

	// переменная для Niagara эффекта
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USTU_WeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";

	virtual void BeginPlay() override;

	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY();
	UNiagaraComponent* MuzzleFXComponent;

	UPROPERTY();
	UAudioComponent* FireAudioComponent;

	void MakeDamage(const FHitResult &HitResult);

	// спавнит Niagara систему, выставляет видимость
	void InitFX();

	// выставляет фллаг видимости эффекта
	void SetFXActive(bool IsActive);

	void SpawnTraceFX (const FVector& TraceStart, FVector& TraceEnd);

	AController* GetController() const;

};
