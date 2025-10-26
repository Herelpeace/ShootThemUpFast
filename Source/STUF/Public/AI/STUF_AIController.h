// BGAT studio. All Rights Reserved. 

// запускаем BehaviorTree (2)
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUF_AIController.generated.h"


UCLASS()
class STUF_API ASTUF_AIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

};
