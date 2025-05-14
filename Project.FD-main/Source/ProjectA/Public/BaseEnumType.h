#pragma once

UENUM(BlueprintType)
enum class EBaseConfirmType : uint8
{
	Yes,
	No
};


UENUM(BlueprintType)
enum class EBaseValidType : uint8
{
	Valid,
	InValid
};

UENUM()
enum class EBaseSuccessType : uint8
{
	Success,
	Failed
};

UENUM(BlueprintType)
enum class EShieldState : uint8
{
	None,
	Open,
	Close
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	idle,
	alert,
	
};