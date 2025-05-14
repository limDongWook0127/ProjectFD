// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PopUp/UI_Reactor_Popup.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Data/DT_ItemInfo.h"

void UUI_Reactor_Popup::UpdatePopUpInfo(FItemInfo_ Data_)
{
	Name->SetText(FText::FromString(Data_.Item_Name));

	Item_Level->SetText(FText::AsNumber(Data_.Item_Number));

	SkillDamage->SetText(FText::AsNumber(Data_.Skill_Damage));

	SkillDamage_1->SetText(FText::AsNumber(Data_.Skill_Damage));
	SkillDamage_2->SetText(FText::AsNumber(Data_.Skill_Damage));
	SkillDamage_3->SetText(FText::AsNumber(Data_.Skill_Damage));
	SkillDamage_4->SetText(FText::AsNumber(Data_.Skill_Damage));

	Rank->SetText(FText::FromString(Data_.AssetData.Rank_Name));

	SecondAttack_Damage->SetText(FText::AsNumber(Data_.Secondary_Attack));

	Item_TierGlow->SetBrushTintColor(FSlateColor(FLinearColor(Data_.AssetData.Rank_Color.R, Data_.AssetData.Rank_Color.G, Data_.AssetData.Rank_Color.B)));

	
}
