// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AttackAbilityBase.generated.h"

USTRUCT(BlueprintType)
struct FAttackSections
{
	GENERATED_BODY()

	// Section with the actual attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	FName attackSection;

	// Section for the recovery after this attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	FName recoverySection;
};

USTRUCT(BlueprintType)
struct FCombatAttackAnimData
{
	GENERATED_BODY()

	// Montage to play during this ability
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	UAnimMontage* montage;

	// Sections from the combo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	TArray<FAttackSections> attackSections;
};

/**
 *
 */
UCLASS()
class GASCOMBATHELPER_API UAttackAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		OUT FGameplayTagContainer*			 OptionalRelevantTags = nullptr) override;

protected:
	// Call to setup the next montage section, also applies ability cost.
	// Will wait for the attack section to finish, jumps from recovery section to the next attack
	UFUNCTION(BlueprintCallable, Category = "GASCombat")
	void ConfirmCombo();

	UFUNCTION(BlueprintCallable, Category = "GASCombat")
	UAnimMontage* GetMontage() const;

	UFUNCTION(BlueprintCallable, Category = "GASCombat")
	FName GetFirstSection() const;

	void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	// Montages for different Combo sequences
	UPROPERTY(EditAnywhere, Category = "GASCombat")
	FCombatAttackAnimData _attackAnimData;

	UPROPERTY(EditAnywhere, Category = "GASCombat")
	TEnumAsByte<EMovementMode> _attackMovementMode = EMovementMode::MOVE_Walking;

	EMovementMode _previousMovementMode = EMovementMode::MOVE_None;
	uint8		  _previousCustomMovementMode = 0;

	int32 _index = -1;
};
