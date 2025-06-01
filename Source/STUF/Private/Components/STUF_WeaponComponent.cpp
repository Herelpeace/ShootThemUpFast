// BGAT studio. All Rights Reserved. 


#include "Components/STUF_WeaponComponent.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "GameFramework/Character.h"

USTUF_WeaponComponent::USTUF_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void USTUF_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();

}

// спавним модель оружия
void USTUF_WeaponComponent::SpawnWeapon()
{
	if(!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUF_BaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

	CurrentWeapon->AttachToComponent(Character->GetMesh(),AttachmentRules,WeaponAttachPointName);

	// указываем кто владеет этим заспавненным актором (классом ASTUF_BaseWeapon)
	// нужно чтобы получить доступ к камере из класса ASTUF_BaseWeapon, при стрельбе
	// компоненты автоматически получают владельца, а акторам его нужно указывать вручную
	CurrentWeapon->SetOwner(Character);
	

}

void USTUF_WeaponComponent::Fire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->Fire();

}

