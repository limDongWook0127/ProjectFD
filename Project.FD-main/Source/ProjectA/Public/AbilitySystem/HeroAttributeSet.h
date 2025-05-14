// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "HeroAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTA_API UHeroAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UHeroAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData UsingMana;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, UsingMana)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData CurrentShield;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, CurrentShield)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MaxShield)

	UPROPERTY(BlueprintReadOnly, Category = "Passive")
	FGameplayAttributeData CurrentPassive;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, CurrentPassive)

	UPROPERTY(BlueprintReadOnly, Category = "Passive")
	FGameplayAttributeData MaxPassive;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, MaxPassive)

	UPROPERTY(BlueprintReadOnly, Category = "Passive")
	FGameplayAttributeData UsingPassive;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, UsingPassive)

	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	FGameplayAttributeData GainingShield;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, GainingShield)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData GainingHeal;
	ATTRIBUTE_ACCESSORS(UHeroAttributeSet, GainingHeal)

private:
	TWeakInterfacePtr<IPawnUIInterface> cachedUIInterface;

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
