// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

class UHeroPawnUIComponent;
class UEnemyPawnUIComponent;
/**
 * 
 */
UCLASS()
class PROJECTA_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningHeroUIComponentInitialized(UHeroPawnUIComponent* HeroUIComponent);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyPawnUIComponent* EnemyPawnUIComponent);
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* EnemyActor);
};
