// BGAT studio. All Rights Reserved. 


#include "AI/Services/STUF_ChangeWeaponService.h"
#include "Components/STUF_WeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"


USTUF_ChangeWeaponService::USTUF_ChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUF_ChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUFPlayerComponent<USTUF_WeaponComponent>(Controller->GetPawn());

		if (WeaponComponent && Probability>0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}

	}


	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds);


}