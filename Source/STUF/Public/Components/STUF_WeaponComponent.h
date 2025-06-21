// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUF_WeaponComponent.generated.h"

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUF_WeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	ASTUF_BaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUF_BaseWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void SpawnWeapons();

	void AttachWeaponToSocket(ASTUF_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;

	bool CanEquip() const;

	bool CanReload() const;

	template <typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if(!Animation) return nullptr;

		const auto NotifyEvents = Animation->Notifies;

		for (auto NotifyEvent:NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);

			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}

};
