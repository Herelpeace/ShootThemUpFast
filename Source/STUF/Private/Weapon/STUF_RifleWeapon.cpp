// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STU_WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTUF_RifleWeapon::ASTUF_RifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTU_WeaponFXComponent>("WeaponFXComponent");

}

void ASTUF_RifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASTUF_RifleWeapon::StartFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	InitMuzzleFX();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this,&ASTUF_RifleWeapon::MakeShot, TimerBetweenShots, true);

	MakeShot();
}

void ASTUF_RifleWeapon::StopFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisibility(false);

}

void ASTUF_RifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart,TraceEnd;

	// �������� ����� ����� �������� ����� �������� ����������� �����
	// ����� �� ������ ���������� �������
	if(!GetTraceData(TraceStart,TraceEnd)) 
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	// ������ ����������� ����� ��������, ���� ���������� ���� �� ���������� ��������� HitResult
	MakeHit(HitResult,TraceStart,TraceEnd);

	// ��� ������� �����������
	FVector TraceFXEnd = TraceEnd; 

	// ���� ������������ ����, ������ ����� �������, ���� �� ��� ��� ����������� ����� ��������
	if (HitResult.bBlockingHit)
	{
		// ���� ���� ��������� �� �������� �������� ����� ��� ������� �����������
		TraceFXEnd = HitResult.ImpactPoint;

		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(),GetMazzleWorldLocation(),HitResult.ImpactPoint,FColor::Red,false,3.0f,0.0,3.0f);
		//DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,20.0f,FColor::Red,false,3.0f);

		//����������� ������ Niagara
		WeaponFXComponent->PlayImpactFx(HitResult);

		//UE_LOGFMT(LogBaseWeapon,Warning, "Bone: {bone_name}",HitResult.BoneName);
	}

	// ������ �����������
	SpawnTraceFX(GetMazzleWorldLocation(),TraceFXEnd); 

	DecreaseAmmo();
}

// �������� ����� ������ � ����� ����� 
bool ASTUF_RifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	// �������� ������� ������ � �� ���������� � ������������
	// GetPlayerViewPoint ��������� ���������� ������� � �� ��������, �������
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) false;


	TraceStart = ViewLocation;	//SocketTransform.GetLocation();
	//const FVector ShootDirection = ViewRotation.Vector(); // ��� x ������, ����� �� ����������� ��������	// SocketTransform.GetRotation().GetForwardVector();
	//���������� �������
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad );
	TraceEnd = TraceStart+ShootDirection*TraceMaxDistance;
	return true;

}

void ASTUF_RifleWeapon::MakeDamage(const FHitResult &HitResult)
{
	const auto DamageActor = HitResult.GetActor();

	if(!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this );

}

	// ������� Niagara �������, ���������� ���������
void ASTUF_RifleWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)		// ���� ������� �� ����������, ������� �
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	SetMuzzleFXVisibility(true);

}

	// ���������� ����� ��������� �������
void ASTUF_RifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);				// ��������������� ������� �� �����
		MuzzleFXComponent->SetVisibility(Visible, true);	// ������ �������
		
	}
}

void ASTUF_RifleWeapon::SpawnTraceFX (const FVector& TraceStart, FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX,TraceStart);
	if (TraceFXComponent )
	{
		// � ���������� �������� ����� ������� ����������� ���������� �������� ����� ��������
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}

}



