// BGAT studio. All Rights Reserved. 


#include "Weapon/Components/STU_WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USTU_WeaponFXComponent::USTU_WeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// ����������� ������ �������
void USTU_WeaponFXComponent::PlayImpactFx(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();

		//��������� ���� �� � ����� ���������� ������ ��� ������ ����������� ���������
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap [PhysMat];

		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
