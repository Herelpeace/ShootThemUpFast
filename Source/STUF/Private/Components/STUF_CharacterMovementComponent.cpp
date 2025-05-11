// BGAT studio. All Rights Reserved. 


#include "Components/STUF_CharacterMovementComponent.h"
#include "Player/STUF_Character.h"

float USTUF_CharacterMovementComponent::GetMaxSpeed() const
{
	const int32 MaxSpeed = Super::GetMaxSpeed();

	const ASTUF_Character* Player = Cast<ASTUF_Character>(GetPawnOwner());

	return Player && Player->IsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}