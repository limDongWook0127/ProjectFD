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
    //생성된 무기 등록
    UFUNCTION(BlueprintCallable, Category = "Hero")
    void RegisterSpawnedWeapon(FGameplayTag WeaponTag, AWeaponBase* Weapon, bool bRegisterAsEquippedWeapon = false);

    UFUNCTION(BlueprintCallable, Category = "Hero")//내가 만든 함수
    void RegisterSpawnedDualWeapon(FGameplayTag WeaponTag1, FGameplayTag WeaponTag2, AWeaponBase* Weapon, AWeaponBase* Weapon2, bool bRegisterAsEquippedWeapon = false);

    //케릭터가 휴대하는 무기
    UFUNCTION(BlueprintCallable, Category = "Hero")
    AWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTag) const;

    //캐릭터가 소유한 무기의 태그
    UPROPERTY(BlueprintReadWrite, Category = "Hero")
    FGameplayTag CurrentEquippedWeaponTag;

    UPROPERTY(BlueprintReadWrite, Category = "Hero")
    FGameplayTag CurrentEquippedWeaponTag2; //추가한 변수

    //캐릭터가 장착한 무기
    UFUNCTION(BlueprintCallable, Category = "Hero")                                                                  
    AWeaponBase* GetCharacterCurrentEquippedWeapon() const;

    UFUNCTION(BlueprintCallable, Category = "Hero")
    AWeaponBase* GetCharacterCurrentSecondEquippedWeapon() const;//추가한 함수

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ToggleWeaponCollsion(bool bUse, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

    UFUNCTION(BlueprintCallable, Category = "Combat")//내가 만든 함수
    void ToggleWeaponsCollsion(bool bUse, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

    // HiyDetection
    virtual void OnHitTargetActor(AActor* HitActor);
    virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
    TArray<AActor*> OverlappedActors;
	
private:
    //캐릭터는 여러 무기를 소유할 수 있다.
    TMap<FGameplayTag, AWeaponBase*> CharacterCarriedWeaponMap;
};
