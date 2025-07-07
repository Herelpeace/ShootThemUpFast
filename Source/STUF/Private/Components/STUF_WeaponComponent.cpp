// BGAT studio. All Rights Reserved. 


#include "Components/STUF_WeaponComponent.h"
#include "Weapon/STUF_BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUF_EquipFinishedAnimNotify.h"
#include "Animations/STUF_ReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent,All,All);

constexpr static int32 WeaponNum = 2;

USTUF_WeaponComponent::USTUF_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUF_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponNum, TEXT("Our character Weapon not set"));

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

	for (auto OneWeaponData:WeaponData )
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUF_BaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this,&USTUF_WeaponComponent::OnEmptyClip);
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
	if (WeaponIndex < 0 || WeaponIndex >= WeaponData.Num())
	{
		// ���� ��������� � ������� �� ���������, ������� �� �������
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();

		// ������������ � ����� ���������
		AttachWeaponToSocket(CurrentWeapon,Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	// CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	
	// ��������� �� ������� �� ����������� ������, �������� WeaponData
	// ���� ��� ��������� ������� ����� �������������� ������ ������
	// ����� CurrentWeapon �������� ��������� � ������� ������� ������������� �������� ������
	// ����� ���������� � ���� ��������� � �������� ������ ���� ��������
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)	//
		{return Data.WeaponClass == CurrentWeapon->GetClass();} );							//

	// ������������� ��������, �� �������� �� ��������� ���������
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage: nullptr;

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
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUF_EquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUF_WeaponComponent::OnEquipFinished);
	}
	else
	{
		UE_LOGFMT(LogWeaponComponent, Warning,"USTUF_EquipFinishedAnimNotify not found in EquipAnimMontage!");
		checkNoEntry();
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUF_ReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify)
		{
			UE_LOGFMT(LogWeaponComponent, Warning,"USTUF_ReloadFinishedAnimNotify not found in ReloadAnimMontage!");
			checkNoEntry();
		}

		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUF_WeaponComponent::OnReloadFinished);
	}
}

// ������ ������� ���� ����� ����� ������ 
void USTUF_WeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || MeshComponent!=Character->GetMesh() ) return;

		EquipAnimInProgress = false;
}

// ������ ������� ���� ����� ����������� ������
void USTUF_WeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || MeshComponent!=Character->GetMesh() ) return;

		ReloadAnimInProgress = false;
}

bool USTUF_WeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}


bool USTUF_WeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress  && !ReloadAnimInProgress;
}

bool USTUF_WeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void USTUF_WeaponComponent::Reload()
{
	ChangeClip();
}

void USTUF_WeaponComponent::OnEmptyClip(ASTUF_BaseWeapon* AmmoEmptyWeapon)
{
	if(!AmmoEmptyWeapon) return;

	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}

	
}

void USTUF_WeaponComponent::ChangeClip()
{
	if (!CanReload()) return;

	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();

	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUF_WeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}

	return false;
}

bool USTUF_WeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}

	return false;
}

bool USTUF_WeaponComponent::TryToAddAmmo(TSubclassOf<ASTUF_BaseWeapon> WeaponType, int32 ClipsAmount)
{
	for (const auto Weapon:Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipsAmount);
		}
	}
	return false;

}