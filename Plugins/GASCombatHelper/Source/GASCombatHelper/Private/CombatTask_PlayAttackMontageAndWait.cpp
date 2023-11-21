// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatTask_PlayAttackMontageAndWait.h"
#include <AbilitySystemGlobals.h>
#include <Macros.h>
#include "CombatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

UCombatTask_PlayAttackMontageAndWait* UCombatTask_PlayAttackMontageAndWait::CreatePlayCombatAttackMontageAndWaitProxy(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, const FGameplayTag& hitActionTag,
	UAnimMontage* MontageToPlay, float Rate, FName StartSection, bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale, float StartTimeSeconds, bool bAllowInterruptAfterBlendOut)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UCombatTask_PlayAttackMontageAndWait* MyObj =
		NewAbilityTask<UCombatTask_PlayAttackMontageAndWait>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->_hitActionTag = hitActionTag;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->bAllowInterruptAfterBlendOut = bAllowInterruptAfterBlendOut;
	MyObj->StartTimeSeconds = StartTimeSeconds;

	return MyObj;
}

void UCombatTask_PlayAttackMontageAndWait::Activate()
{
	Super::Activate();

	AActor* actor = GetAvatarActor();
	AssertNotNullReturn(actor);

	UCombatComponent* hitComponent = actor->GetComponentByClass<UCombatComponent>();
	AssertNotNullReturn(hitComponent);

	hitComponent->_applyHitToActorWithActionTag.AddDynamic(
		this, &UCombatTask_PlayAttackMontageAndWait::ApplyHitToActor);
}

void UCombatTask_PlayAttackMontageAndWait::OnDestroy(bool AbilityEnded)
{
	AActor* actor = GetAvatarActor();
	if (actor)
	{
		UCombatComponent* meleeComponent = actor->GetComponentByClass<UCombatComponent>();
		if (meleeComponent)
		{
			meleeComponent->_applyHitToActorWithActionTag.RemoveDynamic(
				this, &UCombatTask_PlayAttackMontageAndWait::ApplyHitToActor);
		}
	}

	Super::OnDestroy(AbilityEnded);
}

void UCombatTask_PlayAttackMontageAndWait::ApplyHitToActor(AActor* actor, const FGameplayTag& hitActionTag)
{
	if (hitActionTag.MatchesTag(_hitActionTag))
	{
		_applyHitToActor.Broadcast(actor);
	}
}

void UCombatTask_PlayAttackMontageAndWait::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCombatTask_PlayAttackMontageAndWait, _hitActionTag);
}
