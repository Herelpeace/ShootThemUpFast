// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Logging/StructuredLog.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All);

ASTUF_BaseWeapon::ASTUF_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void ASTUF_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ASTUF_BaseWeapon::StartFire()
{

}

void ASTUF_BaseWeapon::StopFire()
{

}

void ASTUF_BaseWeapon::MakeShot()
{

}

// �������� ����������
APlayerController* ASTUF_BaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

// �������� ��������� ������ � ������������
bool ASTUF_BaseWeapon::GetPlayerViewPoint( FVector& ViewLocation,FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) nullptr;

	// �������� ������� ������ � �� ���������� � ������������
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);
	return true;
}

// �������� ��������� ������ �� �������� ������ �������
FVector ASTUF_BaseWeapon::GetMazzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// �������� ����� ������ � ����� ����� 
bool ASTUF_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	// �������� ������� ������ � �� ���������� � ������������
	// GetPlayerViewPoint ��������� ���������� ������� � �� ��������, �������
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) false;


	TraceStart = ViewLocation;	//SocketTransform.GetLocation();
	const FVector ShootDirection = ViewRotation.Vector(); // ��� x ������, ����� �� ����������� ��������	// SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart+ShootDirection*TraceMaxDistance;
	return true;

}

// ����������� ����� ��������
void ASTUF_BaseWeapon::MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;

	// �������� �������������� � ������������� ���������
	// �������� ����� ������ ������������ 
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	// �������� ���������� �� ����� �������� ����� ���� �������
	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility,CollisionParams);

}

void ASTUF_BaseWeapon::MakeDamage(const FHitResult &HitResult)
{
	const auto DamageActor = HitResult.GetActor();

	if(!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this );

}