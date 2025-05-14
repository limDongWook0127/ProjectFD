// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	//TryGetPawnOwner 소유자의 Pawn 반환
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	//소유한 캐릭터와 소유한 무브먼트중 하나라도 nullptr이면
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	//소유한 캐릭터의 속도
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	//소유한 캐릭터무브먼트의 움직임
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;


	LocoMotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
