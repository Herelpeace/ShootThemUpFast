// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUF_HealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class STUF_API USTUF_HealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthPercent (float Percent);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentVisibilityTreshold = 0.8f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float PercentColorTreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor GoodColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor BadColor = FLinearColor::Red;

};
