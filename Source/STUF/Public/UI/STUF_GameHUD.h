// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUF_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API ASTUF_GameHUD : public AHUD
{
	GENERATED_BODY()

public:
		virtual void DrawHUD() override;

private:
	void DrawCrossHair();
	
};
