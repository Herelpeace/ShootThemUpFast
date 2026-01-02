// BGAT studio. All Rights Reserved. 

// запускаем BehaviorTree с использованием C++
// плавный поворот персонажа при изменении вектора движения

#pragma once

#include "CoreMinimal.h"
#include "Player/STUF_Character.h"
#include "STUF_AICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class STUF_API ASTUF_AICharacter : public ASTUF_Character
{
	GENERATED_BODY()
	
public:
	ASTUF_AICharacter(const FObjectInitializer & ObjInit );

	// переменная для выбора BehaviorTree
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MYAI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MYComponents")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MYAI")
	float HealthVisibilityDistance = 1000.0f;	// расстояние на котором progressBar здоровья становется невидимым

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	virtual void OnHealthChange(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};
