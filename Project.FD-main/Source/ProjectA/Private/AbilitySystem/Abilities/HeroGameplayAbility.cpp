// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility.h"
#include "Characters/HeroCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGamePlayTags.h"
#include "Controllers/HeroController.h"

AHeroCharacter* UHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedHeroCharacter.IsValid())
    {
        CachedHeroCharacter = Cast<AHeroCharacter>(CurrentActorInfo->AvatarActor);
    }

    return CachedHeroCharacter.IsValid()? CachedHeroCharacter.Get() : nullptr;
}

AHeroController* UHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedHeroController.IsValid())
    {
        CachedHeroController = Cast<AHeroController>(CurrentActorInfo->PlayerController);

    }
    return CachedHeroController.IsValid()? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float BaseDamage, FGameplayTag AttackTypeTag, int32 ComboCount)
{
    check(Effect);

    // Contexthandle을 만들어서 타겟 정보 주입
    FGameplayEffectContextHandle ContextHandle;
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());


    // spechandle을 만들어서 contexthandle에 정보 주입
    FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

    SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Shared_SetByCaller_BaseDamage, BaseDamage);

    if (AttackTypeTag.IsValid())
    {
        SpecHandle.Data->SetSetByCallerMagnitude(AttackTypeTag, ComboCount);
    }

    return SpecHandle;
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroUsingPassiveEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float UsingPassive)
{
    check(Effect);

    // Contexthandle을 만들어서 타겟 정보 주입
    FGameplayEffectContextHandle ContextHandle;
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());


    // spechandle을 만들어서 contexthandle에 정보 주입
    FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

    SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Player_SetBycaller_UsingPassive, UsingPassive);

    return SpecHandle;
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroGainingShieldEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float GainShield)
{
    check(Effect);

    // Contexthandle을 만들어서 타겟 정보 주입
    FGameplayEffectContextHandle ContextHandle;
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());


    // spechandle을 만들어서 contexthandle에 정보 주입
    FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

    SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Player_SetBycaller_GainingShield, GainShield);

    return SpecHandle;
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroUsingManaEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float UsingMana)
{
    check(Effect);

    // Contexthandle을 만들어서 타겟 정보 주입
    FGameplayEffectContextHandle ContextHandle;
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());


    // spechandle을 만들어서 contexthandle에 정보 주입
    FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

    SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Player_SetBycaller_UsingMana, UsingMana);

    return SpecHandle;
}

FGameplayEffectSpecHandle UHeroGameplayAbility::MakeHeroGainingHealEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float GainingHeal)
{
    check(Effect);

    // Contexthandle을 만들어서 타겟 정보 주입
    FGameplayEffectContextHandle ContextHandle;
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());


    // spechandle을 만들어서 contexthandle에 정보 주입
    FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

    SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Player_SetBycaller_GainingHeal, GainingHeal);

    return SpecHandle;
}
