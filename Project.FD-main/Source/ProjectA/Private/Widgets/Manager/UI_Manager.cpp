// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Manager/UI_Manager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UUI_Manager::Push_Widget(TSubclassOf<UUserWidget> Widget_)
{
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), Widget_);

	// ���ÿ� �߰�
	Widget_Stacks.Add(NewWidget);
	
	// ǥ��
	AddToViewPort_Widget(NewWidget);

}


void UUI_Manager::Remove_Widget()
{

}


void UUI_Manager::AddToViewPort_Widget(UUserWidget* Widget_)
{

}


void UUI_Manager::OnPressed_Button()
{

}
