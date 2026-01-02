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

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeSignature, float, float);


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

// GameMode
//----------------------------------------------------------------------------------------------------------
// храним настройки игры

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"));
	int32 PlayersNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"));
	int32 RoundsNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"));
	int32 RoundTime = 2;	// in secound

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLinearColor> TeamColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"));
	int32 RespawnTime = 5;	// in secound

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"));
	int32 MinTimeAcceptRespawn = 10;	// in secound

};


// State для GameMode в котором хранится текущее состояние игры
//----------------------------------------------------------------------------------------------------------
// хранит состояние игры, содержит делегат который оповещает об изменении состояния

UENUM(BlueprintType)
enum class ESTUMatchState:uint8
{
	WaitingToStart = 0,	// ожидание начала игры
	InProgress,			// игра
	Pause,				// пауза
	GameOver			// игра окончена
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESTUMatchState);


// Структура хранит данные для виджета LevelItem
//----------------------------------------------------------------------------------------------------------
// делегат передает данные от виджета LevelItem к MainMenu, определяет какой уровень выбран

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game");
	FName LevelName = NAME_None;	// имя уровня

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game");
	FName LevelDisplayName = NAME_None;		// уровень который отображем в виджете

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game");
	UTexture2D* LevelThumb;		// картинка для отображения (указатель на текстуру)

};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);	// принимает параметр по константной ссылке