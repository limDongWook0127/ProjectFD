// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"

#include "BaseDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag), TEXT("%s has already been as carried weapon"), *WeaponTag.ToString());
	check(Weapon);

	CharacterCarriedWeaponMap.Emplace(WeaponTag, Weapon);

	Weapon->OnWeaponHitTarget.BindUObject(this, &UPawnCombatComponent::OnHitTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &UPawnCombatComponent::OnWeaponPulledFromTargetActor);

	//장착한 무기로 등록이 되면 현재장착무기를 변경
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag;
	}


	//const FString WeaponString = FString::Printf(TEXT("%s has been registerd using the tag: %s"),*Weapon->GetName(), *WeaponTag.ToString());
	//Debug::Print(WeaponString);

}

void UPawnCombatComponent::RegisterSpawnedDualWeapon(FGameplayTag WeaponTag1, FGameplayTag WeaponTag2, AWeaponBase* Weapon, AWeaponBase* Weapon2, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag1), TEXT("%s has already been as carried weapon"), *WeaponTag1.ToString());
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTag2), TEXT("%s has already been as carried weapon"), *WeaponTag2.ToString());
	check(Weapon);
	check(Weapon2);
	CharacterCarriedWeaponMap.Emplace(WeaponTag1, Weapon);
	CharacterCarriedWeaponMap.Emplace(WeaponTag2, Weapon2);

	Weapon->OnWeaponHitTarget.BindUObject(this, &UPawnCombatComponent::OnHitTargetActor);
	Weapon->OnWeaponPulledFromTarget.BindUObject(this, &UPawnCombatComponent::OnWeaponPulledFromTargetActor);

	//장착한 무기로 등록이 되면 현재장착무기를 변경
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag1;
		CurrentEquippedWeaponTag2 = WeaponTag2;

	}
}

AWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	//Map 컨테이너에 WeaponTag의 데이터가 있으면 AWeaponBase 반환
	if (CharacterCarriedWeaponMap.Contains(WeaponTag))
	{
		if (AWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeaponTag))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

AWeaponBase* UPawnCombatComponent::GetCharacterCurrentSecondEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag2.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag2);
	
}

void UPawnCombatComponent::ToggleWeaponCollsion(bool bUse, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWeaponBase* Weapon = GetCharacterCurrentEquippedWeapon();

		check(Weapon);

		if (bUse)
		{
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			// Debug::Print(Weapon->GetName() + TEXT(" Collision Enabled"), FColor::Green);


		}
		else
		{
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//  Debug::Print(Weapon->GetName() + TEXT(" Collision disabled"), FColor::Blue);

			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::ToggleWeaponsCollsion(bool bUse, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		// 현재 장착된 무기 두 개에 대해 콜리전 설정
		TArray<AWeaponBase*> Weapons;

		//두 무기 모두 가져오기
		if (CharacterCarriedWeaponMap.Contains(CurrentEquippedWeaponTag))
		{
			AWeaponBase* Weapon = GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
			if (Weapon)
			{
				Weapons.Add(Weapon);
			}
		}

		// 두 번째 무기 태그로 두 번째 무기 가져오기
		if (CharacterCarriedWeaponMap.Contains(CurrentEquippedWeaponTag2)) // 두 번째 태그
		{
			AWeaponBase* Weapon2 = GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag2);
			if (Weapon2)
			{
				Weapons.Add(Weapon2);
			}
		}
		for (AWeaponBase* Weapon : Weapons)
		{
			if (Weapon)
			{
				if (bUse)
				{
					Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					// Debug::Print(Weapon->GetName() + TEXT(" Collision Enabled"), FColor::Green);
				}
				else
				{
					Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					// Debug::Print(Weapon->GetName() + TEXT(" Collision Disabled"), FColor::Blue);
				}
			}
		}

		// OverlappedActors 비우기
		if (!bUse)
		{
			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 자식에서 구현
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	// 자식에서 구현
}
