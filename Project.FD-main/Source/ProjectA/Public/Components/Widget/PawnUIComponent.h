// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);


class UHeroPawnUIComponent;

/**
 * 
 */
UCLASS()
class PROJECTA_API UPawnUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentHpChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentShieldChanged;
	


};
