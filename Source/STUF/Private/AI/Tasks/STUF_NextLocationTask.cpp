// BGAT studio. All Rights Reserved. 


#include "AI/Tasks/STUF_NextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUF_NextLocationTask::USTUF_NextLocationTask()
{
	// переменная из базового класса, она выводится визуально в редакторе
	NodeName = "NextLocation";
}

EBTNodeResult::Type USTUF_NextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSys) return EBTNodeResult::Failed;

	// просто переменная заглушка, в нее записывается новое значение координат
	FNavLocation NavLocation;

	auto Location = Pawn->GetActorLocation();

	if (!SelfCenter)
	{
		auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));

		if(!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}

	// получаем рандомное значение координат
	const auto Found = NavSys->GetRandomReachablePointInRadius(Location,Radius, NavLocation );

	if(!Found) return EBTNodeResult::Failed;

	// передаем координаты в Blackboard
	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location );

	return EBTNodeResult::Succeeded;
}