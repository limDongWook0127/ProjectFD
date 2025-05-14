// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapon/WeaponBase.h"
#include "BaseType/BaseStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "HeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API AHeroWeapon : public AWeaponBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
    FHeroWeaponData HeroWeaponData;

    UFUNCTION(BlueprintCallable)
    void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& SpecHandles);

    UFUNCTION(BlueprintPure)
    TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:

    TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};