// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUFCoreTypes.h"
#include "STUF_LevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class STUF_API USTUF_LevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelectedSignature OnLevelSelected;		// экземпляр делегата

	void SetLevelData (const FLevelData& Data);

	FLevelData GetLevelData() const {return LevelData;}

	void SetSelected (bool IsSelected);		// включает отображение рамки в зависимости от того выбран уровень или нет

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectButton;		// кнопка выбранного уровня

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;		// имя уровня в виджете

	UPROPERTY(meta = (BindWidget))		//	картинка уровня
	UImage* LevelImage;
		
	UPROPERTY(meta = (BindWidget))		//	картинка рамки
	UImage* FrameImage;

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelItemClicked();		// callback функция, вызывается при нажатии на кнопку LevelSelectedButton
};
