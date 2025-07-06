// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUF_BasePickup.generated.h"

class USphereComponent;

UCLASS()
class STUF_API ASTUF_BasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUF_BasePickup();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


public:	
	virtual void Tick(float DeltaTime) override;

};
