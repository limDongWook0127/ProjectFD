// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory_Component.generated.h"



USTRUCT(BlueprintType)
struct FPartsInfo
{
	GENERATED_BODY()


public:
	FPartsInfo();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaxShild;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Defence;
};


class ADrop_Item_Base;
struct FItemInfo_;

DECLARE_DELEGATE_TwoParams(Activated_slot, int32, FItemInfo_);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UInventory_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory_Component();

	void AddItemData_InArray(int32 Index);

	void Update_Inventory(int32 Index, FItemInfo_ Data_);

	void Additem(int32 Index);

	Activated_slot FActivated_slot;

	void FirstWeaponSet();

	void ChangeDataForEquip(int32 Index, FItemInfo_ Data_);

	void UpdateInventorySlots(FItemInfo_ Data_);

	void UpdateMainSlots(TArray<FItemInfo_> Data);

	UFUNCTION(BlueprintCallable, Category = "WeaponData")
	FItemInfo_ GetEquip_AR() const;
	void SetEquip_AR(FItemInfo_& AR_Data);

	UFUNCTION(BlueprintCallable, Category = "WeaponData")
	FItemInfo_ GetEquip_DMR() const;
	void SetEquip_DMR(FItemInfo_& DMR_Data);


	UFUNCTION(BlueprintCallable, Category = "Bullet")
	int32 GetCurrent_Bullet_AR() const;

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	int32 GetMax_Bullet_AR() const;

	void SetMax_bullet_AR(int32 Capacity);

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	int32 GetCurrent_Bullet_DMR() const;

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	int32 GetMax_Bullet_DMR() const;

	void SetMax_bullet_DMR(int32 Capacity);

	UFUNCTION(BlueprintCallable, Category = "EquipItem")
	float GetEquipWeapon_Damage() const;

	UFUNCTION(BlueprintCallable, Category = "EquipItem")
	FPartsInfo GetEquipParts_Data() const;	

	UFUNCTION(BlueprintCallable, Category = "EquipItem")
	float GetEquipReactor_SkillDamage() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	ADrop_Item_Base* Dropitem;

	TArray<FItemInfo_> ItemData;

	TArray<FItemInfo_> ItemData_Weapon;

	TArray<FItemInfo_> ItemData_Reactor;

	TArray<FItemInfo_> ItemData_Parts;

	TArray<FItemInfo_> EquipWeaponData;

	TArray<FItemInfo_> EquipReactorData;

	TArray<FItemInfo_> EquipPartsData;

	

private:
	




		
};
