// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Interfaces/PawnUIInterface.h"
#include "EnemyAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTA_API UEnemyAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UEnemyAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData CurrentShield;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, CurrentShield)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxShield)

private:
	TWeakInterfacePtr<IPawnUIInterface> cachedUIInterface;

protected:
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
	UFUNCTION(BlueprintCallable, Category = "AttributeSet")
	void ShieldReset();
};

