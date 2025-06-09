// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ASTUF_RifleWeapon::StartFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	MakeShot();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this,&ASTUF_RifleWeapon::MakeShot, TimerBetweenShots, true);
}

void ASTUF_RifleWeapon::StopFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

}

void ASTUF_RifleWeapon::MakeShot()
{
	if(!GetWorld()) return; 

	FVector TraceStart,TraceEnd;

	// �������� ����� ����� �������� ����� �������� ����������� �����
	// ����� �� ������ ���������� �������
	if(!GetTraceData(TraceStart,TraceEnd)) return;

	FHitResult HitResult;
	// ������ ����������� ����� ��������, ���� ���������� ���� �� ���������� ��������� HitResult
	MakeHit(HitResult,TraceStart,TraceEnd);

	// ���� ������������ ����, ������ ����� �������, ���� �� ��� ��� ����������� ����� ��������
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