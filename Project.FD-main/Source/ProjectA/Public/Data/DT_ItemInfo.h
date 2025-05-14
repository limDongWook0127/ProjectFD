// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DT_ItemInfo.generated.h"

UENUM(BlueprintType)
enum class ItemTypeName : uint8
{
	WEAPON,
	ITEM_REACTOR,
	ITEM_EXPERORPARTS,
	Module,
};

UENUM(BlueprintType)
enum class ItemType : uint8
{
	WEAPON_AR,
	WEAPON_DMR,
	ITEM_REACTOR,
	ITEM_EXPERORPARTS_1,
	ITEM_EXPERORPARTS_2,
	ITEM_EXPERORPARTS_3,
	ITEM_EXPERORPARTS_4,
	Module_LV_1,
	Module_LV_2,
};

USTRUCT(BlueprintType)
struct FRankColor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float R;

	UPROPERTY(EditAnywhere)
	float G;

	UPROPERTY(EditAnywhere)
	float B;
};

USTRUCT(BlueprintType)
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere)
	UTexture2D* BulletIcon;

	UPROPERTY(EditAnywhere)
	UTexture2D* Socket_Type;

	UPROPERTY(EditAnywhere)
	UTexture2D* TierBar;

	UPROPERTY(EditAnywhere)
	UTexture2D* Module_BGImage;

	UPROPERTY(EditAnywhere)
	FRankColor Rank_Color;

	UPROPERTY(EditAnywhere)
	FString ItemType_Name;

	UPROPERTY(EditAnywhere)
	FString Rank_Name;

	UPROPERTY(EditAnywhere)
	FString Bullet_Type_Name;

	UPROPERTY(EditAnywhere)
	FString Item_SetName;

};


USTRUCT(Atomic, BlueprintType)
struct FItemInfo_ : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �ѱ� / ������ / �����ǰ / ���
	ItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // Ÿ�Ժ� �ѹ�
	int32 Item_Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �̸�
	FString Item_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �ѱ� ���ݷ� / ��� -> �ѱ� ���ݷ� ������
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ġ��Ÿ Ȯ��
	float Critical_Percent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ġ��Ÿ ����
	float Critical_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ���� ���� ����
	float Weekness_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ��ź��
	int32 Bullet_Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �ִ� ź���
	int32 Max_Bullet_Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �ִ� ü��
	float Max_Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �ִ� ���差
	float Max_Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ����
	float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ��ų ���ݷ�
	float Skill_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ���� ���ݷ�
	float Secondary_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // �߻�ӵ�
	float AttackSpeed;

	int32 DPS(); // �ѱ� DPS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo") // ������ �̹���
	FItemAssetData AssetData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	ItemTypeName ItemTypeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	int32 ID;

};
/**
 * 
 */
UCLASS()
class PROJECTA_API UDT_ItemInfo : public UDataTable
{
	GENERATED_BODY()
	
};
