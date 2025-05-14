// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/Inventory_Component.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/BaseGameInstance.h"
#include "Data/DT_ItemInfo.h"
#include <algorithm>
#include "UI_HUDClass.h"



UInventory_Component::UInventory_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventory_Component::BeginPlay()
{
	Super::BeginPlay();

	FActivated_slot.BindUObject(this, &ThisClass::Update_Inventory);

	FirstWeaponSet();
}


void UInventory_Component::AddItemData_InArray(int32 Index)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

		if (PlayerController != nullptr)
		{
			AUI_HUDClass* HUD = Cast<AUI_HUDClass>(PlayerController->GetHUD());
			
			switch (GameInstance->GetRowNum_Data(Index).ItemTypeName)
			{
			case ItemTypeName::WEAPON:
				HUD->Item_Info_Update(ItemData_Weapon.Last(), "WBP_Weapon_Inventory", "Weapon_Inventory", "Wp_inventory_Slots");
				break;

			case ItemTypeName::ITEM_EXPERORPARTS:
				HUD->Item_Info_Update(ItemData_Parts.Last(), "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_inventory_Slots_");
				break;

			case ItemTypeName::ITEM_REACTOR:
				HUD->Item_Info_Update(ItemData_Reactor.Last(), "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Reactor_inventory_Slots");
				break;

			default:
				break;
			}
		}
	}
}


void UInventory_Component::Update_Inventory(int32 Index, FItemInfo_ Data_)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AUI_HUDClass* HUD = Cast<AUI_HUDClass>(Cast<APlayerController>(GetWorld()->GetFirstPlayerController())->GetHUD());

	ItemTypeName TypeName = ItemData[Index].ItemTypeName;

	switch (Data_.ItemTypeName)
	{
	case ItemTypeName::WEAPON:
		ChangeDataForEquip(Index, Data_);
		UpdateMainSlots(EquipWeaponData);
		HUD->Reset_RowColunm(ItemTypeName::WEAPON);
		break;


	case ItemTypeName::ITEM_EXPERORPARTS:
		ChangeDataForEquip(Index, Data_);
		UpdateMainSlots(EquipPartsData);
		HUD->Reset_RowColunm(ItemTypeName::ITEM_EXPERORPARTS);
		break;

	case ItemTypeName::ITEM_REACTOR:
		ChangeDataForEquip(Index, Data_);
		UpdateMainSlots(EquipReactorData);
		HUD->Reset_RowColunm(ItemTypeName::ITEM_REACTOR);
		break;

	case ItemTypeName::Module:
		ChangeDataForEquip(Index, Data_);
		HUD->Reset_RowColunm(ItemTypeName::Module);
		break;

	default:
		break;
	}

	UpdateInventorySlots(Data_);

}




void UInventory_Component::Additem(int32 Index)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (GameInstance)	
	{
		ItemData.Add(GameInstance->GetRowNum_Data(Index));

		switch (ItemData.Last().ItemTypeName)
		{
		case ItemTypeName::WEAPON:
			ItemData_Weapon.Add(ItemData.Last());
			ItemData_Weapon.Last().Damage += FMath::RoundToInt(ItemData_Weapon.Last().Damage * FMath::RandRange(-0.2f, 0.2f));
			break;

		case ItemTypeName::ITEM_REACTOR:
			ItemData_Reactor.Add(ItemData.Last());
			ItemData_Reactor.Last().Skill_Damage += FMath::RoundToInt(ItemData_Reactor.Last().Skill_Damage * FMath::RandRange(-0.2f, 0.2f));
			break;

		case ItemTypeName::ITEM_EXPERORPARTS:
			ItemData_Parts.Add(ItemData.Last());

			if (ItemData_Parts.Last().Max_Hp != 0)
			{
				ItemData_Parts.Last().Max_Hp += FMath::RoundToInt(ItemData_Parts.Last().Max_Hp * FMath::RandRange(-0.2f, 0.2f));
				break;
			}
			else if (ItemData_Parts.Last().Max_Shield != 0)
			{
				ItemData_Parts.Last().Max_Shield += FMath::RoundToInt(ItemData_Parts.Last().Max_Shield * FMath::RandRange(-0.2f, 0.2f));
				break;
			}
			else if (ItemData_Parts.Last().Defence != 0)
			{
				ItemData_Parts.Last().Defence += FMath::RoundToInt(ItemData_Parts.Last().Defence * FMath::RandRange(-0.2f, 0.2f));
				break;
			}
		}
	}
}



