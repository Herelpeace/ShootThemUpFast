// BGAT studio. All Rights Reserved. 

// ���������� ������� BehaviorTree

#include "AI/STUF_AIController.h"
#include "AI/STUF_AICharacter.h"


void ASTUF_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUFCharacter = Cast<ASTUF_AICharacter>(InPawn);

	if (STUFCharacter)
	{
		// ��������� BehaviorTree
		RunBehaviorTree(STUFCharacter->BehaviorTreeAsset );
	}

}