// BGAT studio. All Rights Reserved. 


#include "Components/STUF_AIWeaponComponent.h"
#include "Weapon/STUF_BaseWeapon.h"


void USTUF_AIWeaponComponent::StartFire()
{
	if(!CanFire()) return;

	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void USTUF_AIWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex+1)%Weapons.Num();

	while (NextIndex != CurrentWeaponIndex)
	{
		// если патроны есть то выходим
		if(!Weapons[NextIndex]->IsAmmoEmpty()) break;

		NextIndex  = (NextIndex+1)%Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}

}