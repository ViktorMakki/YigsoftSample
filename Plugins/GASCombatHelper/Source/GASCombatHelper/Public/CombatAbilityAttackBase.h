// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "CombatAbilityAttackBase.generated.h"

USTRUCT(BlueprintType)
struct FCombatAttackAnimData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	UAnimMontage* montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	FName attackSection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	FName recoverySection;
};

/**
 *
 */
UCLASS()
class UCombatAbilityAttackBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

protected:
	// Montages for different Combo sequences
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASCombat")
	TArray<FCombatAttackAnimData> _comboMontages;

	// Returns true if the combo can continue
	UFUNCTION(BlueprintCallable, Category = "GASCombat")
	bool ConfirmCombo();

	UFUNCTION(BlueprintCallable, Category = "GASCombat")
	void UpdateCombo();

	UFUNCTION(BlueprintCallable, Category = "GASCombat")
	const FCombatAttackAnimData& GetCurrentAttackMontage() const;

	void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	int32 _comboIndex = 0;
	bool  _isCombo = true;
};
