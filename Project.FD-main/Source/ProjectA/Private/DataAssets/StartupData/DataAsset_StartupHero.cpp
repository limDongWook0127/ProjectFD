// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupHero.h"
#include "AbilitySystem/Abilities/HeroGameplayAbility.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseType/BaseStructType.h"


void UDataAsset_StartupHero::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level)
{
    Super::GiveToAbilitySystemComponent(ASC, Level);

    for(const FHeroAbilitySet& AbilitySet : HeroStartupAbilitySets)
    {
        if (!AbilitySet.IsValid()) continue;
        
        FGameplayAbilitySpec Spec(AbilitySet.AbilityToGrant);
        Spec.SourceObject = ASC->GetAvatarActor();
        Spec.Level = Level;
        //동적태그 생성 
        Spec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        ASC->GiveAbility(Spec);
    }
}
