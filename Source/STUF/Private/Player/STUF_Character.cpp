// BGAT studio. All Rights Reserved. 


#include "Player/STUF_Character.h"

#include "Components/STUF_CharacterMovementComponent.h"
#include "Components/STUF_HealthComponent.h"
#include "Components/STUF_WeaponComponent.h"
#include "Logging/StructuredLog.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter,All,All);


// Sets default values
ASTUF_Character::ASTUF_Character( const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<USTUF_CharacterMovementComponent> (ACharacter::CharacterMovementComponentName) )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTUF_HealthComponent>("MY_HealthComponent");

	WeaponComponent = CreateDefaultSubobject<USTUF_WeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASTUF_Character::BeginPlay()
{
	Super::BeginPlay();	
	check(HealthComponent);
	check(GetCharacterMovement());
	check(WeaponComponent);
	check(GetMesh());

	OnHealthChange(HealthComponent->GetHealth(), 0.0f);

	HealthComponent->OnDeath.AddUObject(this, &ASTUF_Character::OnDeath);
	HealthComponent->OnHealtChange.AddUObject(this,&ASTUF_Character::OnHealthChange);

	LandedDelegate.AddDynamic(this, &ASTUF_Character::OnGroundLanded);

}


void ASTUF_Character::OnHealthChange(float Health, float HealthDelta)
{

}

void ASTUF_Character::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;	// скорость по оси Z

	UE_LOGFMT(LogBaseCharacter, Warning, "On lended: {velocityZ} ",FallVelocityZ );

	if(FallVelocityZ<LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage,FallVelocityZ);

	TakeDamage(FinalDamage,FDamageEvent(),nullptr,nullptr);

	UE_LOGFMT(LogBaseCharacter, Warning, "Final damage: {damage} ",FinalDamage );
}

// Called every frame
void ASTUF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool ASTUF_Character::IsRunning() const
{
	return false;
}

float  ASTUF_Character::GetMovementDirection() const
{
	if(GetVelocity().IsZero()) return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto  AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees* FMath::Sign(CrossProduct.Z);
}

void ASTUF_Character::OnDeath()
{
	// UE_LOGFMT(LogBaseCharacter, Warning,"Plyer is dead! {name}", *GetName());

	// PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifaSpanOnDeath);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTUF_Character::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if(!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName,Color);

}

