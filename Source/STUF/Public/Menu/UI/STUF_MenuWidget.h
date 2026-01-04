// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "UI/STUF_BaseWidget.h"
#include "STUFCoreTypes.h"
#include "STUF_MenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTUF_GameInstance;
class USTUF_LevelItemWidget;
class USoundCue;

UCLASS()
class STUF_API USTUF_MenuWidget : public USTUF_BaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;		// массив с виджетами уровней

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HideAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "USound")
	USoundCue* StartGameSound;		


	virtual void NativeOnInitialized() override;

	// вызывается каждый раз когда завершилась какая нибудь анимация
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;	

private:
	UPROPERTY()
	TArray<USTUF_LevelItemWidget*> LevelItemWidgets;	// массим виджетов с уровнями

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();	// создает кнопки выбора уровней

	void OnLevelSelected(const FLevelData& Data);	// вызывается когда сработает делегат после нажатия на кнопку уровня

	USTUF_GameInstance* GetSTUFGameInstance() const;	// возвращает указатель на наш класс STUF_GameInstance
	
};
