// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Drop_Item/Drop_Item_InvenItem.h"
#include "Components/Inventory/Inventory_Component.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ADrop_Item_InvenItem::ADrop_Item_InvenItem()
{

}


void ADrop_Item_InvenItem::BeginPlay()
{
	Super::BeginPlay();

	Item_Type = FMath::RandRange(1, 2);
	SetItemMesh(Item_Type);

	ItemCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
}


void ADrop_Item_InvenItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UInventory_Component* Inventory = OtherActor->FindComponentByClass<UInventory_Component>())
	{
		if (Inventory)
		{
			Inventory->Additem(ItemRow_index);
			Inventory->AddItemData_InArray(ItemRow_index);
		}
		Destroy();
	}
}

void ADrop_Item_InvenItem::SetItemMesh(int32 Type)
{
	UStaticMesh* LoadedMesh = nullptr; // 로드된 메쉬를 저장할 변수

	switch (Type)
	{
	case 1:
		ItemRow_index = FMath::RandRange(1, 4);
		LoadedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Textures/Item_Mesh/Weapon.Weapon")));

		if (LoadedMesh)
		{
			ItemMesh->SetStaticMesh(LoadedMesh);
		}
		break;

	case 2:
		ItemRow_index = FMath::RandRange(5, 15);
		LoadedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Textures/Item_Mesh/Parts.Parts")));

		if (LoadedMesh)
		{
			ItemMesh->SetStaticMesh(LoadedMesh);
		}
		break;

	default:
		break;
	}
}
