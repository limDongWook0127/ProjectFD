// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Inventory/BulletSystem_Component.h"
#include "Components/Inventory/Inventory_Component.h"
#include "Data/DT_ItemInfo.h"

// Sets default values for this component's properties
UBulletSystem_Component::UBulletSystem_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



bool UBulletSystem_Component::TryUseBullet_AR()
{

	FItemInfo_ Data = InventoryComponent->GetEquip_AR();

	if (Data.Bullet_Capacity > 0)
	{
		Data.Bullet_Capacity -= 1;
		InventoryComponent->SetEquip_AR(Data);

		return true;
	}
	else
		return false;

}


bool UBulletSystem_Component::TryReloadBullet_AR()
{

	FItemInfo_ Data = InventoryComponent->GetEquip_AR();

	int32 MaxCapaCity = Data.Max_Bullet_Capacity - (25 - Data.Bullet_Capacity);

	if (Data.Max_Bullet_Capacity > 0)
	{
		if (MaxCapaCity >= 0)
		{
			Data.Max_Bullet_Capacity = MaxCapaCity;
			Data.Bullet_Capacity = 25;

			InventoryComponent->SetEquip_AR(Data);
			return true;
		}
		else if (MaxCapaCity < 0)
		{
			Data.Bullet_Capacity = Data.Bullet_Capacity + Data.Max_Bullet_Capacity;
			Data.Max_Bullet_Capacity = 0;

			InventoryComponent->SetEquip_AR(Data);
			return true;
		}
		else
			return false;
	}
	else
		return false;

}




bool UBulletSystem_Component::TryUseBullet_DMR()
{

	FItemInfo_ Data = InventoryComponent->GetEquip_DMR();

	if (Data.Bullet_Capacity > 0)
	{
		Data.Bullet_Capacity -= 1;
		InventoryComponent->SetEquip_DMR(Data);

		return true;
	}
	else
		return false;
}



bool UBulletSystem_Component::TryReloadBullet_DMR()
{
	FItemInfo_ Data = InventoryComponent->GetEquip_DMR();

	int32 MaxCapaCity = Data.Max_Bullet_Capacity - (18 - Data.Bullet_Capacity);

	if (Data.Max_Bullet_Capacity > 0)
	{
		if (MaxCapaCity >= 0)
		{
			Data.Max_Bullet_Capacity = MaxCapaCity;
			Data.Bullet_Capacity = 18;

			InventoryComponent->SetEquip_DMR(Data);
			return true;
		}
		else if (MaxCapaCity < 0)
		{
			Data.Bullet_Capacity = Data.Bullet_Capacity + Data.Max_Bullet_Capacity;
			Data.Max_Bullet_Capacity = 0;

			InventoryComponent->SetEquip_DMR(Data);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}



// Called when the game starts
void UBulletSystem_Component::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetOwner();
	if (Actor != nullptr)
	{
		InventoryComponent = Cast<UInventory_Component>(Actor->FindComponentByClass<UInventory_Component>());
	}

	
}

