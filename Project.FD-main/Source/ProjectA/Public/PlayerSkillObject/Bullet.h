// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSkillObject/HeroSkillBase.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ABullet : public AHeroSkillBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABullet();

public:
	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageRadius = 32.0f;

	// ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 10.0f;

	// ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float Lifetime = 1.0f;

private:
	// ���� �ð� �� �Ҹ�
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DestroyEffect();

	// ������ �ο�
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DamageEnemy(AActor* HitActor);
};
