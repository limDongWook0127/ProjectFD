// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/BaseGameInstance.h"
#include "Components/Inventory/Inventory_Component.h"
#include "Kismet/GameplayStatics.h"
#include "Data/DT_ItemInfo.h"

UBaseGameInstance::UBaseGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemInfo(TEXT("/Game/_BP/DataTable/DT_ItemInfo.DT_ItemInfo"));

	if (DT_ItemInfo.Succeeded())
	{
		DataTable = DT_ItemInfo.Object;
	}
}

FItemInfo_ UBaseGameInstance::GetRowNum_Data(int32 Index)
{	

	int RowNum = DataTable->GetRowNames().Num();	
	if (Index <= RowNum)
	{
		FItemInfo_ ItemInfo = *DataTable->FindRow<FItemInfo_>(FName(*FString::FromInt(Index)), TEXT(""));

		return ItemInfo;
	}
	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("--------------No ItemData-------------------"));
		
		FItemInfo_ ItemInfo;

		return ItemInfo;
	}

}

void UBaseGameInstance::ChangeWeaponDelegate(int32 Index, FItemInfo_ Data_)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();

		UInventory_Component* InventoryComponent = PlayerPawn->FindComponentByClass<UInventory_Component>();
		
		if (InventoryComponent)
		{
			InventoryComponent->FActivated_slot.ExecuteIfBound(Index, Data_);
		}

	}
	
}

void UBaseGameInstance::SetSetItemNum(int32 SetItem_)
{
	SetItemNum_ = SetItem_;
}

void UBaseGameInstance::SetSetItemData(TArray<FItemInfo_> ItemData_)
{
	ItemData = ItemData_;
}
