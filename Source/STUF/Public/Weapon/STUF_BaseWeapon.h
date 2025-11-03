// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUFCoreTypes.h"
#include "STUF_BaseWeapon.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class STUF_API ASTUF_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUF_BaseWeapon();

	FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip();
	bool CanReload() const;

	FWeaponUIData GetUIData() const {return UIData;}
	FAmmoData GetAmmoData() const {return CurrentAmmo;}

	bool TryToAddAmmo(int32 ClipsAmount);
	bool IsAmmoEmpty() const;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "MyComponents")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyComponents")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyComponents")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	FAmmoData DefaultAmmo{15,10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyWeaponUIImage")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint( FVector& ViewLocation,FRotator& ViewRotation) const;

	FVector GetMazzleWorldLocation() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	bool IsClipsEmpty() const;
	void LogAmmo();
	bool IsAmmoFull() const;

	UNiagaraComponent* SpawnMuzzleFX();
	
	
private:
	FAmmoData CurrentAmmo;


};
