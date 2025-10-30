// BGAT studio. All Rights Reserved. 

// реализация запуска BehaviorTree

#include "AI/STUF_AIController.h"
#include "AI/STUF_AICharacter.h"
#include "Components/STUF_AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTUF_AIController::ASTUF_AIController()
{
	// создвем наш AIPercaptionComponent
	STUF_AIPerceptionComponent = CreateDefaultSubobject<USTUF_AIPerceptionComponent>("STUF_AIPerceptionComponent");
	SetPerceptionComponent(*STUF_AIPerceptionComponent);
}

void ASTUF_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = GetFocusOnActor();

	// указываем AI какого актора держать в фокусе
	SetFocus(AimActor );
}

void ASTUF_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUFCharacter = Cast<ASTUF_AICharacter>(InPawn);

	if (STUFCharacter)
	{
		// запускаем BehaviorTree
		RunBehaviorTree(STUFCharacter->BehaviorTreeAsset );
	}

}

AActor* ASTUF_AIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));

}