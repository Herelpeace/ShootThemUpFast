// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUF_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUF_HealthComponent;
class UTextRenderComponent;
class ASTUF_BaseWeapon;

UCLASS()
class STUF_API ASTUF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUF_Character( const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AComponents")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AComponents")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "AComponents")
	USTUF_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "AComponents")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	float LifaSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1500.0f);

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "AComponents")
	TSubclassOf<ASTUF_BaseWeapon> WeaponClass;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// �������� ������� �� ��� � ��������� (������� Shift � ������)
	UFUNCTION(BlueprintCallable, Category = "AComponents")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "AComponents")
	float GetMovementDirection() const;


private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	// ���������� ��� �������� ������/ �����
	void MoveForward(float Amount);

	// ���������� ��� �������� �����/������
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();
	void OnDeath();
	void OnHealthChange(float Health);

	UFUNCTION() // ������������ �������
	void OnGroundLanded(const FHitResult& Hit);

	void SpawnWeapon();

};
