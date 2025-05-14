// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UI_PopUpBase.h"
#include "UI_Weapon_Popup.generated.h"


class UTextBlock;
class UImage;
struct FItemInfo_;
struct FSlateBrush;


/**
 * 
 */
UCLASS()
class PROJECTA_API UUI_Weapon_Popup : public UUI_PopUpBase
{
	GENERATED_BODY()

public:
	void UpdatePopUpInfo(FItemInfo_ Data_);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Level;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DPS;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Rank;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BulletType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Damage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Capacity;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Atk_Speed;

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponType_Image;

	UPROPERTY(meta = (BindWidget))
	UImage* BulletType_Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierGlow;
	
};
