// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_LauncherWeapon.h"
#include "Weapon/STUF_Projectiles.h"
#include "Kismet/GameplayStatics.h"

void ASTUF_LauncherWeapon::StartFire()
{
	MakeShot();

}

void ASTUF_LauncherWeapon::MakeShot()
{
	if(!GetWorld() || IsAmmoEmpty()) return; 

	FVector TraceStart,TraceEnd;

	// �������� ����� ����� �������� ����� �������� ����������� �����
	// ����� �� ������ ���������� �������
	if(!GetTraceData(TraceStart,TraceEnd)) return;

	FHitResult HitResult;
	// ������ ����������� ����� ��������, ���� ���������� ���� �� ���������� ��������� HitResult
	MakeHit(HitResult,TraceStart,TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint:TraceEnd;
	const FVector Direction = (EndPoint-GetMazzleWorldLocation()).GetSafeNormal();


	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMazzleWorldLocation());

	ASTUF_Projectiles* Projectile = GetWorld()->SpawnActorDeferred<ASTUF_Projectiles>(ProjectileClass,SpawnTransform);

	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());

		Projectile->FinishSpawning(SpawnTransform);

	}

	DecreaseAmmo();

}