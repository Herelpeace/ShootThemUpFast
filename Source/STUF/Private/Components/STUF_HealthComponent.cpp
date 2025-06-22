// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Logging/StructuredLog.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent,All,All);

USTUF_HealthComponent::USTUF_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUF_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(MaxHealth>0, TEXT("MaxHealth not be 0"));

	SetHealth(MaxHealth);

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
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	SetHealth(Health-Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USTUF_HealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	//UE_LOGFMT (LogHealthComponent,Warning,"Damage: {damage}", Damage);
}

void USTUF_HealthComponent::HealUpdate()
{

	SetHealth(Health+HealModifier);

	if (FMath::IsNearlyEqual(Health,MaxHealth,0.5f) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}

}

void USTUF_HealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	OnHealtChange.Broadcast(Health);
}

