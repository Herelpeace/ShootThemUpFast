// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFCoreTypes.h"
#include "STUF_HealthComponent.generated.h"

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUF_HealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangeSignature OnHealtChange;

	UFUNCTION(BlueprintCallable, Category = "AComponents")
	bool IsDead() const {return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "AComponents")
	float GetHealthPercent() const {return Health/MaxHealth;};

	float GetHealth() const {return Health;}

	bool TryToAddHealth(float HealthAmount);

	bool IsHealthFull() const;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "AComponents", meta = (ClapmpMin = "0", ClampMax = "1000"))
	float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal",meta =( EditCondition ="AutoHeal"))
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal",meta =( EditCondition ="AutoHeal"))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal",meta =( EditCondition ="AutoHeal"))
	float HealModifier = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;


private:

	float Health = 0;

	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	void HealUpdate();

	void SetHealth(float NewHealth);

	void PlayCameraShake();

	void Killed(AController* KillerController);


};