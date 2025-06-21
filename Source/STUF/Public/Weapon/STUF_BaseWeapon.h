// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUFCoreTypes.h"
#include "STUF_BaseWeapon.generated.h"



class USkeletalMeshComponent;




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

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "MyComponents")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyComponents")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyComponents")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyComponents")
	FAmmoData DefaultAmmo{15,10, false};

	virtual void BeginPlay() override;

	virtual void MakeShot();

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint( FVector& ViewLocation,FRotator& ViewRotation) const;

	FVector GetMazzleWorldLocation() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd);

	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipsEmpty() const;
	void LogAmmo();
	
private:
	FAmmoData CurrentAmmo;


};
