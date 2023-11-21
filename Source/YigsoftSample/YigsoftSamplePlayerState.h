// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Ability/CharacterAttributeSet.h"
#include "SampleAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

#include "YigsoftSamplePlayerState.generated.h"

/**
 *
 */
UCLASS()
class YIGSOFTSAMPLE_API AYigsoftSamplePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AYigsoftSamplePlayerState();

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<USampleAbilitySystemComponent> abilitySystemComponent;
};
