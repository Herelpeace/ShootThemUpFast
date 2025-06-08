// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_Projectiles.h"
#include "Components/SphereComponent.h"

ASTUF_Projectiles::ASTUF_Projectiles()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	SetRootComponent(CollisionComponent);

}

void ASTUF_Projectiles::BeginPlay()
{
	Super::BeginPlay();
	
}

