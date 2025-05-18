// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"
#include "GameFramework/Actor.h"

USTUF_HealthComponent::USTUF_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUF_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;	

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUF_HealthComponent::OnTakeAnyDamage); 
	}

	
}

void USTUF_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -=Damage;

}

