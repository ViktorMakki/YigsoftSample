// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"

void UCombatComponent::AddHitActors(const TArray<AActor*>& hitActors, const FGameplayTag& hitActionTag)
{
	TArray<AActor*>& registeredHitActors = _hitActorMap.FindOrAdd(hitActionTag);
	for (auto* actor : hitActors)
	{
		if (actor == GetOwner())
		{
			continue;
		}

		if (!registeredHitActors.Contains(actor))
		{
			registeredHitActors.Add(actor);
			_applyHitToActorWithActionTag.Broadcast(actor, hitActionTag);
		}
	}
}

void UCombatComponent::RemoveHitActors(const FGameplayTag& hitActionTag)
{
	if (_hitActorMap.Contains(hitActionTag))
	{
		_hitActorMap.FindAndRemoveChecked(hitActionTag);
	}
}