// BGAT studio. All Rights Reserved. 


#include "AI/Services/STUF_FireTService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUF_WeaponComponent.h"
#include "STUUtils.h"

USTUF_FireTService::USTUF_FireTService()
{
	NodeName = "Fire";
}

	
void USTUF_FireTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	
	if (Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUFPlayerComponent<USTUF_WeaponComponent>(Controller->GetPawn());

		if (WeaponComponent)
		{
			HasAim?WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}