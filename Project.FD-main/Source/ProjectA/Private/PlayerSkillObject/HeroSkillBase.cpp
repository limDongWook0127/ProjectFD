// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillObject/HeroSkillBase.h"
#include "BaseFunctionLibrary.h"

// Sets default values
AHeroSkillBase::AHeroSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHeroSkillBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeroSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroSkillBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

