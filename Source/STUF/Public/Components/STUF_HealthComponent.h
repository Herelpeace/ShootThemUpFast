// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUF_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUF_HealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangeSignature OnHealtChange;

	UFUNCTION(BlueprintCallable, Category = "MyHealth")
	bool IsDead() const {return FMath::IsNearlyZero(Health); }

	float GetHealth() const {return Health;}


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyHealth", meta = (ClapmpMin = "0", ClampMax = "1000"))
	float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal")
		bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal",meta =( EditCondition ="AutoHeal"))
		float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal",meta =( EditCondition ="AutoHeal"))
		float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Heal",meta =( EditCondition ="AutoHeal"))
		float HealModifier = 5.0f;





private:

	float Health = 0;

	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	void HealUpdate();

	void SetHealth(float NewHealth);


};