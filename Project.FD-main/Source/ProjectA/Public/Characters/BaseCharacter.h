// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;
class UBaseAttributeSet;
class UDataAsset_StartupBase;
class UMotionWarpingComponent;

UCLASS()
class PROJECTA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    UBaseAbilitySystemComponent* BaseAbilitySystemComponent;

   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    UBaseAttributeSet* BaseAttributeSet;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
    UMotionWarpingComponent* MotionWarpingComponent;

    //동기식으로 데이터를 불러온다
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "StartupData")
    TSoftObjectPtr<UDataAsset_StartupBase> StartupData;
    

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    virtual void PossessedBy(AController* NewController) override;

    virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
    virtual UPawnUIComponent* GetPawnUIComponent() const override;

public:
    FORCEINLINE UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const { return BaseAbilitySystemComponent; }
    FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const { return BaseAttributeSet; }
};
