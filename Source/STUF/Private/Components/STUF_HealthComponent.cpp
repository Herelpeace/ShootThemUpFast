// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"

USTUF_HealthComponent::USTUF_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUF_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}


