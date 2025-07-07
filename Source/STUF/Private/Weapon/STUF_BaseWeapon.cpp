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

void ASTUF_BaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOGFMT(LogBaseWeapon, Warning,"No more clips ");
		//UE_LOG(LogBaseWeapon, Warnin,TEXT("No more clips "));
		return;
	}

	CurrentAmmo.Bullets--;

	if (IsClipsEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
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

bool ASTUF_BaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASTUF_BaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <=0 ) return false;

	if (IsAmmoEmpty())
	{
		UE_LOGFMT(LogBaseWeapon,Warning," Ammo was empty!");
		CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips+ClipsAmount, 0, DefaultAmmo.Clips+1);
		
		// ������ �����������
		OnClipEmpty.Broadcast(this);
	}
	else 
	if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips+ClipsAmount;

		if (DefaultAmmo.Clips - NextClipsAmount >=0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
			UE_LOGFMT(LogBaseWeapon,Warning," Clips where added!");
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOGFMT(LogBaseWeapon,Warning," Ammo is full now!");
		}

	}
	else
	{
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		UE_LOGFMT(LogBaseWeapon,Warning," Bullets where added");
	}
	return true;

}