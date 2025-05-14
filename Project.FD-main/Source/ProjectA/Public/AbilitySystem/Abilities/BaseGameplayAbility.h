// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseEnumType.h"
#include "BaseGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EBaseAbilityActivationPolcy : uint8
{
	OnTriggered,
	OnGiven
};


class UPawnCombatComponent;
class UBaseAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTA_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EBaseAbilityActivationPolcy AbilityActivationPolicy = EBaseAbilityActivationPolcy::OnTriggered;
	
    //CombatComponent 확보
    UFUNCTION(BlueprintPure, Category = "Ability")
    UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

    //BaseAbilitySystemComponent 확보
    UFUNCTION(BlueprintPure, Category = "Ability")
    UBaseAbilitySystemComponent* GetBaseAbilitySystemComponentFromActorInfo() const;

	//AvtivateGameplayEffectHandle 얻기
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta = (Display = "Apply Gameplay Effect Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, EBaseSuccessType& OutSuccessType);
};
