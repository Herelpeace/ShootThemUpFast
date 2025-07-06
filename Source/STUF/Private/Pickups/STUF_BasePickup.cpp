// BGAT studio. All Rights Reserved. 


#include "Pickups/STUF_BasePickup.h"
#include "Components/SphereComponent.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup,All,All);

ASTUF_BasePickup::ASTUF_BasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);

}

void ASTUF_BasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUF_BasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUF_BasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOGFMT(LogBasePickup,Warning, "Pickup wat Taken!");
	Destroy();
}