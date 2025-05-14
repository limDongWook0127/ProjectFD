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
	// 데미지 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageRadius = 32.0f;

	// 데미지 양
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 10.0f;

	// 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float Lifetime = 1.0f;

private:
	// 일정 시간 후 소멸
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DestroyEffect();

	// 데미지 부여
	UFUNCTION(BlueprintCallable, Category = "SkillFunc")
	void DamageEnemy(AActor* HitActor);
};
