// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUF_Character.generated.h"


class USTUF_HealthComponent;
class USTUF_WeaponComponent;


UCLASS()
class STUF_API ASTUF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUF_Character( const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "AComponents")
	USTUF_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	float LifaSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1500.0f);

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AComponent")
	USTUF_WeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// проверят включен ли бег у персонажа (клавиша Shift и вперед)
	UFUNCTION(BlueprintCallable, Category = "AComponents")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "AComponents")
	float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

private:
	void OnHealthChange(float Health, float HealthDelta);

	UFUNCTION() // динамический делегат
	void OnGroundLanded(const FHitResult& Hit);

};
