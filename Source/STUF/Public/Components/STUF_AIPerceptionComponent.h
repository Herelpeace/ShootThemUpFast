// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STUF_AIPerceptionComponent.generated.h"


UCLASS()
class STUF_API USTUF_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClosestEnemy() const;
};
