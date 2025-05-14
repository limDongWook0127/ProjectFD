// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "HeroGameplayAbility.generated.h"

class AHeroCharacter;
class AHeroController;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECTA_API UHeroGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintPure, Category = "Ability")
    AHeroCharacter* GetHeroCharacterFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Ability")
    AHeroController* GetHeroControllerFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Ability")
    UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Ability")
    FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float BaseDamaege, FGameplayTag AttackTypeTag, int32 ComboCount);

    UFUNCTION(BlueprintPure, Category = "Ability")
    FGameplayEffectSpecHandle MakeHeroUsingPassiveEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float UsingPassive);

    UFUNCTION(BlueprintPure, Category = "Ability")
    FGameplayEffectSpecHandle MakeHeroGainingShieldEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float GainShield);

    UFUNCTION(BlueprintPure, Category = "Ability")
    FGameplayEffectSpecHandle MakeHeroUsingManaEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float UsingMana);

    UFUNCTION(BlueprintPure, Category = "Ability")
    FGameplayEffectSpecHandle MakeHeroGainingHealEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float GainingHeal);

private:
    //�����ɸ����� ������ ������ �ִٸ� ĳ�� TWeakObjectPtr�� ���� ������ �������� ���� �� ��ü�� �ڵ����� �����մϴ�. (���� ������)
    TWeakObjectPtr<AHeroCharacter> CachedHeroCharacter;
    TWeakObjectPtr<AHeroController> CachedHeroController;

};
