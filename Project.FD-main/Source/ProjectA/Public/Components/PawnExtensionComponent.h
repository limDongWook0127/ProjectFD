// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
    //T�� ���ʸ� Ÿ�� T�� �ν��Ͻ��� �����Ҷ� ��ü���� Ÿ���� ��������.
    template<class T>
    T* GetOwningPawn() const
    {
       //�����Ͽ��� ������ �߻��ϸ� �ش� �ؽ�Ʈǥ�� T�� �Ķ���ʹ� APawn���� �Ļ��Ǿ�� �Ѵ�.
       static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");
       return CastChecked<T>(GetOwner());
    }

    APawn* GetOwningPawn() const
    {
        return GetOwningPawn<APawn>();
    }

    template<class T>
    T* GetOwningController() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter get GetController must be derived from AController");
        return GetOwningPawn<APawn>()->GetController<T>();
    }

    AController* GetOwingController() const
    {
        return GetOwningController<AController>();
    }
};
