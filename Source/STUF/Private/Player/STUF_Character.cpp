// BGAT studio. All Rights Reserved. 


#include "Player/STUF_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUF_CharacterMovementComponent.h"
#include "Components/STUF_HealthComponent.h"
#include "Components/TextRenderComponent.h"
//#include "Logging/StructuredLog.h"




// Sets default values
ASTUF_Character::ASTUF_Character( const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<USTUF_CharacterMovementComponent> (ACharacter::CharacterMovementComponentName) )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation=true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUF_HealthComponent>("MY_HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASTUF_Character::BeginPlay()
{
	Super::BeginPlay();	

	check(HealthComponent);
	check(HealthTextComponent);
}

// Called every frame
void ASTUF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Health = HealthComponent->GetHealth();
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f "),Health)));

	TakeDamage(0.1f,FDamageEvent(),Controller,this);
}




// Called to bind functionality to input
void ASTUF_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &ASTUF_Character::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUF_Character::MoveRight );
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUF_Character::Jump );
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUF_Character::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUF_Character::OnStopRunning);

	// мышка
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUF_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUF_Character::AddControllerYawInput);

}

	// вызывается при движении вперед/ назад
	void ASTUF_Character::MoveForward(float Amount)
	{
		if(Amount==0.0f) return;
		
		IsMovingForward = Amount>0.0f;	//нажата клавиша вперед
		AddMovementInput(GetActorForwardVector(), Amount);
	}


	// вызывается при движении влево/вправо
	void ASTUF_Character::MoveRight(float Amount)
	{
		if(Amount==0.0f) return;
		AddMovementInput(GetActorRightVector(), Amount);
	}

	void ASTUF_Character::OnStartRunning()
	{
		WantsToRun  = true;	// нажата клавиша Shift
	}

	void ASTUF_Character::OnStopRunning()
	{
		WantsToRun  = false;
	}

	bool ASTUF_Character::IsRunning() const
	{
		return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
	}

	float  ASTUF_Character::GetMovementDirection() const
	{
		if(GetVelocity().IsZero()) return 0.0f;

		const auto VelocityNormal = GetVelocity().GetSafeNormal();
		const auto  AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
		const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
		const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
		return CrossProduct.IsZero() ? Degrees : Degrees* FMath::Sign(CrossProduct.Z);
	}

