// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackAbilityBase.h"

#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\Character.h"
#include "Macros.h"
#include "AbilitySystemComponent.h"

static int32 FindByAttackSection(const TArray<FAttackSections>& data, const FName& attackSection)
{
	for (int32 i = 0; i < data.Num(); ++i)
	{
		if (data[i].attackSection.IsEqual(attackSection))
		{
			return i;
		}
	}
	return -1;
}

void UAttackAbilityBase::ConfirmCombo()
{
	UAbilitySystemComponent* abilitySystem = GetAbilitySystemComponentFromActorInfo();
	AssertNotNullReturn(abilitySystem);

	const FName currentSectionPlaying = abilitySystem->GetCurrentMontageSectionName();

	// Will be -1 if the current section is recovery
	const int32 currentIndex = FindByAttackSection(_attackAnimData.attackSections, currentSectionPlaying);

	// Return if the attack is already set in this section,
	// Skip first attack
	if (_index == currentIndex && _index > 0)
	{
		return;
	}
	// initialize index
	_index = FMath::Max(0, _index);

	// Apply cost for the attack
	if (!CommitAbilityCost(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		return;
	}

	// If the animation is currently during an attack phase, then set the next section to the next attack phase
	if (currentIndex >= 0)
	{
		_index = (currentIndex + 1) % _attackAnimData.attackSections.Num();
		const FAttackSections nextSection = _attackAnimData.attackSections[_index];
		abilitySystem->CurrentMontageSetNextSectionName(currentSectionPlaying, nextSection.attackSection);
		abilitySystem->CurrentMontageSetNextSectionName(nextSection.attackSection, nextSection.recoverySection);
	}
	// The animation is in recovery phase, lets just jump into the next attack phase
	else
	{
		_index = (_index + 1) % _attackAnimData.attackSections.Num();
		const FAttackSections nextSection = _attackAnimData.attackSections[_index];
		abilitySystem->CurrentMontageJumpToSection(nextSection.attackSection);
		abilitySystem->CurrentMontageSetNextSectionName(nextSection.attackSection, nextSection.recoverySection);
	}
}

UAnimMontage* UAttackAbilityBase::GetMontage() const
{
	return _attackAnimData.montage;
}

FName UAttackAbilityBase::GetFirstSection() const
{
	return _attackAnimData.attackSections[0].attackSection;
}

void UAttackAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ACharacter* avatar = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (avatar)
	{
		UCharacterMovementComponent* movementComponent = avatar->GetCharacterMovement();
		if (movementComponent)
		{
			movementComponent->SetMovementMode(_previousMovementMode, _previousCustomMovementMode);
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UAttackAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/,
	const FGameplayTagContainer* TargetTags /*= nullptr*/,
	OUT FGameplayTagContainer*	 OptionalRelevantTags /*= nullptr*/) const
{
	return !_attackAnimData.attackSections.IsEmpty() &&
		Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

bool UAttackAbilityBase::CommitAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/)
{
	const bool result = Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);

	_index = -1;

	ACharacter* avatar = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	CheckNotNullReturnVal(avatar, false);

	UCharacterMovementComponent* movementComponent = avatar->GetCharacterMovement();
	CheckNotNullReturnVal(movementComponent, false);

	_previousMovementMode = movementComponent->MovementMode;
	_previousCustomMovementMode = movementComponent->CustomMovementMode;

	movementComponent->SetMovementMode(_attackMovementMode);

	return result;
}
