// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Drop_Item/ItemBase.h"
#include "Drop_Item_InvenItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ADrop_Item_InvenItem : public AItemBase
{
	GENERATED_BODY()

public:
	ADrop_Item_InvenItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 ItemRow_index;

	int32 Item_Type;

public:
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void SetItemMesh(int32 Type) override;
	
};
