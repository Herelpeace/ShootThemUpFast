// BGAT studio. All Rights Reserved. 


#include "UI/STUF_BaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUF_BaseWidget::Show()
{
	PlayAnimation(ShowAnimation); 
	UGameplayStatics::PlaySound2D(GetWorld(),OpenSound);
}