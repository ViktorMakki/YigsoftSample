// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatAbilityAttackBase.h"

bool UCombatAbilityAttackBase::ConfirmCombo()
{
	bool temp = _isCombo;
	_isCombo = false;
	return temp;
}

void UCombatAbilityAttackBase::UpdateCombo()
{
	++_comboIndex;

	if (_comboIndex < _comboMontages.Num())
	{
		_isCombo = true;
		return;
	}

	_isCombo = false;
}

const FCombatAttackAnimData& UCombatAbilityAttackBase::GetCurrentAttackMontage() const
{
	return _comboMontages[_comboIndex % _comboMontages.Num()];
}

void UCombatAbilityAttackBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	_comboIndex = 0;
	_isCombo = true;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UCombatAbilityAttackBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/,
	const FGameplayTagContainer* TargetTags /*= nullptr*/,
	OUT FGameplayTagContainer*	 OptionalRelevantTags /*= nullptr*/) const
{
	return !_comboMontages.IsEmpty() &&
		Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
