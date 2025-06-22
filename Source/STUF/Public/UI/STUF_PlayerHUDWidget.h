// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUF_PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API USTUF_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyConfig")
	float GetHealthPercent() const;

	
};
