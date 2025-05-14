// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EnemyGameplayAbility.h"
#include "Characters/EmenyCharacter.h"
#include "BaseGamePlayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "BaseFunctionLibrary.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Items/Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"


AEmenyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (CachedEnemyCharacter.IsValid() == false)
	{
		CachedEnemyCharacter = Cast<AEmenyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat)
{

	check(Effect);

	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, GetAbilityLevel(), ContextHandle);

	SpecHandle.Data->SetSetByCallerMagnitude(BaseGamePlayTags::Shared_SetByCaller_BaseDamage, DamageFloat.GetValueAtLevel(GetAbilityLevel()));

	return SpecHandle;
}

void UEnemyGameplayAbility::OnDeathCollisionSettings(AActor* Actor)
{
	UCapsuleComponent* CapsuleComp = GetEnemyCharacterFromActorInfo()->GetCapsuleComponent();
	
	if (CapsuleComp)
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}

	UPawnCombatComponent* EnemyCombatComp = UBaseFunctionLibrary::NativeGetPawnCombatComponentFromActor(Actor);
	if (!EnemyCombatComp)
	{
		return;
	}
	else if (EnemyCombatComp)
	{
		if (AWeaponBase* FirstWeapon = EnemyCombatComp->GetCharacterCurrentEquippedWeapon())
		{
			UBoxComponent* WeaponCollsionBox = FirstWeapon->GetWeaponCollisionBox();
			WeaponCollsionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
		}
		
		if (AWeaponBase* SecondWeapon = EnemyCombatComp->GetCharacterCurrentSecondEquippedWeapon())
		{
			UBoxComponent* WeaponCollsionBox = SecondWeapon->GetWeaponCollisionBox();
			WeaponCollsionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

}

float UEnemyGameplayAbility::TeleportAnimationCalculate(FVector StrafingLocation)
{
	FVector CurrentLocation = GetEnemyCharacterFromActorInfo()->GetActorLocation();
	FVector Direction = StrafingLocation - CurrentLocation;
	FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	// Yaw만 추출하고, 범위 -180 ~ 180으로 정규화
	float NormalizedYaw = Rotation.Yaw;
	UE_LOG(LogTemp, Warning, TEXT("NormalizedYaw:%f"), NormalizedYaw);
	if (-45 <= NormalizedYaw && NormalizedYaw < 45)//Forward
	{
		return NormalizedYaw;
	}
	else if (45 <= NormalizedYaw && NormalizedYaw < 135)//LEFT
	{
		return NormalizedYaw;
	}
	else if (-135 <= NormalizedYaw && NormalizedYaw < -45)//RIGHT
	{
		return NormalizedYaw;
	}
	else
	{
		return NormalizedYaw;
	}
}
