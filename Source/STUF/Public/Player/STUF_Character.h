// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUF_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUF_HealthComponent;
class UTextRenderComponent;

UCLASS()
class STUF_API ASTUF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUF_Character( const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "MyComponents")
	USTUF_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "MyComponents")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "MyComponents")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "MyComponents")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1500.0f);

	UPROPERTY(EditDefaultsOnly, Category = "MyComponents")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// проверят включен ли бег у персонажа (клавиша Shift и вперед)
	UFUNCTION(BlueprintCallable, Category = "MyMovement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "MyMovement")
	float GetMovementDirection() const;


private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	// вызывается при движении вперед/ назад
	void MoveForward(float Amount);

	// вызывается при движении влево/вправо
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();
	void OnDeath();
	void OnHealthChange(float Health);

	UFUNCTION() // динамический делегат
	void OnGroundLanded(const FHitResult& Hit);


};
