// BGAT studio. All Rights Reserved. 


#include "Menu/UI/STUF_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUF_GameInstance.h"
#include "Logging/StructuredLog.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/STUF_LevelItemWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUFMenuWidget, All, All);

void USTUF_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUF_MenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USTUF_MenuWidget::OnQuitGame);
	}

	InitLevelItems();
}

// создает кнопки выбора уровней, вызывается один раз при инициализации виджета
void USTUF_MenuWidget::InitLevelItems()
{
	const auto STUGameInstance = GetSTUFGameInstance();

	if(!STUGameInstance) return;

	checkf( STUGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty"));

	if(!LevelItemBox) return;	// если не установлен HorizontalBox

	LevelItemBox->ClearChildren();	// очищаем данные в боксе

	for (auto LevelData : STUGameInstance->GetLevelsData())		// получаем струтуры FLevelData из класса STUF_GameInstance
	{
		const auto LevelItemWidget = CreateWidget<USTUF_LevelItemWidget>(GetWorld(), LevelItemWidgetClass);		// создаем виджет типа STUF_LevelItemWidget

		if(!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);	// в созданном виджете заплняем структуру LevelData, данными из STUF_GameInstance
		LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUF_MenuWidget::OnLevelSelected);	// подписываемся на делегат

		LevelItemBox->AddChild(LevelItemWidget);	// добавлем в HorizontalBox
		LevelItemWidgets.Add(LevelItemWidget);		// добавляем в массив LevelItemWidgets
	}

	// если стартовый уровень не задан
	if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(STUGameInstance->GetStartupLevel());
	}

}

// вызывается когда сработает делегат после нажатия на кнопку уровня
void USTUF_MenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto STUGameInstance = GetSTUFGameInstance();

	if(!STUGameInstance) return;

	STUGameInstance->SetStartupLevel(Data);

	for (auto LevelItemWidget : LevelItemWidgets)
	{
		if (LevelItemWidget)
		{
			// true если имя в колбэк такое же как имя в массиве текущих виджетов
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);	// устанавливаем видимость рамки
		}
	}
}


void USTUF_MenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);

}


// вызывается каждый раз когда завершилась какая нибудь анимация
void USTUF_MenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation!=HideAnimation) return;

	// загрузка уровня после того как прошла анимация загрузки
	const auto STUGameInstance = GetSTUFGameInstance();

	if(!STUGameInstance) return;

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);

}

void USTUF_MenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

// возвращает указатель на наш класс STUF_GameInstance
USTUF_GameInstance* USTUF_MenuWidget::GetSTUFGameInstance() const
{
	if(!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<USTUF_GameInstance>();
}