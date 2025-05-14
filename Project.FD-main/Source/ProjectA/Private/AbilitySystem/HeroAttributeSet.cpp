// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HeroAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"
#include "BaseGamePlayTags.h"
#include "BaseFunctionLibrary.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/Widget/PawnUIComponent.h"
#include "Components/Widget/HeroPawnUIComponent.h"

UHeroAttributeSet::UHeroAttributeSet()
{
	InitCurrentShield(1.0f);
	InitMaxShield(1.0f);
	InitCurrentPassive(1.0f);
	InitMaxPassive(1.0f);
	InitUsingMana(1.0f);
	InitUsingPassive(1.0f);
	InitGainingShield(1.0f);
}

void UHeroAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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

		if (UHeroPawnUIComponent* HeroUIComponent = cachedUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentMPChanged.Broadcast(GetCurrentMp() / GetMaxMp());
		}

	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeShield = GetCurrentShield();
		const float BeforeHp = GetCurrentHp();
		const float Damage = GetDamageTaken();

		float NewCurrentShield = BeforeShield - Damage;

		if (NewCurrentShield < 0)
		{
			const float NewCurrentHp = FMath::Clamp(BeforeHp + NewCurrentShield, 0.f, GetMaxHP());
			SetCurrentHp(NewCurrentHp);
			PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHP());

			NewCurrentShield = 0.f;
			SetCurrentShield(NewCurrentShield);
			PawnUIComponent->OnCurrentShieldChanged.Broadcast(0.f);
		}
		else
		{
			SetCurrentShield(NewCurrentShield);
			PawnUIComponent->OnCurrentShieldChanged.Broadcast(GetCurrentShield() / GetMaxShield());
		}

		//const FString DebugString = FString::Printf(TEXT("BeforeShield : %f, Damage : %f, CurrentShield : %f"), BeforeShield, Damage, GetCurrentShield());
		//Debug::Print(DebugString, FColor::Red);


		// TODO:: - UI로 값을 전달
		if (GetCurrentHp() == 0.f)
		{
			// character Death Process
			UBaseFunctionLibrary::AddPlaygameTagActor(Data.Target.GetAvatarActor(), BaseGamePlayTags::Shared_Status_Death);
		}
	}

	if (Data.EvaluatedData.Attribute == GetUsingManaAttribute())
	{
		const float BeforeMp = GetCurrentMp();
		const float UsingMana_ = GetUsingMana();

		float NewCurrentMp = FMath::Clamp(BeforeMp - UsingMana_, 0.f, GetMaxMp());
		SetCurrentMp(NewCurrentMp);

		if (UHeroPawnUIComponent* HeroUIComponent = cachedUIInterface->GetHeroUIComponent())
		{
			if (GetCurrentMp() == 0.f)
			{
				HeroUIComponent->OnCurrentMPChanged.Broadcast(0.f);
			}
			else
			{
				HeroUIComponent->OnCurrentMPChanged.Broadcast(GetCurrentMp() / GetMaxMp());
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetUsingPassiveAttribute())
	{
		const float BeforePassive = GetCurrentPassive();
		const float UsingPassive_ = GetUsingPassive();

		float NewCurrentPassive = FMath::Clamp(BeforePassive - UsingPassive_, 0.f, GetMaxPassive());
		SetCurrentPassive(NewCurrentPassive);

		if (UHeroPawnUIComponent* HeroUIComponent = cachedUIInterface->GetHeroUIComponent())
		{
			if (GetCurrentPassive() == 0.f)
			{
				HeroUIComponent->OnCurrentPassiveChanged.Broadcast(0.f);
			}
			else
			{
				HeroUIComponent->OnCurrentPassiveChanged.Broadcast(GetCurrentPassive() / GetMaxPassive());
			}
		}
	}

	if (Data.EvaluatedData.Attribute == GetGainingShieldAttribute())
	{
		const float BeforeShield = GetCurrentShield();
		const float GainingShield_ = GetGainingShield();

		float NewCurrentShield = FMath::Clamp(BeforeShield + GainingShield_, 0.f, GetMaxShield());
		SetCurrentShield(NewCurrentShield);

		PawnUIComponent->OnCurrentShieldChanged.Broadcast(GetCurrentShield() / GetMaxShield());
	}

	if (Data.EvaluatedData.Attribute == GetGainingHealAttribute())
	{
		const float BeforeHp = GetCurrentHp();
		const float GainingHeal_ = GetGainingHeal();

		float NewCurrentHp = FMath::Clamp(BeforeHp + GainingHeal_, 0.f, GetMaxHP());
		SetCurrentHp(NewCurrentHp);

		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHP());
	}
}
