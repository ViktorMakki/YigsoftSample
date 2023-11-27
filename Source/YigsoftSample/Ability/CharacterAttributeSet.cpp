// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeSet.h"

void UCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	UE_LOG(LogTemp, Warning, TEXT("damage: %f"), NewValue);
}
