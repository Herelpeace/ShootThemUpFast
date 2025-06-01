// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Logging/StructuredLog.h"

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
}


void ASTUF_BaseWeapon::Fire()
{
	UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");
}