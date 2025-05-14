// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Data/DT_ItemInfo.h"
#include "UI_HUDClass.generated.h"

class UUI_Main_Inventory;
/**
 * 
 */
UCLASS()
class PROJECTA_API AUI_HUDClass : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UUI_Main_Inventory* Inventory;

	
public:
	virtual void BeginPlay() override;

	void Item_Info_Update(struct FItemInfo_ Data, FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name);

	void Main_Slot_Update(struct FItemInfo_ Data);

	void Reset_RowColunm(ItemTypeName TypeName);

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUI_Main_Inventory> BP_InventoryWidget;


	UFUNCTION(BlueprintCallable)
	UUI_Main_Inventory* GetBP_Inventory() { return Inventory; }

	
};
