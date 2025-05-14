// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillObject/Bullet.h"
#include "Components/SphereComponent.h"
#include <BaseFunctionLibrary.h>

ABullet::ABullet()
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

void ABullet::DestroyEffect()
{
    Destroy();
}

void ABullet::DamageEnemy(AActor* HitActor)
{
    if (APawn* HitPawn = Cast<APawn>(HitActor))
    {
        if (UBaseFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
        {
            ToOverlappedTarget.ExecuteIfBound(HitActor);
        }
    }
}