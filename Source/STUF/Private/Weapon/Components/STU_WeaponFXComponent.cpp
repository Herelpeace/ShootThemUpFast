// BGAT studio. All Rights Reserved. 


#include "Weapon/Components/STU_WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

USTU_WeaponFXComponent::USTU_WeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// проигрываем эффект ниагары
void USTU_WeaponFXComponent::PlayImpactFx(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
