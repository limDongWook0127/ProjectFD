// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapon/HeroWeapon.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGamePlayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PlayerSkillObject/HeroSkillBase.h"

#include "BaseDebugHelper.h"

AHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag Tag) const
{
    return Cast<AHeroWeapon>(GetCharacterCarriedWeaponByTag(Tag));
}

AHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
    return Cast<AHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float Level) const
{
    // 해당 레벨의 데이터를 얻어옴
    return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(Level);
}

void UHeroCombatComponent::RegisterSkillObject(AHeroSkillBase* SkillObject, ESkillType SkillType)
{
    switch (SkillType)
    {
    case ESkillType::LandingSpark:
    {
        SkillObject->ToOverlappedTarget.BindUObject(this, &UHeroCombatComponent::OnLandingSparkHitTargetActor);
        break;
    }
    case ESkillType::SparkBall:
    {
        SkillObject->ToOverlappedTarget.BindUObject(this, &UHeroCombatComponent::OnSparkBallHitTargetActor);
        break;
    }
    case ESkillType::SparkLaser:
    {
        SkillObject->ToOverlappedTarget.BindUObject(this, &UHeroCombatComponent::OnSparkLaserHitTargetActor);
        break;
    }
    case ESkillType::SparkRing:
    {
        SkillObject->ToOverlappedTarget.BindUObject(this, &UHeroCombatComponent::OnSparkRingHitTargetActor);
        break;
    }
    default:
        break;
    }
}

void UHeroCombatComponent::RegisterBulletObject(AHeroSkillBase* BulletObject)
{
    BulletObject->ToOverlappedTarget.BindUObject(this, &UHeroCombatComponent::OnBulletHitTargetActor);
}

void UHeroCombatComponent::ResetOverlappedActor()
{
    OverlappedActors.Empty();
}

void UHeroCombatComponent::ResetSparkBallOverlappedActor()
{
    SparkBallOverlappedActors.Empty();
}

void UHeroCombatComponent::ResetSparkRingOverlappedActor()
{
    SparkRingOverlappedActors.Empty();
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    //send Event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Shared_Event_MeleeHit, Data);
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Player_Event_HitPause, FGameplayEventData());
}

void UHeroCombatComponent::OnLandingSparkHitTargetActor(AActor* HitActor)
{
    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    //send Event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Player_Event_SkillHit_LandingSpark, Data);
}

void UHeroCombatComponent::OnSparkBallHitTargetActor(AActor* HitActor)
{
    if (SparkBallOverlappedActors.Contains(HitActor))
    {
        return;
    }

    SparkBallOverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    //send Event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Player_Event_SkillHit_SparkBall, Data);
}

void UHeroCombatComponent::OnSparkLaserHitTargetActor(AActor* HitActor)
{
    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    //send Event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Player_Event_SkillHit_SparkLaser, Data);
}

void UHeroCombatComponent::OnSparkRingHitTargetActor(AActor* HitActor)
{
    if (SparkRingOverlappedActors.Contains(HitActor))
    {
        return;
    }

    SparkRingOverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    //send Event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Player_Event_SkillHit_SparkRing, Data);
}

void UHeroCombatComponent::OnBulletHitTargetActor(AActor* HitActor)
{
    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;


    //send Event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGamePlayTags::Player_Event_Hit_Bullet, Data);
}
