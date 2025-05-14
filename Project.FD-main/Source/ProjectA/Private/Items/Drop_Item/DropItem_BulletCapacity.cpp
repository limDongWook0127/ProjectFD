// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Drop_Item/DropItem_BulletCapacity.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/Inventory/Inventory_Component.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ADropItem_BulletCapacity::ADropItem_BulletCapacity()
{
}

void ADropItem_BulletCapacity::BeginPlay()
{
	Super::BeginPlay();

	Item_Type = FMath::RandRange(1, 2);
	SetItemMesh(Item_Type);

	ItemCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
	
}

void ADropItem_BulletCapacity::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (UInventory_Component* Inventory = OtherActor->FindComponentByClass<UInventory_Component>())
	{

		if (Inventory)
		{
			switch (Item_Type)
			{
			case 1:
				Inventory->SetMax_bullet_AR(25);
				break;

			case 2:
				Inventory->SetMax_bullet_DMR(18);
				break;

			default:
				break;
			}
		}
		Destroy();
	}
}

void ADropItem_BulletCapacity::SetItemMesh(int32 Type)
{
	UStaticMesh* LoadedMesh = nullptr; // 로드된 메쉬를 저장할 변수

	switch (Type)
	{
	case 1:
		LoadedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Textures/Item_Mesh/Bullet_General.Bullet_General")));

		if (LoadedMesh)
		{
			ItemMesh->SetStaticMesh(LoadedMesh);
		}
		break;

	case 2:
		LoadedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Textures/Item_Mesh/Bullet_Impact.Bullet_Impact")));

		if (LoadedMesh)
		{
			ItemMesh->SetStaticMesh(LoadedMesh);
		}
		break;

	default:
		break;
	}
}
