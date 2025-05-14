// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroSkillBase.h"
#include "LandingSpark.generated.h"

UCLASS()
class PROJECTA_API ALandingSpark : public AHeroSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandingSpark();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 데미지 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageRadius = 300.0f;

	// 데미지 양
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 50.0f;

	// 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float Lifetime = 2.0f;


private:
	// 일정 시간 후 소멸
	void DestroyEffect();

	// 타이머 핸들
	FTimerHandle TimerHandle;
};
