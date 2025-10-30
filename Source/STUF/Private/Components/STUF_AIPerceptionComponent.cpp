// BGAT studio. All Rights Reserved. 

/*
	 GetClosestEnemy() получает массив акторов которые находятся в поле видимости персонажа
	 проверяет что они живы, и тому AI актору который ближе всего к игроку присваиваются значения BestDistance и BestPawn
	 BestPawn возвращается как результат работы функции
*/

#include "Components/STUF_AIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUF_HealthComponent.h"
#include "Perception/AISense_Sight.h"


AActor* USTUF_AIPerceptionComponent::GetClosestEnemy() const
{
	// создаем массив для хранения акторов
	TArray<AActor*> PerciveActors;

	// функция которая получаает всех акторов включая игрока определенных чувствами
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),PerciveActors );
	if(PerciveActors.Num()==0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	// локальные переменные
	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	// пробегаемся по массиву
	for (const auto PerciveActor:PerciveActors)
	{
		const auto HealthComponent = STUUtils::GetSTUFPlayerComponent<USTUF_HealthComponent>(PerciveActor);

		if (HealthComponent && !HealthComponent->IsDead()) // в будущем добавить проверку на врага
		{
			// получаем расстояние до наблюдаемого актора
			// от координат наблюдаемого актора отнимаем координаты актора которыми влажеет AI
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