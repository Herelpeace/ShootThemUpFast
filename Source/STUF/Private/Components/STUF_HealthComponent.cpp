// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Logging/StructuredLog.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STUF_GameModeBase.h"

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
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&USTUF_HealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	// тряска камеры
	PlayCameraShake();

	//UE_LOGFMT (LogHealthComponent,Warning,"Damage: {damage}", Damage);
}

void USTUF_HealthComponent::HealUpdate()
{

	SetHealth(Health+HealModifier);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}

}

void USTUF_HealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;

	OnHealtChange.Broadcast(Health, HealthDelta);
}

bool USTUF_HealthComponent::TryToAddHealth(float HealthAmount)
{
	if(IsDead()||IsHealthFull()) return false;

	SetHealth(Health + HealthAmount);
	return true;
}

bool USTUF_HealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health,MaxHealth,0.5f);
}

void USTUF_HealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager ) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);

}

void USTUF_HealthComponent::Killed(AController* KillerController)
{
	if(!GetWorld()) return;
	const auto GameMode = Cast<ASTUF_GameModeBase>(GetWorld()->GetAuthGameMode());
	if(!GameMode) return;

	const auto Player = Cast<APawn> (GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}