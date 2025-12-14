// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUF_PlayerController.generated.h"

class USTUF_RespawnComponent;

UCLASS()
class STUF_API ASTUF_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTUF_PlayerController();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTUF_RespawnComponent* RespawnComponent;

	//virtual void OnPossess(APawn* InPawn) override;

};
