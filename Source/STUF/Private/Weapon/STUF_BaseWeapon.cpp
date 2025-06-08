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
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	MakeShot();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this,&ASTUF_BaseWeapon::MakeShot, TimerBetweenShots, true);
}

void ASTUF_BaseWeapon::StopFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

}

void ASTUF_BaseWeapon::MakeShot()
{
	if(!GetWorld()) return; 

	FVector TraceStart,TraceEnd;

	// получаем точки между которыми будем рисовать виртуальную линию
	// сдесь же делаем конический разброс
	if(!GetTraceData(TraceStart,TraceEnd)) return;

	FHitResult HitResult;
	// делаем виртуальную линию выстрела, если пересечние есть то заполнится структура HitResult
	MakeHit(HitResult,TraceStart,TraceEnd);

	// если пересечеение есть, рисуем линии отладки, идут не так как виртуальная линия выстрела
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(),GetMazzleWorldLocation(),HitResult.ImpactPoint,FColor::Red,false,3.0f,0.0,3.0f);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,20.0f,FColor::Red,false,3.0f);

		//UE_LOGFMT(LogBaseWeapon,Warning, "Bone: {bone_name}",HitResult.BoneName);
	}
	else
	{
		DrawDebugLine(GetWorld(),GetMazzleWorldLocation(),TraceEnd,FColor::Red,false,3.0f,0.0,3.0f);
	}


}

// получаем контроллер
APlayerController* ASTUF_BaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

// получаем положение камеры в пространстве
bool ASTUF_BaseWeapon::GetPlayerViewPoint( FVector& ViewLocation,FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) nullptr;

	// получаем позицию камеры и ее ориентацию в пространстве
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);
	return true;
}

// получаем положение сокета из которого делаем выстрел
FVector ASTUF_BaseWeapon::GetMazzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// получаем точки начала и конца линии 
bool ASTUF_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	// получаем позицию камеры и ее ориентацию в пространстве
	// GetPlayerViewPoint заполняет переменные которые в неё передают, данными
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) false;


	TraceStart = ViewLocation;	//SocketTransform.GetLocation();
	//const FVector ShootDirection = ViewRotation.Vector(); // ось x камеры, берем за направление выстрела	// SocketTransform.GetRotation().GetForwardVector();
	//конический разброс
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad );
	TraceEnd = TraceStart+ShootDirection*TraceMaxDistance;
	return true;

}

// виртуальная линия выстрела
void ASTUF_BaseWeapon::MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;

	// параметр взаимодействия с пересеченными объектами
	// передаем какие акторы игнорировать 
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	// проверям пересекает ли линия выстрела какие либо объекты
	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility,CollisionParams);

}

void ASTUF_BaseWeapon::MakeDamage(const FHitResult &HitResult)
{
	const auto DamageActor = HitResult.GetActor();

	if(!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this );

}