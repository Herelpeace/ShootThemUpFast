// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_RifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STU_WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ASTUF_RifleWeapon::ASTUF_RifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTU_WeaponFXComponent>("WeaponFXComponent");

}

void ASTUF_RifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASTUF_RifleWeapon::StartFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	InitMuzzleFX();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this,&ASTUF_RifleWeapon::MakeShot, TimerBetweenShots, true);

	MakeShot();
}

void ASTUF_RifleWeapon::StopFire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetMuzzleFXVisibility(false);

}

void ASTUF_RifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart,TraceEnd;

	// получаем точки между которыми будем рисовать виртуальную линию
	// сдесь же делаем конический разброс
	if(!GetTraceData(TraceStart,TraceEnd)) 
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	// делаем виртуальную линию выстрела, если пересечние есть то заполнится структура HitResult
	MakeHit(HitResult,TraceStart,TraceEnd);

	// для эффекта трассировки
	FVector TraceFXEnd = TraceEnd; 

	// если пересечеение есть, рисуем линии отладки, идут не так как виртуальная линия выстрела
	if (HitResult.bBlockingHit)
	{
		// если есть попадание то изменяем конечную точку для эффекта трассировки
		TraceFXEnd = HitResult.ImpactPoint;

		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(),GetMazzleWorldLocation(),HitResult.ImpactPoint,FColor::Red,false,3.0f,0.0,3.0f);
		//DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,20.0f,FColor::Red,false,3.0f);

		//проигрываем эффект Niagara
		WeaponFXComponent->PlayImpactFx(HitResult);

		//UE_LOGFMT(LogBaseWeapon,Warning, "Bone: {bone_name}",HitResult.BoneName);
	}

	// рисуем трассировку
	SpawnTraceFX(GetMazzleWorldLocation(),TraceFXEnd); 

	DecreaseAmmo();
}

// получаем точки начала и конца линии 
bool ASTUF_RifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	// получаем позицию камеры и ее ориентацию в пространстве
	// GetPlayerViewPoint заполняет переменные которые в неё передают, данными
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) false;


	TraceStart = ViewLocation;	//SocketTransform.GetLocation();
	//const FVector ShootDirection = ViewRotation.Vector(); // ось x камеры, берем за направление выстрела	// SocketTransform.GetRotation().GetForwardVector();
	//конический разброс
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad );
	TraceEnd = TraceStart+ShootDirection*TraceMaxDistance;
	return true;

}

void ASTUF_RifleWeapon::MakeDamage(const FHitResult &HitResult)
{
	const auto DamageActor = HitResult.GetActor();

	if(!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this );

}

	// спавнит Niagara систему, выставляет видимость
void ASTUF_RifleWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)		// если система не заспавнена, спавним её
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	SetMuzzleFXVisibility(true);

}

	// выставляет фллаг видимости эффекта
void ASTUF_RifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!Visible);				// воспроизведение эффекта на паузу
		MuzzleFXComponent->SetVisibility(Visible, true);	// рендер эффекта
		
	}
}

void ASTUF_RifleWeapon::SpawnTraceFX (const FVector& TraceStart, FVector& TraceEnd)
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX,TraceStart);
	if (TraceFXComponent )
	{
		// в переменную конечной точки эффекта трассировки записываем конечную точку выстрела
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}

}



