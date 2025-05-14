// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HeroGameplayAbility.h"
#include "BaseType/BaseStructType.h"

void UBaseAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid())
    {
        return;
    }

    //주입한 스펙으로 입력 실행
    for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
    {
        if (!Spec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

        TryActivateAbility(Spec.Handle);
    }
}

void UBaseAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
    
}

void UBaseAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FHeroAbilitySet>& WeaponAbilities, int32 Level, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
    if (WeaponAbilities.IsEmpty())
    {
        return;
    }

    for (const FHeroAbilitySet& WeaponAbilitySet : WeaponAbilities)
    {
        if (!WeaponAbilitySet.IsValid()) continue;

        FGameplayAbilitySpec Spec(WeaponAbilitySet.AbilityToGrant);
        Spec.SourceObject = GetAvatarActor();
        Spec.Level = Level;
        Spec.DynamicAbilityTags.AddTag(WeaponAbilitySet.InputTag);
        OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(Spec));
        
    }
}

void UBaseAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& SpecHandlesToRemove)
{
    if (SpecHandlesToRemove.IsEmpty())
    {
        return;
    }

    for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandlesToRemove)
    {
        if (SpecHandle.IsValid())
        {
            ClearAbility(SpecHandle);
        }
    }

    SpecHandlesToRemove.Empty();
}

bool UBaseAbilitySystemComponent::TryActivatedAbilityByTag(FGameplayTag Tag)
{
    check(Tag.IsValid());

    TArray<FGameplayAbilitySpec*> AbilitySpecs;

    // 이 함수는 활성화 가능한 모듬 게임 어빌리티 스팩을 가져온다
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

    // abilityspecs 배열에 받은 데이터가 있으면
    if (!AbilitySpecs.IsEmpty())
    {
        const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
        FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

        check(AbilitySpec);

        if (!AbilitySpec->IsActive())
        {
            return TryActivateAbility(AbilitySpec->Handle);
        }

    }
    return false;
}

bool UBaseAbilitySystemComponent::TryDeactivateAbilityByTag(FGameplayTag Tag)
{
    check(Tag.IsValid());

    TArray<FGameplayAbilitySpec*> AbilitySpecs;

    GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

    if (AbilitySpecs.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No abilities found with the specified tag."));
        return false;
    }

    const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
    FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

    check(AbilitySpec);

    if (AbilitySpec->IsActive())
    {
        ClearAbility(AbilitySpec->Handle);
        UE_LOG(LogTemp, Warning, TEXT("Ability deactivated successfully."));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ability is not active."));
        return false;
    }
}

FGameplayAbilitySpecHandle UBaseAbilitySystemComponent::GetHandleByTag(FGameplayTag Tag)
{
    check(Tag.IsValid());

    TArray<FGameplayAbilitySpec*> AbilitySpecs;

    // 이 함수는 활성화 가능한 모듬 게임 어빌리티 스팩을 가져온다
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

    // abilityspecs 배열에 받은 데이터가 있으면
    if (!AbilitySpecs.IsEmpty())
    {
        const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
        FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

        check(AbilitySpec);

        if (!AbilitySpec->IsActive())
        {
            return AbilitySpec->Handle;
        }
    }

    return FGameplayAbilitySpecHandle();
}
