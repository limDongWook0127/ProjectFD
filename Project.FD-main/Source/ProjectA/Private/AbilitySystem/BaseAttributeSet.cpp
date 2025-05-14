// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"
#include "BaseGamePlayTags.h"
#include "BaseFunctionLibrary.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/Widget/PawnUIComponent.h"
#include "Components/Widget/HeroPawnUIComponent.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitCurrentHp(1.0f);
	InitMaxHP(1.0f);   
	InitCurrentMp(1.0f);
	InitMaxMp(1.0f);
	InitAttack(1.0f);
	InitDefence(1.0f);
	InitDamageTaken(1.0f);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (cachedUIInterface.IsValid() == false)
	{
		cachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(cachedUIInterface.IsValid(), TEXT("%s does not Implementation IpawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorLabel());

	UPawnUIComponent* PawnUIComponent = cachedUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("can not load PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.f, GetMaxHP());
		SetCurrentHp(NewCurrentHp);

		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHP());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentMpAttribute())
	{
		const float NewCurrentMp = FMath::Clamp(GetCurrentMp(), 0.f, GetMaxMp());
		SetCurrentMp(NewCurrentMp);

		if (UHeroPawnUIComponent* HeroUiComponent = cachedUIInterface->GetHeroUIComponent())
		{
			HeroUiComponent->OnCurrentMPChanged.Broadcast(GetCurrentMp() / GetMaxMp());
		}
		
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetCurrentHp();
		const float Damage = GetDamageTaken();

		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.f, GetMaxHP());
		SetCurrentHp(NewCurrentHp);

		//const FString DebugString = FString::Printf(TEXT("Befor Hp : %f, Damage : %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		//Debug::Print(DebugString, FColor::Red);

		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHP());

		if (NewCurrentHp == 0.f)
		{
			// character Death Process
			UBaseFunctionLibrary::AddPlaygameTagActor(Data.Target.GetAvatarActor(), BaseGamePlayTags::Shared_Status_Death);
		}
	}
}
