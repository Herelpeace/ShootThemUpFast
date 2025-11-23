// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUF_GameDataWidget.generated.h"

class ASTUF_GameModeBase;
class ASTUF_PlayerState;

UCLASS()
class STUF_API USTUF_GameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondRemaining() const;

private:
	ASTUF_GameModeBase* GetSTUGameMode() const;
	ASTUF_PlayerState* GetSTUPlayerState() const;

	
};
