// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartupData/DataAsset_StartupEnemy.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"

void UDataAsset_StartupEnemy::GiveToAbilitySystemComponent(UBaseAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(ASC, Level);

	if (EnemyCombatAbilities.IsEmpty() == false)
	{
		for (const TSubclassOf<UEnemyGameplayAbility>& Abilityclass : EnemyCombatAbilities)
		{
			if (Abilityclass == nullptr) continue;
			FGameplayAbilitySpec AbilitySpec(Abilityclass);
			AbilitySpec.SourceObject = ASC->GetAvatarActor();
			AbilitySpec.Level = Level;
			ASC->GiveAbility(AbilitySpec);

		}
	}
}
