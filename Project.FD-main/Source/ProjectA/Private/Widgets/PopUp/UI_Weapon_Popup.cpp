// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PopUp/UI_Weapon_Popup.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Data/DT_ItemInfo.h"

void UUI_Weapon_Popup::UpdatePopUpInfo(FItemInfo_ Data_)
{

	Name->SetText(FText::FromString(Data_.Item_Name));

	Item_Level->SetText(FText::AsNumber(Data_.Item_Number));

	DPS->SetText(FText::AsNumber(Data_.DPS()));

	WeaponType->SetText(FText::FromString(Data_.AssetData.ItemType_Name));

	Rank->SetText(FText::FromString(Data_.AssetData.Rank_Name));

	BulletType->SetText(FText::FromString(Data_.AssetData.Bullet_Type_Name));

	Damage->SetText(FText::AsNumber(Data_.Damage));

	Capacity->SetText(FText::AsNumber(Data_.Bullet_Capacity));

	Atk_Speed->SetText(FText::AsNumber(Data_.AttackSpeed));

	WeaponType_Image->SetBrushFromTexture(Data_.AssetData.Socket_Type);

	BulletType_Image->SetBrushFromTexture(Data_.AssetData.BulletIcon);

	Item_TierGlow->SetBrushTintColor(FSlateColor(FLinearColor(Data_.AssetData.Rank_Color.R, Data_.AssetData.Rank_Color.G, Data_.AssetData.Rank_Color.B)));

}