void UInventory_Component::FirstWeaponSet()
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	EquipWeaponData.Add(GameInstance->GetRowNum_Data(1));
	EquipWeaponData.Add(GameInstance->GetRowNum_Data(3));

	EquipReactorData.Add(GameInstance->GetRowNum_Data(5));

	EquipPartsData.Add(GameInstance->GetRowNum_Data(8));
	EquipPartsData.Add(GameInstance->GetRowNum_Data(10));
	EquipPartsData.Add(GameInstance->GetRowNum_Data(12));
	EquipPartsData.Add(GameInstance->GetRowNum_Data(14));

	UpdateMainSlots(EquipWeaponData);
	UpdateMainSlots(EquipReactorData);
	UpdateMainSlots(EquipPartsData);
}




void UInventory_Component::ChangeDataForEquip(int32 Index, FItemInfo_ Data_)
{
	switch (Data_.ItemType)
	{
	case ItemType::WEAPON_AR:
		std::swap(ItemData_Weapon[Index], EquipWeaponData[0]);
		break;

	case ItemType::WEAPON_DMR:
		std::swap(ItemData_Weapon[Index], EquipWeaponData[1]);
		break;

	case ItemType::ITEM_REACTOR:
		std::swap(ItemData_Reactor[Index], EquipReactorData[0]);
		break;

	case ItemType::ITEM_EXPERORPARTS_1:
		std::swap(ItemData_Parts[Index], EquipPartsData[0]);
		break;

	case ItemType::ITEM_EXPERORPARTS_2:
		std::swap(ItemData_Parts[Index], EquipPartsData[1]);
		break;

	case ItemType::ITEM_EXPERORPARTS_3:
		std::swap(ItemData_Parts[Index], EquipPartsData[2]);
		break;

	case ItemType::ITEM_EXPERORPARTS_4:
		std::swap(ItemData_Parts[Index], EquipPartsData[3]);
		break;
	default:
		break;
	}
}

void UInventory_Component::UpdateInventorySlots(FItemInfo_ Data_)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AUI_HUDClass* HUD = Cast<AUI_HUDClass>(Cast<APlayerController>(GetWorld()->GetFirstPlayerController())->GetHUD());

		switch (Data_.ItemTypeName)
		{
		case ItemTypeName::WEAPON:
			for (int i = 0; i < ItemData_Weapon.Num(); i++)
			{
				HUD->Item_Info_Update(ItemData_Weapon[i], "WBP_Weapon_Inventory", "Weapon_Inventory", "Wp_inventory_Slots");
			}
			break;

		case ItemTypeName::ITEM_EXPERORPARTS:
			for (int i = 0; i < ItemData_Parts.Num(); i++)
			{
				HUD->Item_Info_Update(ItemData_Parts[i], "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Parts_inventory_Slots_");
			}
			break;

		case ItemTypeName::ITEM_REACTOR:
			for (int i = 0; i < ItemData_Reactor.Num(); i++)
			{
				HUD->Item_Info_Update(ItemData_Reactor[i], "WBP_Reactor_Parts_Inventory", "Module_Parts_Inventory", "Reactor_inventory_Slots");
			}
			break;
		}
	
}

