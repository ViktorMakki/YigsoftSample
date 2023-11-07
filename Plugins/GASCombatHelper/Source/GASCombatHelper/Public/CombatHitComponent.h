// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"

#include "CombatHitComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FApplyHitToActorWithActionTag, AActor*, hitActor, const FGameplayTag&, hitActionTag);

UCLASS(ClassGroup = (Component), DisplayName = "CombatHitComponent", meta = (BlueprintSpawnableComponent))
class UCombatHitComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Adds the hit actors to the hit map with the hitActionTag.
	void AddHitActors(const TArray<AActor*>& hitActors, const FGameplayTag& hitActionTag);

	// Removes the hit actors with the hitActionTag
	void RemoveHitActors(const FGameplayTag& hitActionTag);

	FApplyHitToActorWithActionTag _applyHitToActorWithActionTag;

private:
	TMap<FGameplayTag, TArray<AActor*>> _hitActorMap;
};
