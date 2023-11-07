// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameplayTagContainer.h"

#include "AbilityInputAction.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class YIGSOFTSAMPLE_API UAbilityInputAction : public UInputAction
{
	GENERATED_BODY()
public:
	const FGameplayTagContainer& GetABilityTags() const;

private:
	UPROPERTY(EditAnywhere, Category = Ability)
	FGameplayTagContainer abilityTags;
};
