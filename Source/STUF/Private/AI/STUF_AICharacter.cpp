// BGAT studio. All Rights Reserved. 


#include "AI/STUF_AICharacter.h"
#include "AI/STUF_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUF_AIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/STUF_HealthBarWidget.h"
#include "Components/STUF_HealthComponent.h"


ASTUF_AICharacter::ASTUF_AICharacter(const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<USTUF_AIWeaponComponent>("WeaponComponent"))
{

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUF_AICharacter::StaticClass();

	bUseControllerRotationYaw = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate=FRotator(0.0f, 200.0f, 0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);

}

void ASTUF_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthWidgetComponent);
}


void ASTUF_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHealthWidgetVisibility();
}

void ASTUF_AICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STUController = Cast<AAIController>(Controller);

	if (STUController && STUController->BrainComponent)
	{
		// останавливаем выполнение дерева поведения у данного AICharactera
		STUController->BrainComponent->Cleanup();
	}

}

void ASTUF_AICharacter::OnHealthChange(float Health, float HealthDelta)
{
	Super::OnHealthChange(Health,HealthDelta);

	const auto HealthBarWidget = Cast<USTUF_HealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());

	if(!HealthBarWidget) return;

	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());

}


void ASTUF_AICharacter::UpdateHealthWidgetVisibility()
{
	if(!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator() ) return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());

	HealthWidgetComponent->SetVisibility(Distance<HealthVisibilityDistance,true);
}