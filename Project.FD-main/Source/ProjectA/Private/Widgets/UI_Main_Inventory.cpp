// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/UI_Main_Inventory.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/PanelWidget.h"

#include "Widgets/Slot/UI_WeaponSlot.h"
#include "Widgets/Slot/UI_Parts_Slot.h"
#include "Widgets/Slot/UI_Reactor_Slot.h"

#include "Widgets/Page_Base.h"
#include "Data/DT_ItemInfo.h"

#include "BaseDebugHelper.h"


UUI_Main_Inventory::UUI_Main_Inventory()
{
	Wp_Row = Wp_Column = Module_Row = Module_Column = Parts_Row = Parts_Column = Reactor_Row = Reactor_Column = 0;
}

//void UUI_Main_Inventory::NativeConstruct()
//{
//}

UWidget* UUI_Main_Inventory::TestFuntion(const FName& WidgetName)
{
	Inventory = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("Inventory")));
	
	if (Inventory)
	{
		for (int32 i = 0; i < Inventory->GetChildrenCount(); i++)
		{
			UWidget* ChildWidget = Inventory->GetChildAt(i);

			if (ChildWidget->GetFName() == WidgetName)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *ChildWidget->GetFName().ToString());
				return ChildWidget;
			}
		}
	}
	return nullptr;
}

void UUI_Main_Inventory::WidgetCastTest(struct FItemInfo_ Data_, FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name)
{

	UPage_Base* page = FindWidgetByName<UPage_Base>(Inventory, FName(WidgetBP_Name));   // WidgetModule_Name 로 변경

	if (page != nullptr)
	{
		UUniformGridPanel* Wp_Slots = FindWidgetByName<UUniformGridPanel>(page->GetWidgetFromName(Widget_CanvasName), FName(WidgetInventorySlot_Name));  // inventory :: 캔버스 패널 / slot 인벤토리 슬롯 - 이름 통일화

		if (Wp_Slots != nullptr)
		{
			UScaleBox* ScaleBox = NewObject<UScaleBox>(Wp_Slots);		// 스케일 박스 생성
			ScaleBox->SetStretch(EStretch::UserSpecified);			// 스케일 박스 상대적 크기 설정
			ScaleBox->SetUserSpecifiedScale(0.1f);						// 크기 조정

			if (ScaleBox)
			{

				switch (Data_.ItemTypeName)
				{
				case ItemTypeName::WEAPON:
					Slots = TEST_2(WeaponSlotWidgetClass);
					WeaponSlotWidget = Cast<UUI_WeaponSlot>(Slots);

					if (WeaponSlotWidget)
					{
						WeaponSlotWidget->UpdateInfo(Data_);
						// 자식 위젯을 ScaleBox에 추가
						ScaleBox->AddChild(WeaponSlotWidget);									// TODO:: weaponSlot / moduleSlot / PartsSlot / ReactorSlot 을 가져와서 scalebox 안에 추가

						Wp_Slots->AddChildToUniformGrid(ScaleBox, Wp_Row, Wp_Column);// 유니폼 그리드 패널에 배치
						UpdateRow_Column(Wp_Row, Wp_Column);
					
					}
					else
						UE_LOG(LogTemp, Warning, TEXT("sssssssssssss-1"));

					break;
					//---------------------------------------------------------------------

				case ItemTypeName::ITEM_EXPERORPARTS:
					Slots = TEST_2(PartsSlotWidgetClass);
					PartsSlotWidget = Cast<UUI_Parts_Slot>(Slots);

					if (PartsSlotWidget)
					{
						PartsSlotWidget->UpdateInfo(Data_);
						// 자식 위젯을 ScaleBox에 추가
						ScaleBox->AddChild(PartsSlotWidget);									// TODO:: weaponSlot / moduleSlot / PartsSlot / ReactorSlot 을 가져와서 scalebox 안에 추가

						Wp_Slots->AddChildToUniformGrid(ScaleBox, Parts_Row, Parts_Column);		// 유니폼 그리드 패널에 배치
						UpdateRow_Column(Parts_Row, Parts_Column);

					}
					else
						UE_LOG(LogTemp, Warning, TEXT("sssssssssssss-1"));
					break;

					//---------------------------------------------------------------------

				case ItemTypeName::ITEM_REACTOR:
					Slots = TEST_2(ReactorSlotWidgetClass);
					ReactorSlotWidget = Cast<UUI_Reactor_Slot>(Slots);

					if (ReactorSlotWidget)
					{
						ReactorSlotWidget->UpdateInfo(Data_);
						// 자식 위젯을 ScaleBox에 추가
						ScaleBox->AddChild(ReactorSlotWidget);									// TODO:: weaponSlot / moduleSlot / PartsSlot / ReactorSlot 을 가져와서 scalebox 안에 추가

						Wp_Slots->AddChildToUniformGrid(ScaleBox, Reactor_Row, Reactor_Column);					// 유니폼 그리드 패널에 배치
						UpdateRow_Column(Reactor_Row, Reactor_Column);

						UE_LOG(LogTemp, Warning, TEXT("ddddddddddddddd"));
					}
					else
						UE_LOG(LogTemp, Warning, TEXT("sssssssssssss-1"));
					break;
				}
			}
		}
	}
}


