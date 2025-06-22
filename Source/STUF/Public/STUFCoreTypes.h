#pragma once
#include "STUFCoreTypes.generated.h"

// #include "STUFCoreTypes.h"

// file for structures and delegates


// for STUF_BaseWeapon.h
//----------------------------------------------------------------------------------------------------------
// ���������� �������� � ��������� ��� ������

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
// ������ ����� ������ � ��� �������� �����������

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
// ������ ������ ������ � ������ ������� ��� ���� 

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