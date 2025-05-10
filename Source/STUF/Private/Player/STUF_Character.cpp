// BGAT studio. All Rights Reserved. 


#include "Player/STUF_Character.h"
#include "Camera/CameraComponent.h"


// Sets default values
ASTUF_Character::ASTUF_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	CameraComponent->SetupAttachment(GetRootComponent());

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

}

