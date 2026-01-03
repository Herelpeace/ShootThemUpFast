// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "UI/STUF_BaseWidget.h"
#include "STUF_PauseWidget.generated.h"

class UButton;

UCLASS()
class STUF_API USTUF_PauseWidget : public USTUF_BaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	// биндим виджет кнопки на функцию
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;
	
private:
	UFUNCTION()
	void OnClearPause();

};
