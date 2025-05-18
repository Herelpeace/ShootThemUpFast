// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Logging/StructuredLog.h"
#include "Dev/STUF_FireDamageType.h"
#include "Dev/STUF_IceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All);

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

// в BeginPlay мы подписаны на делегат OnTakeAnyDamage, в классе DamageActor функция ApplyRadialDamage 
// вызывает срабатывание делегата и мы попадаем сюда
// ApplyRadialDamage - срабатывает автоматически когда попвдаем в сферу
void USTUF_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -=Damage;

	UE_LOGFMT (LogHealthComponent,Warning,"Damage: {damage}", Damage);

	if (DamageType->IsA<USTUF_FireDamageType>())
	{
		UE_LOGFMT (LogHealthComponent,Warning,"So hoooooooooot!!!");
	}
	else if (DamageType->IsA<USTUF_IceDamageType>())
	{
		UE_LOGFMT (LogHealthComponent,Warning,"So coooooooold!!!");
	}

}

