// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Player/STUF_Character.h"
#include "STUF_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class STUF_API ASTUF_PlayerCharacter : public ASTUF_Character
{
	GENERATED_BODY()

	public:
	// Sets default values for this character's properties
	ASTUF_PlayerCharacter( const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AComponents")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AComponents")
	UCameraComponent* CameraComponent;
	
	virtual void OnDeath() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// проверят включен ли бег у персонажа (клавиша Shift и вперед)
	virtual bool IsRunning() const override;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	// вызывается при движении вперед/ назад
	void MoveForward(float Amount);

	// вызывается при движении влево/вправо
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();


};
