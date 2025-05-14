// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BaseEnumType.h"
#include "EmenyCharacter.generated.h"


class UEnemyCombatComponent;
class UEnemyPawnUIComponent;
class UWidgetComponent;
class AWeaponBase;
class UMaterialInstanceDynamic;
class UEnemyAttributeSet;

/**
 * 
 */
UCLASS()
class PROJECTA_API AEmenyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEmenyCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FString EnemyName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyPawnUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEnemyAttributeSet* EnemyAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnAnimation")
	UAnimMontage* SpawnMontage;
	UFUNCTION(BlueprintCallable, Category = "SpawnAnimation")
	void PlaySpawnMontage();

	virtual void PossessedBy(AController* Newcontroller) override;
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyPawnUIComponent* GetEnemyUIComponent() const override;

	virtual void BeginPlay() override;


#pragma region ShieldMonster Add
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShieldState")
	EShieldState ShieldState = EShieldState::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponBase* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UMaterialInstanceDynamic* WeaponMat;

public:
	UFUNCTION(BlueprintCallable, Category = "ShieldState")
	EShieldState SetShieldState(EShieldState State);

	UFUNCTION(BlueprintCallable, Category = "ShieldState")
	EShieldState GetShieldState();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(AWeaponBase* Weapon, UMaterialInstanceDynamic* Mat);
#pragma endregion ShieldEnd Add


//end shield Monster Add

private:
	void InitEnemyStartUpDate();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }



};
