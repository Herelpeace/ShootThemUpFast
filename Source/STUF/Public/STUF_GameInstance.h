// BGAT studio. All Rights Reserved. 
/* 
Класс сохраняет данные на всем протяжении игры
не зависит от смены уровня
В блюпринте данного класса будем осуществлять настройки для уровней (имена уровней, картинки)
храним имена уровней
храним настройки управления Master каналом звука

 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUFCoreTypes.h"
#include "STUF_GameInstance.generated.h"

class USoundClass;

UCLASS()
class STUF_API USTUF_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevel() const {return StartupLevel;}				// получаем структуру настроек уровня (имя,картинку)
	void SetStartupLevel(const FLevelData& Data) {StartupLevel = Data;}		// устанавливаем настройки уровня (имя,картинку)

	TArray<FLevelData> GetLevelsData() const {return LevelsData;}				// получаем массив структур настроек уровней (имена,картинки)

	FName GetMenuLevelName() const {return MenuLevelName;}						// получем имя уровня главного меню

	void ToggleVolume();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Levels name must be uniques! "))
	TArray<FLevelData> LevelsData;	// содержит настройки уровня который выбран в главном меню, его картинку, имя, имя отображаемое в виджете

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundClass* MasterSoundClass;

private:
	FLevelData StartupLevel;

};
