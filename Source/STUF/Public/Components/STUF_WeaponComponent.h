// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUF_WeaponComponent.generated.h"

class ASTUF_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUF_WeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	TArray<TSubclassOf<ASTUF_BaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponArmorySocketName = "ArmorySocket";

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASTUF_BaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUF_BaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUF_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(int32 WeaponIndex);

};
