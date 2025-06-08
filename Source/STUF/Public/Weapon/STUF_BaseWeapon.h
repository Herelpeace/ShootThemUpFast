// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUF_BaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class STUF_API ASTUF_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUF_BaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "MyComponents")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float TimerBetweenShots = 0.1f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite);
	float BulletSpread = 1.5f;

	virtual void BeginPlay() override;

	void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint( FVector& ViewLocation,FRotator& ViewRotation) const;

	FVector GetMazzleWorldLocation() const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd);

	void MakeDamage(const FHitResult &HitResult);

private:
	FTimerHandle ShotTimerHandle;

};
