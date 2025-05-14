// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UI_PopUpBase.h"
#include "UI_Reactor_Popup.generated.h"


class UTextBlock;
class UImage;
struct FItemInfo_;
struct FSlateBrush;


/**
 * 
 */
UCLASS()
class PROJECTA_API UUI_Reactor_Popup : public UUI_PopUpBase
{
	GENERATED_BODY()

public:
	void UpdatePopUpInfo(FItemInfo_ Data_);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Level;

	//========================================
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDamage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDamage_1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDamage_2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDamage_3;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDamage_4;
	//========================================

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SecondAttack_Damage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Rank;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierGlow;
	
};
