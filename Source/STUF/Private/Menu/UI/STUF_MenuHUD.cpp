// BGAT studio. All Rights Reserved. 


#include "Menu/UI/STUF_MenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUF_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(),MenuWidgetClass);

		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}

	}

}