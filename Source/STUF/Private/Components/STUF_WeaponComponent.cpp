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

// ������� ������ ������
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

	// ��������� ��� ������� ���� ������������ ������� (������� ASTUF_BaseWeapon)
	// ����� ����� �������� ������ � ������ �� ������ ASTUF_BaseWeapon, ��� ��������
	// ���������� ������������� �������� ���������, � ������� ��� ����� ��������� �������
	//CurrentWeapon->SetOwner(Character);

}

void USTUF_WeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();

		// ������������ � ����� ���������
		AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	
	// ������������ ������ � ����
	AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(),WeaponEquipSocketName);

	EquipAnimInProgress = true;

	// �������� ����� ������
	PlayAnimMontage(EquipAnimMontage);

		
}


void USTUF_WeaponComponent::StartFire()
{
	if(!CanFire()) return;

	CurrentWeapon->StartFire();
}

void USTUF_WeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StopFire();

}

void USTUF_WeaponComponent::NextWeapon()
{ 
	if (!CanEquip()) return;

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
	if(!Character || MeshComponent!=Character->GetMesh() ) return;

		EquipAnimInProgress = false;

}

bool USTUF_WeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress;

}


bool USTUF_WeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress;

}