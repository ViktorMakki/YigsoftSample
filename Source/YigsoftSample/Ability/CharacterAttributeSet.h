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

public:
	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, health);

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, maxHealth);

	ATTRIBUTE_ACCESSORS(UCharacterAttributeSet, damage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData maxHealth;

	// Temporary meta attribute
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData damage;

public:
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