UUserWidget* UUI_Main_Inventory::TEST_2(TSubclassOf<UUserWidget> slotClass)
{
	if (slotClass)
	{
		return CreateWidget<UUserWidget>(GetWorld(), slotClass);
	}
	return nullptr;
}


void UUI_Main_Inventory::UpdateRow_Column(int32& _Row, int32& _Column)	// 
{
	if (_Column >= 3)
	{
		_Row++;
		_Column = 0;
	}
	else
		_Column++;
}

void UUI_Main_Inventory::Reset_WP_RowColunm()
{
	Wp_Row = Wp_Column =  0;
}

void UUI_Main_Inventory::Reset_Parts_RowColunm()
{
	Parts_Row = Parts_Column = 0;
}

void UUI_Main_Inventory::Reset_Module_RowColunm()
{
	Module_Row = Module_Column = 0;
}

void UUI_Main_Inventory::Reset_Reactor_RowColunm()
{
	Reactor_Row = Reactor_Column = 0;
}


void UUI_Main_Inventory::Reset_Inventory(FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name)
{
	UPage_Base* page = FindWidgetByName<UPage_Base>(Inventory, FName(WidgetBP_Name));   // WidgetModule_Name 로 변경

	if (page != nullptr)
	{
		UUniformGridPanel* Wp_Slots = FindWidgetByName<UUniformGridPanel>(page->GetWidgetFromName(Widget_CanvasName), FName(WidgetInventorySlot_Name));

		if (Wp_Slots)
		{
			Wp_Slots->ClearChildren();
		}
	}

}

void UUI_Main_Inventory::Update_Weapon_MainSlot(FItemInfo_ Data_)
{
	
		switch (Data_.ItemType)
		{
		case ItemType::WEAPON_AR:
			CheckMainSlotAndUpdate(Data_, "WBP_Weapon_Inventory", "Weapon_Inventory", "Weapon_MainSlot_1");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Weapon_MainSlot_1");
			break;

		case ItemType::WEAPON_DMR:
			CheckMainSlotAndUpdate(Data_, "WBP_Weapon_Inventory", "Weapon_Inventory", "Weapon_MainSlot_2");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Weapon_MainSlot_2");
			break;

		case ItemType::ITEM_REACTOR:
			CheckMainSlotAndUpdate(Data_, "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Reactor_MainSlot");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Reactor_MainSlot");
			break;

		case ItemType::ITEM_EXPERORPARTS_1:
			CheckMainSlotAndUpdate(Data_, "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_MainSlot_1");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Parts_MainSlot_1");
			break;

		case ItemType::ITEM_EXPERORPARTS_2:
			CheckMainSlotAndUpdate(Data_, "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_MainSlot_2");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Parts_MainSlot_2");
			break;

		case ItemType::ITEM_EXPERORPARTS_3:
			CheckMainSlotAndUpdate(Data_, "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_MainSlot_3");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Parts_MainSlot_3");
			break;

		case ItemType::ITEM_EXPERORPARTS_4:
			CheckMainSlotAndUpdate(Data_, "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_MainSlot_4");
			CheckMainSlotAndUpdate(Data_, "WBP_Main_Inventory", "Main_Inventory", "Parts_MainSlot_4");
			break;
		default:
			break;
		}

}

void UUI_Main_Inventory::CheckMainSlotAndUpdate(FItemInfo_ Data_, FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name)
{
	UPage_Base* page = FindWidgetByName<UPage_Base>(Inventory, FName(WidgetBP_Name));
	


	switch (Data_.ItemTypeName)
	{
	case ItemTypeName::WEAPON:

		if (page)
		{
			UUI_WeaponSlot* MainSlot = FindWidgetByName<UUI_WeaponSlot>(page->GetWidgetFromName(Widget_CanvasName), FName(WidgetInventorySlot_Name));

			if (MainSlot)
			{
				WeaponMain_SlotWidget = Cast<UUI_WeaponSlot>(MainSlot);

				if (WeaponMain_SlotWidget)
				{
					WeaponMain_SlotWidget->UpdateInfo(Data_);
					break;
				}
			}
		}
		break;

	case ItemTypeName::ITEM_REACTOR:

		if (page)
		{
			UUI_Reactor_Slot* MainSlot = FindWidgetByName<UUI_Reactor_Slot>(page->GetWidgetFromName(Widget_CanvasName), FName(WidgetInventorySlot_Name));

			if (MainSlot)
			{
				ReactorMain_SlotWidget = Cast<UUI_Reactor_Slot>(MainSlot);

				if (ReactorMain_SlotWidget)
				{
					ReactorMain_SlotWidget->UpdateInfo(Data_);
					break;
				}
			}
		}
		break;

	case ItemTypeName::ITEM_EXPERORPARTS:
		if (page)
		{
			UUI_Parts_Slot* MainSlot = FindWidgetByName<UUI_Parts_Slot>(page->GetWidgetFromName(Widget_CanvasName), FName(WidgetInventorySlot_Name));

			if (MainSlot)
			{
				PartsMain_SlotWidget = Cast<UUI_Parts_Slot>(MainSlot);

				if (PartsMain_SlotWidget)
				{
					PartsMain_SlotWidget->UpdateInfo(Data_);
					break;
				}
			}
		}
		break;

	default:
		break;
	}

}




