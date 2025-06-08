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
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMazzleWorldLocation());

	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(),ProjectileClass,SpawnTransform);

	// set projectiles params

	UGameplayStatics::FinishSpawningActor(Projectile,SpawnTransform);

}