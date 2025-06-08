// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUF_Projectiles.generated.h"

class USphereComponent;

UCLASS()
class STUF_API ASTUF_Projectiles : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUF_Projectiles();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent * CollisionComponent;

};
