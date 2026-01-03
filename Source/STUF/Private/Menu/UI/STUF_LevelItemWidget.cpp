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
		LevelSelectButton->OnHovered.AddDynamic(this, &USTUF_LevelItemWidget::OnLevelItemHovered); 
		LevelSelectButton->OnUnhovered.AddDynamic(this, &USTUF_LevelItemWidget::OnLevelItemUnhovered); 
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
	FLinearColor MenuTileColor(0.6f, 1.0f, 0.6f, 1.0f);

	if (LevelImage)
	{
		LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::White : MenuTileColor );
	}

	FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden );
}

// вызывается при наведении на кнопку
void USTUF_LevelItemWidget::OnLevelItemHovered()
{
		if (FrameImage)
	{
		//FrameImage->SetVisibility(ESlateVisibility::Visible);
	}

}

// вызывается когда убираем курсор мыши с кнопки
void USTUF_LevelItemWidget::OnLevelItemUnhovered()
{
		if (FrameImage)
	{
		//FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}

}

