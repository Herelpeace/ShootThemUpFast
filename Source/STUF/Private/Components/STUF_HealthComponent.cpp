// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All);

USTUF_HealthComponent::USTUF_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUF_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;	

	OnHealtChange.Broadcast(Health);

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
	if (Damage <= 0.0f || IsDead()) return;

	Health = FMath::Clamp(Health-Damage, 0.0f,MaxHealth);

	OnHealtChange.Broadcast(Health);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	//UE_LOGFMT (LogHealthComponent,Warning,"Damage: {damage}", Damage);



}

