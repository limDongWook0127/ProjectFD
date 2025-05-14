// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BaseGameplayAbility.h"
#include "EnemyGameplayAbility.generated.h"

class AEmenyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECTA_API UEnemyGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	AEmenyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void OnDeathCollisionSettings(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float TeleportAnimationCalculate(FVector StrafingLocation);

private:
	TWeakObjectPtr<AEmenyCharacter> CachedEnemyCharacter;
};
