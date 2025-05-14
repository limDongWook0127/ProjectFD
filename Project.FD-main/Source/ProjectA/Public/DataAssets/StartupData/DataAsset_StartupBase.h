// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset_StartupBase.generated.h"

class UBaseGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class PROJECTA_API UDataAsset_StartupBase : public UDataAsset
{
	GENERATED_BODY()
public:

	//�ο��ϴ� ASC Level�� �ܰ� 1�ܰ� �⺻�ο�
	virtual void GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level = 1);

protected:
	//�ο����� ���� Ȱ��ȭ �Ǵ� �־��� �ɷµ�
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ActivateOnGivenAbilities;

	//Ư�� ���ǿ� ���� ���߹����̳� ������� �ɷµ�
	UPROPERTY(EditDefaultsOnly, Category="StartupData")
	TArray<TSubclassOf<UBaseGameplayAbility>> ReactiveAbilities;

	//�ɷºο�
	void GrantAbilities(const TArray<TSubclassOf<UBaseGameplayAbility>> GAs, UBaseAbilitySystemComponent* InASC, int32 Level);

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;

};
