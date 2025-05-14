// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Execs/GEExecCalc_DamageTaken.h"
#include "BaseGamePlayTags.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "BaseDebugHelper.h"

//2안
struct FDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Defence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, DamageTaken, Target, false);
	}
};

static const FDamageCapture& GetDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	//// 프로퍼티 생성
	//FProperty* AttackProperty = FindFieldChecked<FProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Attack));

	//// 캡쳐 생성
	//FGameplayEffectAttributeCaptureDefinition AttackCaptureDefindition(AttackProperty, EGameplayEffectAttributeCaptureSource::Source, false);

	//RelevantAttributesToCapture.Add(AttackCaptureDefindition);

	RelevantAttributesToCapture.Add(GetDamageCapture().AttackDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DefenceDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
}


void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackDef, EvaluateParameters, SourceAttack);
	//Debug::Print(TEXT("SourceAttack"), SourceAttack);


	float BaseDamage = 0.f;
	int32 cachedComboCount_Light = 0;
	int32 cachedComboCount_Heavy = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BaseGamePlayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseAttack"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(BaseGamePlayTags::Player_SetBycaller_AttackType_Heavy))
		{
			cachedComboCount_Heavy = TagMagnitude.Value;
		//	Debug::Print(TEXT("cachedComboCount_Heavy"), cachedComboCount_Heavy);
		}

		if (TagMagnitude.Key.MatchesTagExact(BaseGamePlayTags::Player_SetBycaller_AttackType_Light))
		{
			cachedComboCount_Light = TagMagnitude.Value;
		//	Debug::Print(TEXT("cachedComboCount_Light"), cachedComboCount_Light);
		}

	}
	float TargetDefence = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefenceDef, EvaluateParameters, TargetDefence);
//	Debug::Print(TEXT("TargetDefence"), TargetDefence);


	if (cachedComboCount_Light != 0)
	{
		const float LightDamageincrePercent = (cachedComboCount_Light - 1) * 0.05f + 1.f;
		BaseDamage *= LightDamageincrePercent;

	//	Debug::Print(TEXT("cachedComboCount_Light_BaseDamage"), BaseDamage);
	}

	if (cachedComboCount_Heavy != 0)
	{
		const float HeavyDamageincrePercent = cachedComboCount_Heavy * 0.15f + 1.f;
		BaseDamage *= HeavyDamageincrePercent;

	//	Debug::Print(TEXT("cachedComboCount_Heavy_BaseDamage"), BaseDamage);
	}

	const float FinalDamage = BaseDamage * SourceAttack / TargetDefence;
	//Debug::Print(TEXT("FinalDamage"), FinalDamage);

	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamage));
	}


}
