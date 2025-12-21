// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUFCoreTypes.h"
#include "STUF_GameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class STUF_API USTUF_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;		// бокс в котором размещаем виджеты -строки

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;		// виджеты-строки с информацией

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;		// кнопка перезагрузки

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();

};
