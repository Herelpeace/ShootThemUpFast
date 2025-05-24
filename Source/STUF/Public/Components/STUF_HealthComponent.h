// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUF_HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUF_API USTUF_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUF_HealthComponent();

	float GetHealth() const {return Health;}

	UFUNCTION(BlueprintCallable)
	bool IsDead() const {return Health<=0.0f;}

	FOnDeath OnDeath;
	FOnHealthChange OnHealtChange;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "MyHealth", meta = (ClapmpMin = "0", ClampMax = "1000"))
	float MaxHealth = 100;


private:

	float Health = 0;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );


};