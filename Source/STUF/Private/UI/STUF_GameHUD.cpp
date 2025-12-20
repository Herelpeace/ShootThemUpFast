// BGAT studio. All Rights Reserved. 


#include "UI/STUF_GameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUF_GameModeBase.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUFGameHUD, All, All);

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

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUF_GameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUF_GameHUD::OnMatchStateChanged);
		}
	}
}

// для делегата, вызывается при изменении состояния игры
void ASTUF_GameHUD::OnMatchStateChanged(ESTUMatchState State)
{
	UE_LOGFMT(LogSTUFGameHUD, Warning, "Match state changed: {1}", *UEnum::GetValueAsString(State));
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