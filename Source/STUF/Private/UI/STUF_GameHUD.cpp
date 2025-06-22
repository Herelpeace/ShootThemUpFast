// BGAT studio. All Rights Reserved. 


#include "UI/STUF_GameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTUF_GameHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();

}

void ASTUF_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void ASTUF_GameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX*0.5f,Canvas->SizeY*0.5f);

	const float HalfLintSize = 20.0f;	// половина линии
	const float LineThickness = 2.0f;	// толщина линии
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min-HalfLintSize,Center.Max,Center.Min+HalfLintSize,Center.Max,LineColor,LineThickness);
	DrawLine(Center.Min,Center.Max-HalfLintSize,Center.Min,Center.Max+HalfLintSize,LineColor,LineThickness);

}