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

	GenerateRotationYaw();	
}

void ASTUF_BasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f,RotationYaw, 0.0f));

}

// ����� ���� ��� ��������� �����
void ASTUF_BasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);

	if (GivePickupTo(Pawn))		// � ������� ������ �������� ���� �������
	{
		// ������ ���������
		PickupWasTaken();
	}

	
}

bool ASTUF_BasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

// ������ ����� ���������
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
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}

}

void ASTUF_BasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f,2.0f)*Direction;
}