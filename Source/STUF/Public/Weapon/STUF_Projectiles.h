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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeSeconds = 5.0f;

private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	AController* GetController() const;

};
