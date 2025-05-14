// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget/PawnUIComponent.h"
#include "HeroPawnUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UHeroPawnUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentMPChanged;

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentPassiveChanged;
	
};
