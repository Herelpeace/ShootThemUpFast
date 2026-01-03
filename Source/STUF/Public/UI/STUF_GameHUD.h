// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUFCoreTypes.h"
#include "STUF_GameHUD.generated.h"

class USTUF_BaseWidget;

UCLASS()
class STUF_API ASTUF_GameHUD : public AHUD
{
	GENERATED_BODY()

public:
		virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyConfig")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyConfig")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyConfig")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<ESTUMatchState,USTUF_BaseWidget*> GameWidgets;

	UPROPERTY()
	USTUF_BaseWidget* CurrentWidget = nullptr;

	void DrawCrossHair();

	// для делегата, вызывается при изменении состояния игры
	void OnMatchStateChanged(ESTUMatchState State);

};
