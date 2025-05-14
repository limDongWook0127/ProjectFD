// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillObject/SparkLaser.h"
#include "Components/SphereComponent.h"
#include <Characters/HeroCharacter.h>
#include "Components/Combat/HeroCombatComponent.h"
#include <BaseFunctionLibrary.h>

void ASparkLaser::DestroyEffect()
{
    Destroy();
}

void ASparkLaser::DamageEnemy(AActor* HitActor)
{
    if (APawn* HitPawn = Cast<APawn>(HitActor))
    {
        if (UBaseFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
        {
            ToOverlappedTarget.ExecuteIfBound(HitActor);
        }
    }
}
