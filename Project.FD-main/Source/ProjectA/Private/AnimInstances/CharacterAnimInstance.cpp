// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	//TryGetPawnOwner �������� Pawn ��ȯ
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	//������ ĳ���Ϳ� ������ �����Ʈ�� �ϳ��� nullptr�̸�
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	//������ ĳ������ �ӵ�
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	//������ ĳ���͹����Ʈ�� ������
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;


	LocoMotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
