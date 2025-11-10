// BGAT studio. All Rights Reserved. 
/*
ƒекорактор дл€ поиска пикапа боеприспасов.
≈сли функци€ CalculateRawConditionValue возвращает true то выполн€етс€ ветка поведени€ под декоратором.
	- если Controller существует, true
	- если существует WeaponComponent и персонажу требуютс€ паторны, true 
*/

#include "AI/Decorators/STUF_NeeadAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUF_WeaponComponent.h"


USTUF_NeeadAmmoDecorator::USTUF_NeeadAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool USTUF_NeeadAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = STUUtils::GetSTUFPlayerComponent<USTUF_WeaponComponent>(Controller->GetPawn());

	if(!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);

}