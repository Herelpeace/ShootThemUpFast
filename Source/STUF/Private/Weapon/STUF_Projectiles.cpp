// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_Projectiles.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASTUF_Projectiles::ASTUF_Projectiles()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

}

void ASTUF_Projectiles::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);

	MovementComponent->Velocity=ShotDirection*MovementComponent->InitialSpeed;
	SetLifeSpan(5.0f);
}

