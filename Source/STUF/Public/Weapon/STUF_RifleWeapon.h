// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "STUF_RifleWeapon.generated.h"

class USTU_WeaponFXComponent;
class UNiagaraComponent;

UCLASS()
class STUF_API ASTUF_RifleWeapon : public ASTUF_BaseWeapon
{
	GENERATED_BODY()
	
public:
	ASTUF_RifleWeapon();
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	// ���������� ��� Niagara �������
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USTU_WeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float TimerBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float DamageAmount = 10.0f;

	virtual void BeginPlay() override;

	virtual void MakeShot() override;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult &HitResult);

private:
	FTimerHandle ShotTimerHandle;

	UPROPERTY();
	UNiagaraComponent* MuzzleFXComponent;

	// ������� Niagara �������, ���������� ���������
	void InitMuzzleFX();

	// ���������� ����� ��������� �������
	void SetMuzzleFXVisibility(bool Visible);

};
