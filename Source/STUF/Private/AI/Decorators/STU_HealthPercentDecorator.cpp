// BGAT studio. All Rights Reserved. 
/*
ƒекорактор дл€ поиска пикапа здоровь€.
≈сли функци€ CalculateRawConditionValue возвращает true то выполн€етс€ ветка поведени€ под декоратором.
	- если Controller существует, true
	- если существует HealthComponent и персонаж жив, true 
*/


#include "AI/Decorators/STU_HealthPercentDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUF_HealthComponent.h"


USTU_HealthPercentDecorator::USTU_HealthPercentDecorator()
{
	NodeName = "HealthPercent";
}

bool USTU_HealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent()<=HealthPercent; 

}