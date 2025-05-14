// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillObject/SpawnSparkBall.h"
#include "Components/SphereComponent.h"
#include "Characters/EmenyCharacter.h"
#include "TimerManager.h"

#include "Characters/HeroCharacter.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "BaseGamePlayTags.h"

#include "BaseFunctionLibrary.h"


ASpawnSparkBall::ASpawnSparkBall()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // �� ���Ͱ� ���� ���Ǿ� ������Ʈ�� �������� ���� ������ ����
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
    SphereComponent->InitSphereRadius(DamageRadius);
    RootComponent = SphereComponent;

    // ������ �̺�Ʈ�� ����
    SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
}

void ASpawnSparkBall::BeginPlay()
{
    Super::BeginPlay();

    // ���� �ð� �� �Ҹ�
    GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &ASpawnSparkBall::DestroyEffect, Lifetime, false);

    // �ֱ������� ������ �ο�
    GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ASpawnSparkBall::DamageEnemy, TickTime, true);
}

void ASpawnSparkBall::DestroyEffect()
{
    //AHeroCharacter* Player = Cast<AHeroCharacter>(GetInstigator());
    //Player->EndAbilityByTag(BaseGamePlayTags::Player_Ability_Attack_SpawnSparkBallSkill);
    Destroy();
}

void ASpawnSparkBall::DamageEnemy()
{
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
    Cast<AHeroCharacter>(GetInstigator())->GetHeroCombatComponent()->ResetSparkBallOverlappedActor();
}
