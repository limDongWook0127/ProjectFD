// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UI_Inventory_Base.h"
#include "Components/PanelWidget.h"
#include "UI_Main_Inventory.generated.h"

class UCanvasPanel;
class UUniformGridPanel;
class UTextBlock;
class UUI_WeaponSlot;
class UUI_Parts_Slot;
class UUI_Reactor_Slot;
/**
 * 
 */
UCLASS()
class PROJECTA_API UUI_Main_Inventory : public UUI_Inventory_Base
{
	GENERATED_BODY()

private:
	UWidget* MainWidget;

    UUI_WeaponSlot* WeaponSlot;

    int32 Wp_Row;
    int32 Wp_Column;

    int32 Module_Row;
    int32 Module_Column;

    int32 Parts_Row;
    int32 Parts_Column;

    int32 Reactor_Row;
    int32 Reactor_Column;

    int32 Set_Item_Num;

    void UpdateRow_Column(int32& _Row, int32& _Column);

public:

	UUI_Main_Inventory();

	//virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* Inventory;

	UPROPERTY(BlueprintReadWrite)
	UUniformGridPanel* Weapon_GridPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> WeaponSlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ModuleSlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ReactorSlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PartsSlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> WeaponMain_SlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PartsMain_SlotWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ReactorMain_SlotWidgetclass;

    UUI_WeaponSlot* WeaponSlotWidget;
    UUI_Parts_Slot* PartsSlotWidget;
    UUI_Reactor_Slot* ReactorSlotWidget;
    UUserWidget* Slots;

    UUI_WeaponSlot* WeaponMain_SlotWidget;
    UUI_Parts_Slot* PartsMain_SlotWidget;
    UUI_Reactor_Slot* ReactorMain_SlotWidget;


	UWidget* TestFuntion(const FName& WidgetName);

	void WidgetCastTest(struct FItemInfo_ Data_, FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name);

    UUserWidget* TEST_2(TSubclassOf<UUserWidget> slotClass);


    void Reset_WP_RowColunm();
    void Reset_Parts_RowColunm();
    void Reset_Module_RowColunm();
    void Reset_Reactor_RowColunm();

    void Reset_Inventory(FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name);

    void Update_Weapon_MainSlot(struct FItemInfo_ Data_);

    void CheckMainSlotAndUpdate(FItemInfo_ Data_, FName WidgetBP_Name, FName Widget_CanvasName, FName WidgetInventorySlot_Name);


  //  UUserWidget* GetWeaponSlotInstance();

    //---------------------------------------------------------------------------------------

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
