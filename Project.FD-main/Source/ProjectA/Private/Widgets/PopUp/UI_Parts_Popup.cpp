// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PopUp/UI_Parts_Popup.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "GameInstance/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UUI_Parts_Popup::UpdatePopUpInfo(FItemInfo_ Data_)
{
	ItemData_ = Data_;

	Name->SetText(FText::FromString(Data_.Item_Name));

	Item_Level->SetText(FText::AsNumber(Data_.Item_Number));
	
	ItemTypeName->SetText(FText::FromString(Data_.AssetData.ItemType_Name));

	Rank->SetText(FText::FromString(Data_.AssetData.Rank_Name));

	AbilityTypeName->SetText(FText::FromString(Data_.AssetData.Bullet_Type_Name));


	if (Data_.Max_Hp != 0)
	{
		Damage->SetText(FText::AsNumber(Data_.Max_Hp));
	}
	else if (Data_.Max_Shield != 0)
	{
		Damage->SetText(FText::AsNumber(Data_.Max_Shield));
	}
	else if (Data_.Defence != 0)
	{
		Damage->SetText(FText::AsNumber(Data_.Defence));
	}


	switch (Data_.ID)
	{
	case 10001:
	{
		Set_Name->SetText(FText::FromString(Data_.AssetData.Item_SetName));
		break;
	}
	case 10002:
	{
		Set_Name->SetText(FText::FromString(Data_.AssetData.Item_SetName));
		break;
	}
	default:
		break;
	}

	Item_TierGlow->SetBrushTintColor(FSlateColor(FLinearColor(Data_.AssetData.Rank_Color.R, Data_.AssetData.Rank_Color.G, Data_.AssetData.Rank_Color.B)));

	SetItem_Num();
	SetItem_Image();

}

void UUI_Parts_Popup::SetItem_Num()
{
	FString Text;
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance)
	{
		switch (ItemData_.ID)
		{
		case 10001:
			Text = TEXT("( ") + FString::FromInt(GameInstance->GetSetItemNum()) + TEXT(" / ") + TEXT("4") + TEXT(" )");
			Active_set_Num->SetText(FText::FromString(Text));
			break;

		case 10002:
			Text = TEXT("( ") + FString::FromInt(4 - GameInstance->GetSetItemNum()) + TEXT(" / ") + TEXT("4") + TEXT(" )");
			Active_set_Num->SetText(FText::FromString(Text));
			break;

		default:
			break;
		}
	}

}

void UUI_Parts_Popup::SetItem_Image()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TArray<FItemInfo_> Set_ItemData = GameInstance->GetSetItemData();

	if (GameInstance)
	{
		for (int i = 0; i < Set_ItemData.Num(); i++)
		{
			if (ItemData_.ID == Set_ItemData[i].ID)
			{
				switch (Set_ItemData[i].ItemType)
				{
				case ItemType::ITEM_EXPERORPARTS_1:
					Parts_1->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 1)));
					break;

				case ItemType::ITEM_EXPERORPARTS_2:
					Parts_2->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 1)));
					break;

				case ItemType::ITEM_EXPERORPARTS_3:
					Parts_3->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 1)));
					break;

				case ItemType::ITEM_EXPERORPARTS_4:
					Parts_4->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 1)));
					break;

				default:
					break;
				}
			}
			else
			{
				switch (Set_ItemData[i].ItemType)
				{
				case ItemType::ITEM_EXPERORPARTS_1:
					Parts_1->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 0.3)));
					break;

				case ItemType::ITEM_EXPERORPARTS_2:
					Parts_2->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 0.3)));
					break;

				case ItemType::ITEM_EXPERORPARTS_3:
					Parts_3->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 0.3)));
					break;

				case ItemType::ITEM_EXPERORPARTS_4:
					Parts_4->SetBrushTintColor(FSlateColor(FLinearColor(1, 1, 1, 0.3)));
					break;

				default:
					break;
				}
			}
		
		}

	}

}
