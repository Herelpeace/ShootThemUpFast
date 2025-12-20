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

	// добавлем пару ключ-значение в массив (состояние игры - виджет)
	GameWidgets.Add(ESTUMatchState::InProgress,CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause,CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if(!GameWidget) continue;

		// добавляем все найденые виджеты на экран
		GameWidget->AddToViewport();

		// делвем их невидимыми
		GameWidget->SetVisibility(ESlateVisibility::Hidden);

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
	if (CurrentWidget)
	{
		// делвем невидимым текущий виджет
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		// в качестве текущего виджета выбираем тот который соответствует состоянию игры
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		// делвем видимым новый текущий виджет
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}


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