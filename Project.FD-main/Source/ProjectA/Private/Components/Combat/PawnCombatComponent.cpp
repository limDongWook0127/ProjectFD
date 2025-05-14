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

	//������ ����� ����� �Ǹ� �����������⸦ ����
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

	//������ ����� ����� �Ǹ� �����������⸦ ����
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = WeaponTag1;
		CurrentEquippedWeaponTag2 = WeaponTag2;

	}
}

AWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	//Map �����̳ʿ� WeaponTag�� �����Ͱ� ������ AWeaponBase ��ȯ
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
		// ���� ������ ���� �� ���� ���� �ݸ��� ����
		TArray<AWeaponBase*> Weapons;

		//�� ���� ��� ��������
		if (CharacterCarriedWeaponMap.Contains(CurrentEquippedWeaponTag))
		{
			AWeaponBase* Weapon = GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
			if (Weapon)
			{
				Weapons.Add(Weapon);
			}
		}

		// �� ��° ���� �±׷� �� ��° ���� ��������
		if (CharacterCarriedWeaponMap.Contains(CurrentEquippedWeaponTag2)) // �� ��° �±�
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

		// OverlappedActors ����
		if (!bUse)
		{
			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// �ڽĿ��� ����
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	// �ڽĿ��� ����
}
