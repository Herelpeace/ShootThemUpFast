// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUF_GameInstance.generated.h"

UCLASS()
class STUF_API USTUF_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FString TestString = "Hello game!";

};
