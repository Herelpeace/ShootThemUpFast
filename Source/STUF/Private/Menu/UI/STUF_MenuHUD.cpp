// BGAT studio. All Rights Reserved. 


#include "Menu/UI/STUF_MenuHUD.h"
#include "UI/STUF_BaseWidget.h"

void ASTUF_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<USTUF_BaseWidget>(GetWorld(),MenuWidgetClass);

		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}

	}

}