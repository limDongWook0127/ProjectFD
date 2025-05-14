// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Drop_Item/DropItem_Heal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ADropItem_Heal::ADropItem_Heal()
{

}

void ADropItem_Heal::BeginPlay()
{
	Super::BeginPlay();

	Item_Type = FMath::RandRange(1, 2);
	SetItemMesh(Item_Type);

	ItemCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

void ADropItem_Heal::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*HealCharacter();
	Destroy();*/
	// Item Type�� ����
	// TODO:: �÷��̾� current ü�� ���
	// TODO:: �÷��̾� current MP ���
}

void ADropItem_Heal::SetItemMesh(int32 Type)
{
	UStaticMesh* LoadedMesh = nullptr; // �ε�� �޽��� ������ ����

	switch (Type)
	{
	case 1:
		LoadedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Textures/Item_Mesh/HP.HP")));

		if (LoadedMesh)
		{
			ItemMesh->SetStaticMesh(LoadedMesh);
		}
		break;

	case 2:
		LoadedMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Assets/Textures/Item_Mesh/MP.MP")));

		if (LoadedMesh)
		{
			ItemMesh->SetStaticMesh(LoadedMesh);
		}
		break;

	default:
		break;
	}
}
