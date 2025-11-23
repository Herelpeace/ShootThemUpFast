// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUF_RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_RespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUF_RespawnComponent();

	void Respawn (int32 RespawnTime);

private:
	FTimerHandle RespawnTimerHandle;

	int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();

};