#pragma once
#include "STUFCoreTypes.generated.h"

// #include "STUFCoreTypes.h"

// file for structures and delegates


// for STUF_BaseWeapon.h
//----------------------------------------------------------------------------------------------------------
// количество патронов и магазинов для оружия

class ASTUF_BaseWeapon;
class UMaterialInterface;
class UNiagaraSystem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature,ASTUF_BaseWeapon*);

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
// хранит класс оружия и его анимацию перезарядки

class ASTUF_BaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyConfigWeapon")
	TSubclassOf<ASTUF_BaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyConfigWeapon")
	UAnimMontage* ReloadAnimMontage;
};


// for STUF_BaseWeapon.h
//----------------------------------------------------------------------------------------------------------
// хранит иконку оружия и иконку прицела для него 

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category ="MyConfigWeaponUI")
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyConfigWeaponUI")
	UTexture2D* CrossHairIcon;

};


// for STUF_HealthComponent.h
//----------------------------------------------------------------------------------------------------------

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float);


// VFX
//----------------------------------------------------------------------------------------------------------
// храним настройки для текущей декали

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX");
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);

	UPROPERTY (EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;
};

// VFX
//----------------------------------------------------------------------------------------------------------
// объединяет Niagara эффект и декаль

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX");
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX");
	FDecalData DecalData;
};