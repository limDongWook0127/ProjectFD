// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI_Manager.generated.h"

/**
 * 
 */
class UUserWidget;

UCLASS()
class PROJECTA_API UUI_Manager : public UObject
{
	GENERATED_BODY()

public:
	// 스택 추가
	UFUNCTION(BlueprintCallable)
	void Push_Widget(TSubclassOf<UUserWidget> Widget_);

	// 스택에서 최상단 제거
	void Remove_Widget();

	// 화면에 표시
	UFUNCTION(BlueprintCallable)
	void AddToViewPort_Widget(UUserWidget* Widget_);

	// 버튼 누를시
	UFUNCTION(BlueprintCallable)
	void OnPressed_Button();


private:
	TArray<UUserWidget*> Widget_Stacks;

};
