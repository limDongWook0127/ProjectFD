// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UI_SlotBase.h"
#include "Data/DT_ItemInfo.h"
#include "Components/PanelWidget.h"
#include "UI_WeaponSlot.generated.h"


class UTextBlock;
class UImage;
class UBorder;
class UI_Weapon_Popup;
struct FItemInfo_;
struct FSlateBrush;


/**
 * 
 */
UCLASS()
class PROJECTA_API UUI_WeaponSlot : public UUI_SlotBase
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DPS;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Level;

	UPROPERTY(meta = (BindWidget))
	UImage* BulletType_Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierBar;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_TierGlow;

	void UpdateInfo(FItemInfo_& Data_);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	FItemInfo_ ItemData_Num;
	FSlateBrush SlateBrush;


	//--------------------------------------------T---------------------------------------------
		
    template <typename T>
    T* FindWidgetByName(class UWidget* ParentWidget, const FName& TargetName)
    {
        if (!ParentWidget) return nullptr;

        // 위젯 이름과 타입 체크
        if (ParentWidget->GetFName() == TargetName)
        {
            if (T* TypedWidget = Cast<T>(ParentWidget))
            {
                return TypedWidget;
            }
        }

        // 자식 위젯이 있는 경우 탐색
        if (UPanelWidget* Panel = Cast<UPanelWidget>(ParentWidget))
        {
            for (int32 i = 0; i < Panel->GetChildrenCount(); ++i)
            {
                UWidget* ChildWidget = Panel->GetChildAt(i);
                if (T* FoundWidget = FindWidgetByName<T>(ChildWidget, TargetName))
                {
                    return FoundWidget;
                }
            }
        }

        return nullptr;
    }
};
