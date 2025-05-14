// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UI_PopUpBase.h"
#include "Data/DT_ItemInfo.h"
#include "UI_Parts_Popup.generated.h"

class UTextBlock;
class UImage;
struct FSlateBrush;

/**
 * 
 */
UCLASS()
class PROJECTA_API UUI_Parts_Popup : public UUI_PopUpBase
{
	GENERATED_BODY()

public:
	void UpdatePopUpInfo(FItemInfo_ Data_);

	FItemInfo_ ItemData_;

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Level;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemTypeName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityTypeName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Rank;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Damage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Set_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Active_set_Num;


	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierGlow;

	UPROPERTY(meta = (BindWidget))
	UImage* Parts_1;

	UPROPERTY(meta = (BindWidget))
	UImage* Parts_2;

	UPROPERTY(meta = (BindWidget))
	UImage* Parts_3;

	UPROPERTY(meta = (BindWidget))
	UImage* Parts_4;
	

	void SetItem_Num();
	void SetItem_Image();
};
