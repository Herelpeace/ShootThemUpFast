// BGAT studio. All Rights Reserved. 


#include "Menu/UI/STUF_LevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUF_LevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton)
	{
		// нажимаем кнопку SelectedButton, в кнопке вызываем делегат который меняет данные в структуре данных уровня
		LevelSelectButton->OnClicked.AddDynamic(this, &USTUF_LevelItemWidget::OnLevelItemClicked); 
	}
}

// callback функция, вызывается при нажатии на кнопку LevelSelectedButton
void USTUF_LevelItemWidget::OnLevelItemClicked()
{
	// вызываем делегат для структуры FLevelData
	OnLevelSelected.Broadcast(LevelData);
}

void USTUF_LevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}

}


// включает отображение рамки в зависимости от того выбран уровень или нет
void USTUF_LevelItemWidget::SetSelected(bool IsSelected)
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
	}
}


