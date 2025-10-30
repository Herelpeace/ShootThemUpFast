// BGAT studio. All Rights Reserved. 

// запускаем BehaviorTree (2)
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUF_AIController.generated.h"

class USTUF_AIPerceptionComponent;

UCLASS()
class STUF_API ASTUF_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTUF_AIController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUF_AIPerceptionComponent* STUF_AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick (float DeltaTime) override;
	
private:
	AActor* GetFocusOnActor() const;
};
