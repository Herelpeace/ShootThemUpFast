// BGAT studio. All Rights Reserved. 


#include "Player/STUF_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"



// Sets default values
ASTUF_Character::ASTUF_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation=true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);


}

// Called when the game starts or when spawned
void ASTUF_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTUF_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &ASTUF_Character::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUF_Character::MoveRight );
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUF_Character::Jump );

	// мышка
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUF_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUF_Character::AddControllerYawInput);

}

	// вызывается при движении вперед/ назад
	void ASTUF_Character::MoveForward(float Amount)
	{
		AddMovementInput(GetActorForwardVector(), Amount);
	}


	// вызывается при движении влево/вправо
	void ASTUF_Character::MoveRight(float Amount)
	{
		AddMovementInput(GetActorRightVector(), Amount);
	}
