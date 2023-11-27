// Fill out your copyright notice in the Description page of Project Settings.


#include "YigsoftNPCCharacter.h"
#include "AbilitySystemComponent.h"

AYigsoftNPCCharacter::AYigsoftNPCCharacter()
{
	abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}
