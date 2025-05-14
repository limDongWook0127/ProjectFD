// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTD_RandomLoop.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BehaviorTree/Composites/BTComposite_SimpleParallel.h"

UBTD_RandomLoop::UBTD_RandomLoop()
{
	NodeName = TEXT("RandomLoopCustom");

}

void UBTD_RandomLoop::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	Super::InitializeMemory(OwnerComp, NodeMemory, InitType);

	LoopCount = FMath::RandRange(MinLoopCount, MaxLoopCount);

	UE_LOG(LogTemp, Warning, TEXT("Rand num : %d"), LoopCount);
}

void UBTD_RandomLoop::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	//Super::OnNodeActivation(SearchData);

	Count++;

	if (Count == LoopCount)
	{
		Count = 0;
		
		LoopCount = FMath::RandRange(MinLoopCount, MaxLoopCount);
		UE_LOG(LogTemp, Warning, TEXT("Rand num : %d"), LoopCount);
	}

	FBTLoopDecoratorMemory* DecoratorMemory = GetNodeMemory<FBTLoopDecoratorMemory>(SearchData);
	FBTCompositeMemory* ParentMemory = GetParentNode()->GetNodeMemory<FBTCompositeMemory>(SearchData);
	const bool bIsSpecialNode = GetParentNode()->IsA(UBTComposite_SimpleParallel::StaticClass());

	if ((bIsSpecialNode && ParentMemory->CurrentChild == BTSpecialChild::NotInitialized) ||
		(!bIsSpecialNode && ParentMemory->CurrentChild != ChildIndex))
	{
		// initialize counter if it's first activation
		DecoratorMemory->RemainingExecutions = IntCastChecked<uint8>(LoopCount);
		DecoratorMemory->TimeStarted = GetWorld()->GetTimeSeconds();
	}

	bool bShouldLoop = false;
	if (bInfiniteLoop)
	{
		// protect from truly infinite loop within single search
		if (SearchData.SearchId != DecoratorMemory->SearchId)
		{
			if ((InfiniteLoopTimeoutTime < 0.f) || ((DecoratorMemory->TimeStarted + InfiniteLoopTimeoutTime) > GetWorld()->GetTimeSeconds()))
			{
				bShouldLoop = true;
			}
		}

		DecoratorMemory->SearchId = SearchData.SearchId;
	}
	else
	{
		if (DecoratorMemory->RemainingExecutions > 0)
		{
			DecoratorMemory->RemainingExecutions--;
		}
		bShouldLoop = DecoratorMemory->RemainingExecutions > 0;
	}


	// set child selection overrides
	if (bShouldLoop)
	{
		GetParentNode()->SetChildOverride(SearchData, ChildIndex);
	}
}

void UBTD_RandomLoop::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	LoopCount = 0;
	Super::CleanupMemory(OwnerComp, NodeMemory, CleanupType);
}


