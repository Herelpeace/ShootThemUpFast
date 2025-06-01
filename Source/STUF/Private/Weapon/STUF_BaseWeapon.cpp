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

void ASTUF_BaseWeapon::Fire()
{
	UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	MakeShot();
}

void ASTUF_BaseWeapon::MakeShot()
{
	if(!GetWorld()) return; 

	const auto Player = Cast<ACharacter>(GetOwner());

	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller) return;

	// получаем позицию камеры и ее ориентацию в пространстве
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);

	// трансформация сокета
	const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	const FVector TraceStart = ViewLocation;	//SocketTransform.GetLocation();
	const FVector ShootDirection = ViewRotation.Vector(); // ось x камеры, берем за направление выстрела	// SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart+ShootDirection*TraceMaxDistance;

	// параметр взаимодействия с пересеченными объектами
	// передаем какие акторы игнорировать 
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	// проверям пересекает ли линия выстрела какие либо объекты
	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility,CollisionParams);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(),SocketTransform.GetLocation(),HitResult.ImpactPoint,FColor::Red,false,3.0f,0.0,3.0f);

		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,20.0f,FColor::Red,false,3.0f);

		UE_LOGFMT(LogBaseWeapon,Warning, "Bone: {bone_name}",HitResult.BoneName);
	}
	else
	{
		DrawDebugLine(GetWorld(),SocketTransform.GetLocation(),TraceEnd,FColor::Red,false,3.0f,0.0,3.0f);
	}


}