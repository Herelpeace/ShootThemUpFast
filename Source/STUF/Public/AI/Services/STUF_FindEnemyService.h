// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUF_FindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API USTUF_FindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USTUF_FindEnemyService();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
