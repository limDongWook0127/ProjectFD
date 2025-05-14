// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HUDClass.h"
#include "Widgets/UI_Main_Inventory.h"


void AUI_HUDClass::BeginPlay()
{
	Inventory = CreateWidget<UUI_Main_Inventory>(GetWorld()->GetFirstPlayerController(), BP_InventoryWidget);
	Inventory->AddToViewport(5);
}

void AUI_HUDClass::Item_Info_Update(FItemInfo_ Data, FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name)
{
	if (Inventory)
	{
		Inventory->WidgetCastTest(Data, WidgetBP_Name, Widget_CanvasName, WidgetInventorySlot_Name);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Inventory Faild"));

}

void AUI_HUDClass::Main_Slot_Update(FItemInfo_ Data)
{
	if (Inventory)
	{
		Inventory->Update_Weapon_MainSlot(Data);
	}
}

void AUI_HUDClass::Reset_RowColunm(ItemTypeName TypeName)
{
	if (Inventory)
	{
		switch (TypeName)
		{
		case ItemTypeName::WEAPON:
			Inventory->Reset_WP_RowColunm();
			Inventory->Reset_Inventory("WBP_Weapon_Inventory", "Weapon_Inventory", "Wp_inventory_Slots");
			break;

		case ItemTypeName::Module:
			Inventory->Reset_Module_RowColunm();
			break;

		case ItemTypeName::ITEM_EXPERORPARTS:
			Inventory->Reset_Parts_RowColunm();
			Inventory->Reset_Inventory("WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_inventory_Slots_");
			break;

		case ItemTypeName::ITEM_REACTOR:
			Inventory->Reset_Reactor_RowColunm();
			Inventory->Reset_Inventory("WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Reactor_inventory_Slots");
			break;

		default:
			break;
		}

	}
}

