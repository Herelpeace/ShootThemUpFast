// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUF_NextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API USTUF_NextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USTUF_NextLocationTask();

	// вызывается при старте Task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYAI")
	float Radius = 1000.0f;

	// переменная для Blackboard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYAI")
	FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYAI")
	bool SelfCenter = true;

	// ключ для объекта относительно которого находим рандомеую точку при атаке
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYAI", meta = (EditConfition = "!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;

};
