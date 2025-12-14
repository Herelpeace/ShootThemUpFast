// BGAT studio. All Rights Reserved. 


#include "Player/STUF_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUF_WeaponComponent.h"

// Sets default values
ASTUF_PlayerCharacter::ASTUF_PlayerCharacter( const FObjectInitializer& ObjInit)
	:Super(ObjInit )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation=true;
	SpringArmComponent->SocketOffset = FVector(0.0f,100.0f,0.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called to bind functionality to input
void ASTUF_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &ASTUF_PlayerCharacter::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUF_PlayerCharacter::MoveRight );
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUF_PlayerCharacter::Jump );
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUF_PlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUF_PlayerCharacter::OnStopRunning);

	// мышка
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUF_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUF_PlayerCharacter::AddControllerYawInput);

	//стрельба
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUF_WeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUF_WeaponComponent::StopFire);

	// смена оружия
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUF_WeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUF_WeaponComponent::Reload);

}

// вызывается при движении вперед/ назад
void ASTUF_PlayerCharacter::MoveForward(float Amount)
{
	if(Amount==0.0f) return;
		
	IsMovingForward = Amount>0.0f;	//нажата клавиша вперед
	AddMovementInput(GetActorForwardVector(), Amount);
}

// вызывается при движении влево/вправо
void ASTUF_PlayerCharacter::MoveRight(float Amount)
{
	if(Amount==0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUF_PlayerCharacter::OnStartRunning()
{
	WantsToRun  = true;	// нажата клавиша Shift
}

void ASTUF_PlayerCharacter::OnStopRunning()
{
	WantsToRun  = false;
}

bool ASTUF_PlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASTUF_PlayerCharacter::OnDeath()
{

if (Controller)
{
	Super::OnDeath();
	Controller->ChangeState(NAME_Spectating);
}

}