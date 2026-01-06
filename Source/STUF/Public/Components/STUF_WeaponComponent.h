// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFCoreTypes.h"
#include "STUF_WeaponComponent.generated.h"


class ASTUF_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUF_WeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();
	
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASTUF_BaseWeapon> WeaponType, int32 ClipsAmount);

	bool NeedAmmo(TSubclassOf<ASTUF_BaseWeapon> WeaponType);

	void Zoom (bool Enabled);

	void ResetWeaponState();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	ASTUF_BaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUF_BaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool CanFire() const;

	bool CanEquip() const;

	void EquipWeapon(int32 WeaponIndex);

	
private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUF_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const;

	void OnEmptyClip(ASTUF_BaseWeapon* AmmoEmptyWeapon);

	void ChangeClip();



};
