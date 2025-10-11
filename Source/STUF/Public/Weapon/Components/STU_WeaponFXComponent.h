// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_WeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTU_WeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTU_WeaponFXComponent();

void PlayImpactFx(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "VFX")
	UNiagaraSystem* Effect;

		
};
