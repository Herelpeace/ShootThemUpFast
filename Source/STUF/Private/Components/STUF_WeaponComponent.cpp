// BGAT studio. All Rights Reserved. 


#include "Components/STUF_WeaponComponent.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUF_EquipFinishedAnimNotify.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent,All,All);

USTUF_WeaponComponent::USTUF_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void USTUF_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	InitAnimations();

	SpawnWeapons();

	EquipWeapon(CurrentWeaponIndex);

}

void USTUF_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;

	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);

}

// спавним модель оружия
void USTUF_WeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character||!GetWorld()) return;

	for (auto WeaponClass:WeaponClasses )
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUF_BaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon,Character->GetMesh(), WeaponArmorySocketName);
	}

}


void USTUF_WeaponComponent::AttachWeaponToSocket(ASTUF_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon||!SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

	 Weapon->AttachToComponent(SceneComponent,AttachmentRules,SocketName);

	// указываем кто владеет этим заспавненным актором (классом ASTUF_BaseWeapon)
	// нужно чтобы получить доступ к камере из класса ASTUF_BaseWeapon, при стрельбе
	// компоненты автоматически получают владельца, а акторам его нужно указывать вручную
	//CurrentWeapon->SetOwner(Character);

}

void USTUF_WeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();

		// присоединяем к спине персонажа
		AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	
	// присоединяем оружие к руке
	AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(),WeaponEquipSocketName);

	// анимация смены оружия
	PlayAnimMontage(EquipAnimMontage);
}


void USTUF_WeaponComponent::StartFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StartFire();
}

void USTUF_WeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StopFire();

}

void USTUF_WeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex+1)%Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUF_WeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	Character->PlayAnimMontage(Animation);

}

void USTUF_WeaponComponent::InitAnimations()
{
	if(!EquipAnimMontage) return;

	const auto NotifyEvents = EquipAnimMontage->Notifies;

	for (auto NotifyEvent:NotifyEvents)
	{
		auto EquipFinishedNotify = Cast<USTUF_EquipFinishedAnimNotify>(NotifyEvent.Notify);

		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &USTUF_WeaponComponent::OnEquipFinished);
			break;
		}

	}
}


void USTUF_WeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if (Character->GetMesh() == MeshComponent)
	{
		UE_LOGFMT(LogWeaponComponent,Warning,"EquipFinished ");
	}

}