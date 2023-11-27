// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

#include "CombatTask_PlayAttackMontageAndWait.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FApplyHitToActor, AActor*, hitActor);

/**
 *
 */
UCLASS()
class GASCOMBATHELPER_API UCombatTask_PlayAttackMontageAndWait : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FApplyHitToActor _applyHitToActor;

	UPROPERTY(Replicated)
	FGameplayTag _hitActionTag;

	// Will ApplyHitToActor is fired if Actor has a HitComponent and the action tag matches the
	// hitActionTag
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",
		meta = (DisplayName = "PlayCombatAttackMontageAndWait", HidePin = "OwningAbility",
			DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UCombatTask_PlayAttackMontageAndWait* CreatePlayCombatAttackMontageAndWaitProxy(
		UGameplayAbility* OwningAbility, FName TaskInstanceName, const FGameplayTag& hitActionTag,
		UAnimMontage* inMontageToPlay, float inRate = 1.f, FName inStartSection = NAME_None,
		bool StopWhenAbilityEnds = true, float inAnimRootMotionTranslationScale = 1.f, float inStartTimeSeconds = 0.f,
		bool AllowInterruptAfterBlendOut = false);

	virtual void Activate() override;

	virtual void OnDestroy(bool AbilityEnded) override;

	UFUNCTION()
	void ApplyHitToActor(AActor* actor, const FGameplayTag& hitActionTag);
};