void UInventory_Component::UpdateMainSlots(TArray<FItemInfo_> Data)
{
	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AUI_HUDClass* HUD = Cast<AUI_HUDClass>(Cast<APlayerController>(GetWorld()->GetFirstPlayerController())->GetHUD());

	int32 SetItemNum = 0;

	for (int i = 0; i < Data.Num(); i++)
	{
		if (Data[i].ID == 10001)
		{
			SetItemNum++;
			GameInstance->SetSetItemNum(SetItemNum);
		}
	}

	GameInstance->SetSetItemData(EquipPartsData);

	for (int i = 0; i < Data.Num(); i++)
	{
		HUD->Main_Slot_Update(Data[i]);
	}

}



//--------------------------------------------------------------------
FItemInfo_ UInventory_Component::GetEquip_AR() const
{
	return EquipWeaponData[0];
}

void UInventory_Component::SetEquip_AR(FItemInfo_& AR_Data)
{
	EquipWeaponData[0] = AR_Data;
}
//--------------------------------------------------------------------
// 
//--------------------------------------------------------------------
FItemInfo_ UInventory_Component::GetEquip_DMR() const
{
	return EquipWeaponData[1];
}

void UInventory_Component::SetEquip_DMR(FItemInfo_& DMR_Data)
{
	EquipWeaponData[1] = DMR_Data;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
int32 UInventory_Component::GetCurrent_Bullet_AR() const
{
	return EquipWeaponData[0].Bullet_Capacity;
}

int32 UInventory_Component::GetMax_Bullet_AR() const
{
	return EquipWeaponData[0].Max_Bullet_Capacity;
}
void UInventory_Component::SetMax_bullet_AR(int32 Capacity)
{
	if (EquipWeaponData[0].Max_Bullet_Capacity > 275 && EquipWeaponData[0].Max_Bullet_Capacity < 300)
	{
		EquipWeaponData[0].Max_Bullet_Capacity = 300;
	}
	else if (EquipWeaponData[0].Max_Bullet_Capacity >= 0 && EquipWeaponData[0].Max_Bullet_Capacity < 275)
	{
		EquipWeaponData[0].Max_Bullet_Capacity += Capacity;
	}
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
int32 UInventory_Component::GetCurrent_Bullet_DMR() const
{
	return EquipWeaponData[1].Bullet_Capacity;
}

int32 UInventory_Component::GetMax_Bullet_DMR() const
{
	return EquipWeaponData[1].Max_Bullet_Capacity;
}

void UInventory_Component::SetMax_bullet_DMR(int32 Capacity)
{
	if (EquipWeaponData[1].Max_Bullet_Capacity > 72 && EquipWeaponData[1].Max_Bullet_Capacity < 90)
	{
		EquipWeaponData[1].Max_Bullet_Capacity = 90;
	}
	else if (EquipWeaponData[1].Max_Bullet_Capacity >= 0 && EquipWeaponData[1].Max_Bullet_Capacity < 72)
	{
		EquipWeaponData[1].Max_Bullet_Capacity += Capacity;
	}
}
//--------------------------------------------------------------------



float UInventory_Component::GetEquipWeapon_Damage() const
{
	return EquipWeaponData[0].Damage + EquipWeaponData[1].Damage;
}

FPartsInfo UInventory_Component::GetEquipParts_Data() const
{

	FPartsInfo Partsinfo;
	
	for (int i = 0; i < EquipPartsData.Num(); i++)
	{
		if (EquipPartsData[i].Max_Hp != 0)
		{
			Partsinfo.MaxHp += EquipPartsData[i].Max_Hp;
		}
		else if (EquipPartsData[i].Max_Shield != 0)
		{
			Partsinfo.MaxShild += EquipPartsData[i].Max_Shield;
		}
		else if (EquipPartsData[i].Defence != 0)
		{
			Partsinfo.Defence += EquipPartsData[i].Defence;
		}
	}
	return Partsinfo;
}

float UInventory_Component::GetEquipReactor_SkillDamage() const
{
	return EquipReactorData[0].Skill_Damage;
}

FPartsInfo::FPartsInfo()
{
	MaxHp = MaxShild = Defence = 0;
}
