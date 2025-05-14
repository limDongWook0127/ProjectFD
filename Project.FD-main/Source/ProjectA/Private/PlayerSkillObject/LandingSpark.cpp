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

    // �� ���Ͱ� ���� ���Ǿ� ������Ʈ�� �������� ���� ������ ����
    USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
    SphereComponent->InitSphereRadius(DamageRadius);
    RootComponent = SphereComponent;

    // ������ �̺�Ʈ�� ����
    SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALandingSpark::OnCollisionBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ALandingSpark::BeginPlay()
{
	Super::BeginPlay();
	
    // ���� �ð� �� �Ҹ�
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALandingSpark::DestroyEffect, Lifetime, false);
}

void ALandingSpark::DestroyEffect()
{
    Destroy();
}