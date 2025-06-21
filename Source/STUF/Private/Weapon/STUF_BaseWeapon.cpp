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
	checkf(DefaultAmmo.Bullets>0, TEXT("Bullets count not be set 0"));
	checkf(DefaultAmmo.Clips>0, TEXT("Clips count not be set 0"));

	CurrentAmmo = DefaultAmmo;
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
	const FVector ShootDirection = ViewRotation.Vector(); // ось x камеры, берем за направление выстрела	// SocketTransform.GetRotation().GetForwardVector();
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

void ASTUF_BaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOGFMT(LogBaseWeapon, Warning,"No more clips ");
		//UE_LOG(LogBaseWeapon, Warnin,TEXT("No more clips "));
		return;
	}

	CurrentAmmo.Bullets--;
	LogAmmo();

	if (IsClipsEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast();
	}
}

bool ASTUF_BaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 &&  CurrentAmmo.Bullets == 0;
}

bool ASTUF_BaseWeapon::IsClipsEmpty() const
{
	return CurrentAmmo.Bullets == 0;

}

void ASTUF_BaseWeapon::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOGFMT(LogBaseWeapon, Warning,"No more clips ");
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets= DefaultAmmo.Bullets;

	UE_LOGFMT(LogBaseWeapon,Warning," -------------- Change Clip --------------");
}

bool ASTUF_BaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets< DefaultAmmo.Bullets && CurrentAmmo.Clips>0;
}

void ASTUF_BaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: "+ FString::FromInt(CurrentAmmo.Bullets )+ " / ";
	AmmoInfo+= CurrentAmmo.Infinite ? "Infinite": FString::FromInt(CurrentAmmo.Clips);
	UE_LOGFMT(LogBaseWeapon,Warning," {0}",AmmoInfo);
}