// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUF_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class STUF_API ASTUF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUF_Character();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	UCameraComponent* CameraComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// вызывается при движении вперед/ назад
	void MoveForward(float Amount);

	// вызывается при движении влево/вправо
	void MoveRight(float Amount);

};
