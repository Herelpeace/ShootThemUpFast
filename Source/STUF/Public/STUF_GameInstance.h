// BGAT studio. All Rights Reserved. 
/* 
Класс содержит переменные данные в которых сохраняются на всем протяжении игры
не зависит от смены уровня

 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUF_GameInstance.generated.h"

UCLASS()
class STUF_API USTUF_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FName GetStartupLevelName() const {return StartupLevelName;}
	FName GetMenuLevelName() const {return MenuLevelName;}
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;






};
