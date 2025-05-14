// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "HeroCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UHeroCombatComponent;
class UHeroPawnUIComponent;
class UInventory_Component;
class UBulletSystem_Component;

class ALandingSpark;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class PROJECTA_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();
	
private:
	virtual void BeginPlay() override;
	

private:
#pragma region Components
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
    UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "UI", meta = (AllowPrivateAccess = "true"))
	UHeroPawnUIComponent* HeroUIComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "UI", meta = (AllowPrivateAccess = "true"))
	UInventory_Component* InventoryComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "UI", meta = (AllowPrivateAccess = "true"))
	UBulletSystem_Component* Bullet_Component;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, category = "State", meta = (AllowPrivateAccess = "true"))
	bool bIsDoubleJump;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, category = "State", meta = (AllowPrivateAccess = "true"))
	bool bIsEvading;
#pragma endregion

#pragma region Inputs
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);
	void Input_Run(const FInputActionValue& InputActionValue);

    void Input_AbilityInputPressed(FGameplayTag InputTag);
    void Input_AbilityInputReleased(FGameplayTag InputTag);
#pragma endregion

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "LandingSpark", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ALandingSpark> LandingSparkClass;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	//UI
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroPawnUIComponent* GetHeroUIComponent() const override;

public:
    FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }

	void EndAbilityByTag(FGameplayTag Tag);
	
	virtual void Landed(const FHitResult& Hit) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void JumpFx();

	UFUNCTION(BlueprintImplementableEvent)
	void DoubleJumpFx();
};
