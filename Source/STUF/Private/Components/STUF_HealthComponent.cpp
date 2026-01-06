// BGAT studio. All Rights Reserved. 


#include "Components/STUF_HealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Logging/StructuredLog.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STUF_GameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"

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
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &USTUF_HealthComponent::OnTakePointDamage); 
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USTUF_HealthComponent::OnTakeRadialDamage); 
	}
}

void USTUF_HealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	ApplyDamage(FinalDamage, InstigatedBy);
}


void USTUF_HealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}

// в BeginPlay мы подписаны на делегат OnTakeAnyDamage, в классе DamageActor функция ApplyRadialDamage 
// вызывает срабатывание делегата и мы попадаем сюда
// ApplyRadialDamage - срабатывает автоматически когда попвдаем в сферу
void USTUF_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

}

void USTUF_HealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
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
	ReportDamageEvent(Damage, InstigatedBy);
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

float USTUF_HealthComponent::GetPointDamageModifier(AActor* DamageActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamageActor);

	if(!Character ||  !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName) ) return 1.0f;

	const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();

	if(!DamageModifiers.Contains(PhysMaterial)) return 1.0f;

	return DamageModifiers[PhysMaterial];

}

void USTUF_HealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if(!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()  ) return;

	UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(), Damage, InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation() );
}