// Fill out your copyright notice in the Description page of Project Settings.


#include "YigsoftSamplePlayerState.h"

AYigsoftSamplePlayerState::AYigsoftSamplePlayerState()
{
	abilitySystemComponent = CreateDefaultSubobject<USampleAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AssertNotNullReturn(abilitySystemComponent);
}

UAbilitySystemComponent* AYigsoftSamplePlayerState::GetAbilitySystemComponent() const
{
	return abilitySystemComponent;
}
