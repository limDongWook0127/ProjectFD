// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/WeaponBase.h"
#include "Components/BoxComponent.h"
#include "BaseFunctionLibrary.h"
#include "BaseDebugHelper.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	WeaponCollsionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollsionBox->SetupAttachment(RootComponent);
	WeaponCollsionBox->SetBoxExtent(FVector(20.0f));
	WeaponCollsionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollsionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollsionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
	
}

void AWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GetInstrigator - �̺�Ʈ�� �߻���Ų ������ ���� �������� �Էȴ°� TŬ���� ��ȯ (��ü���)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assingn an instigator as ths owning pawn of ths weapon : % s"), *GetName());

	//if (APawn* HitPawn = Cast<APawn>(OtherActor))
	//{
	//    if (WeaponOwningPawn != HitPawn)
	//    {
	//       // Debug::Print(GetName() + TEXT("Begin Overlap with") + HitPawn->GetName(), FColor::Yellow);
	//        OnWeaponHitTarget.ExecuteIfBound(OtherActor);
	//    }
	//}

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UBaseFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);

		}
	}

}

void AWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assingn an instigator as ths owning pawn of ths weapon : % s"), *GetName());

	//if (APawn* HitPawn = Cast<APawn>(OtherActor))
	//{
	//    if (WeaponOwningPawn != HitPawn)
	//    {
	//        // Debug::Print(GetName() + TEXT("Begin Overlap with") + HitPawn->GetName(), FColor::Yellow);
	//        OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
	//    }
	//}

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UBaseFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}

}



