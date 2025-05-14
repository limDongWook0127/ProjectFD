// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "DataAsset_StartupHero.generated.h"

struct FHeroAbilitySet;
/**
 * 
 */
UCLASS()
class PROJECTA_API UDataAsset_StartupHero : public UDataAsset_StartupBase
{
	GENERATED_BODY()

protected:
    virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level = 1) override;
	 
private:
    UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta=(TitleProPerty="InputTag"))
    TArray<FHeroAbilitySet> HeroStartupAbilitySets;
};
