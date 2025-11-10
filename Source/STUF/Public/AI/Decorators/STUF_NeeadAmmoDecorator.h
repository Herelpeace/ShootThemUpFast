// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUF_NeeadAmmoDecorator.generated.h"


class ASTUF_BaseWeapon;

UCLASS()
class STUF_API USTUF_NeeadAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USTUF_NeeadAmmoDecorator();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ASTUF_BaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};

