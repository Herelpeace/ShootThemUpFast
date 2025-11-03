// BGAT studio. All Rights Reserved. 


#include "AI/STUF_AICharacter.h"
#include "AI/STUF_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUF_AIWeaponComponent.h"


ASTUF_AICharacter::ASTUF_AICharacter(const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<USTUF_AIWeaponComponent>("WeaponComponent"))
{

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUF_AICharacter::StaticClass();

	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate=FRotator(0.0f, 200.0f, 0.0f);
	}
}
