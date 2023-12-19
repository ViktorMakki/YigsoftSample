// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeSet.h"


void UCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float newHealth = FMath::Max(0.f, Gethealth() - Getdamage());
	Sethealth(newHealth);
	Setdamage(0.f);
}
