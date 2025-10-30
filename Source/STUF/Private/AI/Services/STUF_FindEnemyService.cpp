// BGAT studio. All Rights Reserved. 


#include "AI/Services/STUF_FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUF_AIPerceptionComponent.h"


USTUF_FindEnemyService::USTUF_FindEnemyService()
{
	NodeName = "Find Enemy";
}

void USTUF_FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if(Blackboard)
	{
		const auto Controller = OwnerComp.GetOwner();
		const auto PerceptionComponent = STUUtils::GetSTUFPlayerComponent<USTUF_AIPerceptionComponent>(Controller);

		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}

	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}