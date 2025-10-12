// BGAT studio. All Rights Reserved. 


#include "Weapon/Components/STU_WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet//GameplayStatics.h"
#include "Components/DecalComponent.h"

USTU_WeaponFXComponent::USTU_WeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// ����������� ������ �������
void USTU_WeaponFXComponent::PlayImpactFx(const FHitResult& Hit)
{
	auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();

		//��������� ���� �� � ����� ���������� ������ ��� ������ ����������� ���������
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap [PhysMat];

		}
	}

	// spawn Niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),	//
		ImpactData.NiagaraEffect,								//
		Hit.ImpactPoint,										//
		Hit.ImpactNormal.Rotation());

	// spawn Decals
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),	//
	ImpactData.DecalData.Material,						//
	ImpactData.DecalData.Size,							//
	Hit.ImpactPoint,									//
	Hit.ImpactNormal.Rotation()	);

	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

}
