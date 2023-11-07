// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatHitComponent.h"

void UCombatHitComponent::AddHitActors(const TArray<AActor*>& hitActors, const FGameplayTag& hitActionTag)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT DETECTED"));

	TArray<AActor*>& registeredHitActors = _hitActorMap.FindOrAdd(hitActionTag);
	for (auto* actor : hitActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("actor : %s"), *actor->GetName());

		if (actor == GetOwner())
		{
			continue;
		}

		if (!registeredHitActors.Contains(actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("broadcast hit actor : %s"), *actor->GetName());
			registeredHitActors.Add(actor);
			_applyHitToActorWithActionTag.Broadcast(actor, hitActionTag);
		}
	}
}

void UCombatHitComponent::RemoveHitActors(const FGameplayTag& hitActionTag)
{
	if (_hitActorMap.Contains(hitActionTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("REMOVING HITS	"));

		_hitActorMap.FindAndRemoveChecked(hitActionTag);
	}
}