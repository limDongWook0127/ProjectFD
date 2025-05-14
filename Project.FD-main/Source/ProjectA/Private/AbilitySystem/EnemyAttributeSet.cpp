// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"
#include "BaseGamePlayTags.h"
#include "BaseFunctionLibrary.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/Widget/PawnUIComponent.h"
#include "Components/Widget/HeroPawnUIComponent.h"


UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitCurrentShield(1.0f);
	InitMaxShield(1.0f);
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("DestroyShield"));
	if (cachedUIInterface.IsValid() == false)
	{
		cachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());

	}

	checkf(cachedUIInterface.IsValid(), TEXT("%s does not Implementation IpawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorLabel());

	UPawnUIComponent* PawnUIComponent = cachedUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("can not load PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentShieldAttribute())
	{
		const float NewCurrentShield = FMath::Clamp(GetCurrentShield(), 0.f, GetMaxShield());
		SetCurrentShield(NewCurrentShield);

		PawnUIComponent->OnCurrentShieldChanged.Broadcast(GetCurrentShield() / GetMaxShield());
		
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeShield = GetCurrentShield();
		const float Damage = GetDamageTaken();

		const float NewCurrentShield = FMath::Clamp(BeforeShield - Damage, 0.f, GetMaxShield());
		SetCurrentShield(NewCurrentShield);
		if (NewCurrentShield == 0.f)
		{
			UBaseFunctionLibrary::AddPlaygameTagActor(Data.Target.GetAvatarActor(), BaseGamePlayTags::Enemy_Status_ShieldDestroy);
			const float BeforeHp = GetCurrentHp();
			 
			const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.f, GetMaxHP());
			SetCurrentHp(NewCurrentHp);
			if (NewCurrentHp < GetMaxHP() /2)
			{
				UBaseFunctionLibrary::AddPlaygameTagActor(Data.Target.GetAvatarActor(), BaseGamePlayTags::Boss_Status_Berserk);
			}
			if (NewCurrentHp == 0.f)
			{
				// character Death Process
				UBaseFunctionLibrary::AddPlaygameTagActor(Data.Target.GetAvatarActor(), BaseGamePlayTags::Shared_Status_Death);
			}
		}
		
		//const FString DebugString = FString::Printf(TEXT("Befor Hp : %f, Damage : %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		//Debug::Print(DebugString, FColor::Red);

		PawnUIComponent->OnCurrentShieldChanged.Broadcast(GetCurrentShield() / GetMaxShield());
		PawnUIComponent->OnCurrentHpChanged.Broadcast(GetCurrentHp() / GetMaxHP());
	
		
	}
}

void UEnemyAttributeSet::ShieldReset()
{
	float NewShield = GetMaxShield();
	UE_LOG(LogTemp, Warning, TEXT("Resetting shield to: %f"), NewShield);
	SetCurrentShield(NewShield);
}
