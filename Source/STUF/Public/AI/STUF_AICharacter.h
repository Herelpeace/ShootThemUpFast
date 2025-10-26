// BGAT studio. All Rights Reserved. 

// ��������� BehaviorTree � �������������� C++
// ������� ������� ��������� ��� ��������� ������� ��������

#pragma once

#include "CoreMinimal.h"
#include "Player/STUF_Character.h"
#include "STUF_AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class STUF_API ASTUF_AICharacter : public ASTUF_Character
{
	GENERATED_BODY()
	
	public:
		ASTUF_AICharacter(const FObjectInitializer & ObjInit );

		// ���������� ��� ������ BehaviorTree
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MYAI")
		UBehaviorTree* BehaviorTreeAsset;



};
