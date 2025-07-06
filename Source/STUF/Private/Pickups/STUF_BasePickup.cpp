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

	check(CollisionComponent);
	
}

void ASTUF_BasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// после того как пересекли пикап
void ASTUF_BasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);

	if (GivePickupTo(Pawn))		// у каждого пикапа вызываем свою функцию
	{
		// делаем невидимым
		PickupWasTaken();
	}

	
}

bool ASTUF_BasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

// делает пикап невидимым
void ASTUF_BasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle,this,&ASTUF_BasePickup::Respawn,RespawnTime);


}

void ASTUF_BasePickup::Respawn()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}

}