// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "STUFCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUF_PlayerHUDWidget.generated.h"


UCLASS()
class STUF_API USTUF_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyFunctionUI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "MyFunctionUI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category = "MyFunctionUI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "MyFunctionUI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category ="MyFunctionUI")
	bool IsPlayerSpectating() const;
	
	UFUNCTION(BlueprintImplementableEvent , Category ="MyFunctionUI")
	void OnTakeDamage();

protected:
	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged (float Health, float HealthDelta);

	void OnNewPawn(APawn* NewPawn);
	

};
