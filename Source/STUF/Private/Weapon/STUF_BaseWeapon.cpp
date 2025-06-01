// BGAT studio. All Rights Reserved. 


#include "Weapon/STUF_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Logging/StructuredLog.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon,All,All);

ASTUF_BaseWeapon::ASTUF_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}

void ASTUF_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void ASTUF_BaseWeapon::Fire()
{
	//UE_LOGFMT(LogBaseWeapon,Warning, "Fire!");

	MakeShot();
}

void ASTUF_BaseWeapon::MakeShot()
{
	if(!GetWorld()) return; 

	FVector TraceStart,TraceEnd;

	// �������� ����� ����� �������� ����� �������� ����������� �����
	if(!GetTraceData(TraceStart,TraceEnd)) return;

	FHitResult HitResult;
	// ������ ����������� ����� ��������, ���� ���������� ���� �� ���������� ��������� HitResult
	MakeHit(HitResult,TraceStart,TraceEnd);

	// ���� ������������ ����, ������ ����� �������, ���� �� ��� ��� ����������� ����� ��������
	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(),GetMazzleWorldLocation(),HitResult.ImpactPoint,FColor::Red,false,3.0f,0.0,3.0f);
		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,10.0f,20.0f,FColor::Red,false,3.0f);

		//UE_LOGFMT(LogBaseWeapon,Warning, "Bone: {bone_name}",HitResult.BoneName);
	}
	else
	{
		DrawDebugLine(GetWorld(),GetMazzleWorldLocation(),TraceEnd,FColor::Red,false,3.0f,0.0,3.0f);
	}


}

// �������� ����������
APlayerController* ASTUF_BaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

// �������� ��������� ������ � ������������
bool ASTUF_BaseWeapon::GetPlayerViewPoint( FVector& ViewLocation,FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if(!Controller) nullptr;

	// �������� ������� ������ � �� ���������� � ������������
	Controller->GetPlayerViewPoint(ViewLocation,ViewRotation);
	return true;
}

// �������� ��������� ������ �� �������� ������ �������
FVector ASTUF_BaseWeapon::GetMazzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// �������� ����� ������ � ����� ����� 
bool ASTUF_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	// �������� ������� ������ � �� ���������� � ������������
	// GetPlayerViewPoint ��������� ���������� ������� � �� ��������, �������
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation,ViewRotation)) false;


	TraceStart = ViewLocation;	//SocketTransform.GetLocation();
	const FVector ShootDirection = ViewRotation.Vector(); // ��� x ������, ����� �� ����������� ��������	// SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart+ShootDirection*TraceMaxDistance;
	return true;

}

// ����������� ����� ��������
void ASTUF_BaseWeapon::MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;

	// �������� �������������� � ������������� ���������
	// �������� ����� ������ ������������ 
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	// �������� ���������� �� ����� �������� ����� ���� �������
	GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECollisionChannel::ECC_Visibility,CollisionParams);


}