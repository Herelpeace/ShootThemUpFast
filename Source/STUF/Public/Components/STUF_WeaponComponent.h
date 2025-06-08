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

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	TSubclassOf<ASTUF_BaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASTUF_BaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();

};
