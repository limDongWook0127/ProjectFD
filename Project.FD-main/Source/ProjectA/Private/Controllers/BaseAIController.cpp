// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BaseAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BaseDebugHelper.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	// SetDefaultSubobjectClass로 CrowdFloowingComponent 사용
	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		//Debug::Print(TEXT("CrowdFollowingComponent Vaild"), FColor::Green);
	}


	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));

	// 적 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;

	// 아군 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;

	// 중립 감지
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	// 시야 설정
	AISenseConfig_Sight->SightRadius = 1200.f;

	// 대상을 잃는 시야 범위 설정
	AISenseConfig_Sight->LoseSightRadius = 0.f;

	// 주변 시야각
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;



	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// 센서 설정
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ABaseAIController::OnEnemyPerceptionUpdate);

	SetGenericTeamId(FGenericTeamId(1));
	
}

void ABaseAIController::OnEnemyPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	// Update
	//if (Stimulus.WasSuccessfullySensed() && Actor)
	//{
	//	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	//	{
	//		BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
	//	}
	//}

	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName(TEXT("TargetActor")), Actor);
			}
		}
	}
}

ETeamAttitude::Type ABaseAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnCheck->GetController());

	// EQS TEST Pawn을 제외시키고 HeroCharacter만 체크하기 위한 조건 (HeroCharacter GenericTeamId = 0)
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		// TeamID가 다르면 적으로 변경
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdFollowingComponent->SetCrowdSimulationState(bDetourCrowdAvoidence ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidenceQuality)
		{
		case 1:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;

		}

		// 회피 그룹 설정
		CrowdFollowingComponent->SetAvoidanceGroup(1);
		// 회피 그룹이 설정되면 회피해
		CrowdFollowingComponent->SetGroupsToAvoid(1);
		//
		CrowdFollowingComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
	UE_LOG(LogTemp, Warning, TEXT("AI Controller Team ID: %d"), GetGenericTeamId().GetId());
}

