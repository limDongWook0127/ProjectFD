// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
    CurrentEquippedWeapon,
    LeftHand,
    RightHand,
};


class AWeaponBase;

/**
 * 
 */

UCLASS()
class PROJECTA_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
    //������ ���� ���
    UFUNCTION(BlueprintCallable, Category = "Hero")
    void RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon, bool bRegisterAsEquippedWeapon = false);

    UFUNCTION(BlueprintCallable, Category = "Hero")//���� ���� �Լ�
    void RegisterSpawnedDualWeapon(FGameplayTag WeaponTag1, FGameplayTag WeaponTag2, AWeaponBase* Weapon, AWeaponBase* Weapon2, bool bRegisterAsEquippedWeapon = false);

    //�ɸ��Ͱ� �޴��ϴ� ����
    UFUNCTION(BlueprintCallable, Category = "Hero")
    AWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;

    //ĳ���Ͱ� ������ ������ �±�
    UPROPERTY(BlueprintReadWrite, Category = "Hero")
    FGameplayTag CurrentEquippedWeaponTag;

    UPROPERTY(BlueprintReadWrite, Category = "Hero")
    FGameplayTag CurrentEquippedWeaponTag2; //�߰��� ����

    //ĳ���Ͱ� ������ ����
    UFUNCTION(BlueprintCallable, Category = "Hero")                                                                  
    AWeaponBase* GetCharacterCurrentEquippedWeapon() const;

    UFUNCTION(BlueprintCallable, Category = "Hero")
    AWeaponBase* GetCharacterCurrentSecondEquippedWeapon() const;//�߰��� �Լ�

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ToggleWeaponCollsion(bool bUse, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

    UFUNCTION(BlueprintCallable, Category = "Combat")//���� ���� �Լ�
    void ToggleWeaponsCollsion(bool bUse, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

    // HiyDetection
    virtual void OnHitTargetActor(AActor* HitActor);
    virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
    TArray<AActor*> OverlappedActors;
	
private:
    //ĳ���ʹ� ���� ���⸦ ������ �� �ִ�.
    TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;
};
