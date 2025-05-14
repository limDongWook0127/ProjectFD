// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSkillObject/HeroSkillBase.h"
#include "SpawnSparkBall.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ASpawnSparkBall : public AHeroSkillBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASpawnSparkBall();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageRadius = 300.0f;

	// ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 50.0f;

	// ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float Lifetime = 5.0f;

	// ƽ ������ �ֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float TickTime = 1.0f;

private:
	// ���� �ð� �� �Ҹ�
	void DestroyEffect();

	// ������ �ο�
	void DamageEnemy();

	// Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
};
