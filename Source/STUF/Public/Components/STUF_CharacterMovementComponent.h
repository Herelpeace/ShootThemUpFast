// BGAT studio. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUF_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class STUF_API USTUF_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyMovement", meta=(ClampMin = "1.0",ClampMax="10.0"))
	int32 RunModifier = 1.0f;

	
};
