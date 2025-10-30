// BGAT studio. All Rights Reserved. 

/*
	 GetClosestEnemy() �������� ������ ������� ������� ��������� � ���� ��������� ���������
	 ��������� ��� ��� ����, � ���� AI ������ ������� ����� ����� � ������ ������������� �������� BestDistance � BestPawn
	 BestPawn ������������ ��� ��������� ������ �������
*/

#include "Components/STUF_AIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUF_HealthComponent.h"
#include "Perception/AISense_Sight.h"


AActor* USTUF_AIPerceptionComponent::GetClosestEnemy() const
{
	// ������� ������ ��� �������� �������
	TArray<AActor*> PerciveActors;

	// ������� ������� ��������� ���� ������� ������� ������ ������������ ���������
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PerciveActors );
	if(PerciveActors.Num()==0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	// ��������� ����������
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	// ����������� �� �������
	for (const auto PerciveActor:PerciveActors)
	{
		const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(PerciveActor);

		if (HealthComponent && !HealthComponent->IsDead()) // � ������� �������� �������� �� �����
		{
			// �������� ���������� �� ������������ ������
			// �� ��������� ������������ ������ �������� ���������� ������ �������� ������� AI
			const auto CurrentDistance = (PerciveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();

			if (CurrentDistance < BestDistance) 
			{
				BestDistance=CurrentDistance;
				BestPawn = PerciveActor;
			}
		}
	}

	return BestPawn;

}