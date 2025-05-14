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
	// ���� �߰�
	UFUNCTION(BlueprintCallable)
	void Push_Widget(TSubclassOf<UUserWidget> Widget_);

	// ���ÿ��� �ֻ�� ����
	void Remove_Widget();

	// ȭ�鿡 ǥ��
	UFUNCTION(BlueprintCallable)
	void AddToViewPort_Widget(UUserWidget* Widget_);

	// ��ư ������
	UFUNCTION(BlueprintCallable)
	void OnPressed_Button();


private:
	TArray<UUserWidget*> Widget_Stacks;

};
