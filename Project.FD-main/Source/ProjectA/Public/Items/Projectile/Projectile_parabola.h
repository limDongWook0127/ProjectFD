// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Projectile/ProjectileBase.h"


#include "Projectile_parabola.generated.h"

/**
 *
 */
UCLASS()
class PROJECTA_API AProjectile_parabola : public AProjectileBase
{
    GENERATED_BODY()

public:
    AProjectile_parabola();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // �ʱ� �߻� �ӵ�
    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    float InitialSpeed;

    // ��ǥ �÷��̾� ĳ����
    ACharacter* PlayerCharacter;
    UFUNCTION(BlueprintCallable, Category = "Projectile")
    void CalculateProjectileVelocity(FVector Start, FVector End, float LaunchSpeed);

    UFUNCTION(BlueprintCallable, Category = "Projectile")
    AProjectile_parabola* SpawnProjectileParabola();

};
