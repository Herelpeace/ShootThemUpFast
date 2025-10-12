// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFCoreTypes.h"
#include "STU_WeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTU_WeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTU_WeaponFXComponent();

void PlayImpactFx(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "VFX")
	TMap<UPhysicalMaterial*,FImpactData> ImpactDataMap;	
};
