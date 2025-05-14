// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UI_SlotBase.h"
#include "Data/DT_ItemInfo.h"
#include "UI_Reactor_Slot.generated.h"


class UImage;
class UTextBlock;
struct FSlateBrush;

/**
 * 
 */
UCLASS()
class PROJECTA_API UUI_Reactor_Slot : public UUI_SlotBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Level;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierBar;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierGlow;

	void UpdateInfo(struct FItemInfo_ Data_);

	FSlateBrush SlateBrush;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	FItemInfo_ ItemData_Num;
	
};
