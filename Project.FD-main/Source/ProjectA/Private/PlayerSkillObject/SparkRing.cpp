// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillObject/SparkRing.h"
#include "Components/SphereComponent.h"
#include "Characters/EmenyCharacter.h"
#include "TimerManager.h"

#include "Characters/HeroCharacter.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "BaseGamePlayTags.h"

#include "BaseFunctionLibrary.h"

ASparkRing::ASparkRing()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // 이 액터가 지닌 스피어 컴포넌트로 데미지를 입힐 범위를 정의
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
    SphereComponent->InitSphereRadius(DamageRadius);
    RootComponent = SphereComponent;

    // 오버랩 이벤트를 수신
    SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
}

void ASparkRing::BeginPlay()
{
    Super::BeginPlay();

    // 일정 시간 후 소멸
    GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &ASparkRing::DestroyEffect, Lifetime, false);

    // 주기적으로 데미지 부여
    GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ASparkRing::DamageEnemy, TickTime, true);
}

void ASparkRing::DestroyEffect()
{
    Destroy();
}

void ASparkRing::DamageEnemy()
{
    DamageEffect();

    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);

    for (AActor* OverlappingActor : OverlappingActors)
    {
        if (APawn* HitPawn = Cast<APawn>(OverlappingActor))
        {
            if (UBaseFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
            {
                ToOverlappedTarget.ExecuteIfBound(OverlappingActor);
            }
        }
    }
    Cast<AHeroCharacter>(GetInstigator())->GetHeroCombatComponent()->ResetSparkRingOverlappedActor();
}