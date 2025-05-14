// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Loop.h"
#include "BTD_RandomLoop.generated.h"

class UBlackboardComponent;
/**
 * 
 */
UCLASS()
class PROJECTA_API UBTD_RandomLoop : public UBTDecorator_Loop
{
	GENERATED_BODY()
	
public:
	UBTD_RandomLoop();

	UPROPERTY(EditAnywhere, Category = "Loop Settings")
	int32 MinLoopCount = 5;
	UPROPERTY(EditAnywhere, Category = "Loop Settings")
	int32 MaxLoopCount = 7;

protected:
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;

private:
	mutable int32 LoopCount;

	int32 Count;




};
