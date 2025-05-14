// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EmenyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Engine/AssetManager.h"
#include "BaseDebugHelper.h"
#include "Components/Widget/EnemyPawnUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Widgets/WidgetBase.h"
#include "AbilitySystem/EnemyAttributeSet.h"
#include "Items/Weapon/WeaponBase.h"

AEmenyCharacter::AEmenyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.0f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	
	EnemyUIComponent = CreateDefaultSubobject<UEnemyPawnUIComponent>(TEXT("EnemyUIComponent"));
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());

}

void AEmenyCharacter::PlaySpawnMontage()
{
	if (SpawnMontage && !GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		// 몬스터가 애니메이션을 실행 중이지 않다면 몽타주 실행
		GetMesh()->GetAnimInstance()->Montage_Play(SpawnMontage);
	}
}

void AEmenyCharacter::PossessedBy(AController* Newcontroller)
{
	Super::PossessedBy(Newcontroller);
	InitEnemyStartUpDate();

}

UPawnCombatComponent* AEmenyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AEmenyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyPawnUIComponent* AEmenyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AEmenyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UWidgetBase* HealthWidget = Cast<UWidgetBase>(WidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreateWidget(this);
	}
	
}

EShieldState AEmenyCharacter::SetShieldState(EShieldState State)
{
	if (State == EShieldState::Open)
	{
		State = EShieldState::Close;
	}
	else if (State == EShieldState::Close)
	{
		State = EShieldState::Open;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EShieldState not Setting"));
	}

	return State;
}

EShieldState AEmenyCharacter::GetShieldState()
{
	return ShieldState;
}

void AEmenyCharacter::EquipWeapon(AWeaponBase* Weapon, UMaterialInstanceDynamic* Mat)
{
	EquippedWeapon = Weapon;
	WeaponMat = Mat;
}

void AEmenyCharacter::InitEnemyStartUpDate()
{
	
	if (StartupData.IsNull())
	{
		return;
	}

	// startup data 비동기식 로드
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartupBase* LoadedData = StartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(BaseAbilitySystemComponent);
				//	Debug::Print(TEXT("enemystartupdataload"), FColor::Red);
				}
			}
		)
		);
}

