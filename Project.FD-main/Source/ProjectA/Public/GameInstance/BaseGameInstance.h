// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"


struct FItemInfo_;

/**
 * 
 */

UCLASS()
class PROJECTA_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UBaseGameInstance();

private:
	class UDataTable* DataTable;  // ������ ������ ���̺�

	int32 SetItemNum_;
	TArray<FItemInfo_> ItemData;

public:

	int GetDataTableRowNum() { return DataTable->GetRowNames().Num(); } // �ִ� rownumber ��ȯ
	FItemInfo_ GetRowNum_Data(int32 Index); // index�� data �� ����

	void ChangeWeaponDelegate(int32 Index, FItemInfo_ Data_);

	int32 GetSetItemNum() const { return SetItemNum_; }
	void SetSetItemNum(int32 SetItem_);

	TArray<FItemInfo_> GetSetItemData() const { return ItemData; }
	void SetSetItemData(TArray<FItemInfo_> ItemData_);





	
};
