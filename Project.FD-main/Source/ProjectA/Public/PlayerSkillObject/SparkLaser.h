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
	// ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 50.0f;

protected:
	// ���� �ð� �� �Ҹ�
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DestroyEffect();

	// ������ �ο�
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DamageEnemy(AActor* HitActor);
};
