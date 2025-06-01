// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUF_BaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class STUF_API ASTUF_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUF_BaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "MyComponents")
	USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;

	

};
