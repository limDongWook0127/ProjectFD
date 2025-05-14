// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Drop_Item/ItemBase.h"
#include "Components/Inventory/Inventory_Component.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ItemMesh;

	ItemCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ItemCollision"));
	ItemCollision->SetupAttachment(RootComponent);
	ItemCollision->SetCapsuleRadius(50.f);
	ItemCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

}

void AItemBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 자식에서 정의
}

void AItemBase::SetItemMesh(int32 Type)
{
	// 자식에서 정의
}




