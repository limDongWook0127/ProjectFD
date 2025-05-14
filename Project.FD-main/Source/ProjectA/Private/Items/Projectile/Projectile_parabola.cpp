// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Projectile/Projectile_parabola.h"
#include "Items/Projectile/ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"



AProjectile_parabola::AProjectile_parabola()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent->bAutoActivate = false;
}

void AProjectile_parabola::BeginPlay()
{
	Super::BeginPlay();

}



void AProjectile_parabola::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile_parabola::CalculateProjectileVelocity(FVector Start, FVector End, float LaunchSpeed)
{
	FVector OutLaunchVelocity;
	bool bSuggestVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Start,
		End,
		LaunchSpeed,
		true, // 높은 포물선
		0.0f,  // 발사체 충돌 반경
		0.0f,  // 기본 중력 값 사용
		ESuggestProjVelocityTraceOption::DoNotTrace, // 충돌 검사 없음
		FCollisionResponseParams::DefaultResponseParam, // 기본 충돌 응답
		TArray<AActor*>(), // 무시할 액터 없음
		false,// 디버그 선 활성화
		false);
}

AProjectile_parabola* AProjectile_parabola::SpawnProjectileParabola()
{
	UClass* Projectile = AProjectile_parabola::StaticClass();

	if (Projectile && GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		FTransform SpawnTransform = GetActorTransform();

		AProjectile_parabola* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile_parabola>(Projectile, SpawnTransform, SpawnParams);
		if (SpawnedProjectile)
		{
			return SpawnedProjectile;
		}

	}
	return nullptr;
}







