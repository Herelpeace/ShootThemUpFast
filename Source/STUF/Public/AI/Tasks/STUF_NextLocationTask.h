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

	// ���������� ��� ������ Task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYAI")
	float Radius = 1000.0f;

	// ���������� ��� Blackboard
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYAI")
	FBlackboardKeySelector AimLocationKey;

};
