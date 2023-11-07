// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Macros.h"
#include "AbilitySystemComponent.h"

#include "CharacterAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class YIGSOFTSAMPLE_API UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData health;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData maxHealth;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, maxHealth);

	// Temporary meta attribute, not replicated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData damage;
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, damage);
};
