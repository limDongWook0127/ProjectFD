// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillObject/LandingSpark.h"
#include "Components/SphereComponent.h"
#include "Characters/EmenyCharacter.h"
#include "TimerManager.h"

#include "Characters/HeroCharacter.h"
#include "BaseGamePlayTags.h"

#include <BaseFunctionLibrary.h>
// Sets default values
ALandingSpark::ALandingSpark()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // 이 액터가 지닌 스피어 컴포넌트로 데미지를 입힐 범위를 정의
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
    SphereComponent->InitSphereRadius(DamageRadius);
    RootComponent = SphereComponent;

    // 오버랩 이벤트를 수신
    SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALandingSpark::OnCollisionBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ALandingSpark::BeginPlay()
{
	Super::BeginPlay();
	
    // 일정 시간 후 소멸
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALandingSpark::DestroyEffect, Lifetime, false);
}

void ALandingSpark::DestroyEffect()
{
    Destroy();
}