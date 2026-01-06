// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_Projectiles.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STU_WeaponFXComponent.h"


ASTUF_Projectiles::ASTUF_Projectiles()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true; // включаем передачу физического материала
	SetRootComponent(CollisionComponent);
	

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	WeaponFXComponent = CreateDefaultSubobject<USTU_WeaponFXComponent>("WeaponFXComponent");

}

void ASTUF_Projectiles::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);
	check(CollisionComponent);
	check(WeaponFXComponent);

	MovementComponent->Velocity=ShotDirection*MovementComponent->InitialSpeed;
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUF_Projectiles::OnProjectileHit);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(),true);
	SetLifeSpan(LifeSeconds);
}

void ASTUF_Projectiles::OnProjectileHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if(!GetWorld()) return;

	MovementComponent->StopMovementImmediately();
	// make damage


	//DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 50, SphereColor);
	UGameplayStatics::ApplyRadialDamage (
		GetWorld(), //
		DamageAmount,//
		GetActorLocation(),//
		DamageRadius,//
		UDamageType::StaticClass(), //
		{GetOwner()}, //
		this, //
		GetController(), //
		DoFullDamage//
	                                   );

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 50, FColor::Red, false, 5.0f);

	WeaponFXComponent->PlayImpactFx(Hit);

	Destroy();
}


AController* ASTUF_Projectiles::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn? Pawn->GetController():nullptr;

}