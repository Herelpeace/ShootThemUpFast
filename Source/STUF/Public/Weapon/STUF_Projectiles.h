// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUF_Projectiles.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class STUF_API ASTUF_Projectiles : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUF_Projectiles();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; };

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent * CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

private:
	FVector ShotDirection;
};
