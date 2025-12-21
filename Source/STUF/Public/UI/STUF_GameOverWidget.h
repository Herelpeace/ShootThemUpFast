// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUFCoreTypes.h"
#include "STUF_GameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class STUF_API USTUF_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;		// бокс в котором размещаем виджеты -строки

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;		// виджеты-строки с информацией

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdatePlayersStat();

};
