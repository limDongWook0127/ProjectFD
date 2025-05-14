// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/Input/BaseInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "BaseGamePlayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupBase.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Widget/HeroPawnUIComponent.h"
#include "Components/Inventory/Inventory_Component.h"
#include "Components/Inventory/BulletSystem_Component.h"
#include "PlayerSkillObject/LandingSpark.h"

#include "BaseDebugHelper.h"
#include <BaseFunctionLibrary.h>
#include <AbilitySystem/HeroAttributeSet.h>

AHeroCharacter::AHeroCharacter()
{
	//캡슐컴포넌트 초기사이즈 세팅
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	//회전 사용 비활성화
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//스프링암 초기세팅
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	//카메라 초기세팅
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//케릭터움직임 초기세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	//매시 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/HeroCharacter/SK_CharM_Barbarous.SK_CharM_Barbarous"));

	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	//매시 초기위치 세팅 Z방향으로 -100 내리고 Yaw축으로 -90도 회전
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -100.0f), FRotator(0, -90.0f, 0));

    //Component 세팅
	BaseAttributeSet = CreateDefaultSubobject<UHeroAttributeSet>(TEXT("BaseAttributeSet"));
    HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UHeroPawnUIComponent>(TEXT("HeroUiComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventory_Component>(TEXT("InventoryComponent"));
	Bullet_Component = CreateDefaultSubobject<UBulletSystem_Component>(TEXT("BulletComponent"));

	JumpMaxCount = 2;
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	//BeginPlay에서 로그 테스트
	//Debug::Print(TEXT("Hero is Working"));
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UBaseInputComponent* BaseInputComponent = CastChecked<UBaseInputComponent>(PlayerInputComponent);
    BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AHeroCharacter::Input_Move);
    BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AHeroCharacter::Input_Look);
    BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Jump, ETriggerEvent::Started, this, &AHeroCharacter::Input_Jump);
    BaseInputComponent->BindNativeInputAction(InputConfigDataAsset, BaseGamePlayTags::InputTag_Run, ETriggerEvent::Started, this, &AHeroCharacter::Input_Run);
    
    BaseInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AHeroCharacter::Input_AbilityInputPressed, &AHeroCharacter::Input_AbilityInputReleased);
}

void AHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if(bIsEvading) return;

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHeroCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	if (!GetCharacterMovement()->IsFalling())
	{
		JumpFx();
		Jump();
	}
	else if (!bIsDoubleJump)
	{
		DoubleJumpFx();
		LaunchCharacter(FVector(0, 0, 1) * 600.0f, false, true);
		bIsDoubleJump = true;
	}
}

void AHeroCharacter::Input_Run(const FInputActionValue& InputActionValue)
{
	if (GetCharacterMovement()->MaxWalkSpeed == 800)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
	else if (GetCharacterMovement()->MaxWalkSpeed == 600)
	{
		GetCharacterMovement()->MaxWalkSpeed = 800;
	}
}

void AHeroCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
    BaseAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AHeroCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
    BaseAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/*if (BaseAbilitySystemComponent && BaseAttributeSet)
	{
		const FString AppendString = FString::Printf(TEXT("Owner Actor: %s, AvatarActor: %s"), *BaseAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *BaseAbilitySystemComponent->GetAvatarActor()->GetActorLabel());

		Debug::Print(TEXT("Ability system component and AttributeSet valid. ") + AppendString, FColor::Green);
	}*/

	if (!StartupData.IsNull())
	{
		if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
		{
			//Startup데이터가 Null이 아닌경우 StartupData는 동기화로드를 거쳐서 최종적으로 게임어빌리티시스템이 발동된다. GA_HeroSpawnAxe
			LoadedData->GiveToAbilitySystemComponent(GetBaseAbilitySystemComponent());
		}
	}
	
}

UPawnCombatComponent* AHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AHeroCharacter::GetPawnUIComponent() const
{
//	UE_LOG(LogTemp, Warning, TEXT("aaaaaaaaaaaaaaaaaaaaaaaaa"));
	return HeroUIComponent;
}

UHeroPawnUIComponent* AHeroCharacter::GetHeroUIComponent() const
{
//	UE_LOG(LogTemp, Warning, TEXT("bbbbbbbbbbbbbbbbbbbbbbbbbbbb"));
	return HeroUIComponent;
}

void AHeroCharacter::EndAbilityByTag(FGameplayTag Tag)
{
	BaseAbilitySystemComponent->TryDeactivateAbilityByTag(Tag);
}

void AHeroCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bIsDoubleJump)
	{
		BaseAbilitySystemComponent->TryActivatedAbilityByTag(BaseGamePlayTags::Player_Ability_Attack_LandingSkill);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		ALandingSpark* LandingSpark = GetWorld()->SpawnActor<ALandingSpark>(LandingSparkClass, Hit.ImpactPoint, FRotator::ZeroRotator, SpawnParams);

		if (LandingSpark)
		{
			HeroCombatComponent->RegisterSkillObject(LandingSpark,ESkillType::LandingSpark);

			TArray<AActor*> OverlappingActors;
			LandingSpark->GetOverlappingActors(OverlappingActors);

			for (AActor* OverlappingActor : OverlappingActors)
			{
				if (APawn* HitPawn = Cast<APawn>(OverlappingActor))
				{
					if (UBaseFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
					{
						LandingSpark->ToOverlappedTarget.ExecuteIfBound(OverlappingActor);
					}
				}
			}
		}

		HeroCombatComponent->ResetOverlappedActor();
	}
	bIsDoubleJump = false;
}
