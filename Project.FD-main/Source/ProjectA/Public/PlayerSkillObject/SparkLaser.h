// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSkillObject/HeroSkillBase.h"
#include "SparkLaser.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ASparkLaser : public AHeroSkillBase
{
	GENERATED_BODY()

public:
	// 데미지 양
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 50.0f;

protected:
	// 일정 시간 후 소멸
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DestroyEffect();

	// 데미지 부여
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DamageEnemy(AActor* HitActor);
};
