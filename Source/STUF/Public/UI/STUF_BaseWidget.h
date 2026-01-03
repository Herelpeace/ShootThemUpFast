// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUF_BaseWidget.generated.h"


UCLASS()
class STUF_API USTUF_BaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();	// запуск анимации в виджете

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;
	
};
