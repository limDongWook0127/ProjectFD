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
	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageRadius = 300.0f;

	// ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float DamageAmount = 50.0f;

	// ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
	float Lifetime = 2.0f;


private:
	// ���� �ð� �� �Ҹ�
	void DestroyEffect();

	// Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle;
};
