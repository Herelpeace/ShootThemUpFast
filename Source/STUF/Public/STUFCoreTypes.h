#pragma once
#include "STUFCoreTypes.generated.h"

// #include "STUFCoreTypes.h"

// file for structures and delegates


// for STUF_BaseWeapon.h
//----------------------------------------------------------------------------------------------------------

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;

};


// for STUF_WeaponComponent.h
//----------------------------------------------------------------------------------------------------------
class ASTUF_BaseWeapon;

// хранит класс оружия и его анимацию перезарядки
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AComponents")
	TSubclassOf<ASTUF_BaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AComponents")
	UAnimMontage* ReloadAnimMontage;
};


// for STUF_HealthComponent.h
//----------------------------------------------------------------------------------------------------------

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float);