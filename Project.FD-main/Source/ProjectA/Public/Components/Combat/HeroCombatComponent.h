// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

UENUM()
enum class ESkillType : uint8
{
	LandingSpark,
	SparkBall,
	SparkLaser,
	SparkRing,
};

class AHeroWeapon;
/**
 * 
 */
UCLASS()
class PROJECTA_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Combat")
    AHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float Level) const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterSkillObject(AHeroSkillBase* SkillObject, ESkillType SkillType);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterBulletObject(AHeroSkillBase* BulletObject);

	void ResetOverlappedActor();
	void ResetSparkBallOverlappedActor();
	void ResetSparkRingOverlappedActor();

protected:
	TArray<AActor*> SparkBallOverlappedActors;
	TArray<AActor*> SparkRingOverlappedActors;

protected:
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnLandingSparkHitTargetActor(AActor* HitActor);
	virtual void OnSparkBallHitTargetActor(AActor* HitActor);
	virtual void OnSparkLaserHitTargetActor(AActor* HitActor);
	virtual void OnSparkRingHitTargetActor(AActor* HitActor);

	virtual void OnBulletHitTargetActor(AActor* HitActor);
};
