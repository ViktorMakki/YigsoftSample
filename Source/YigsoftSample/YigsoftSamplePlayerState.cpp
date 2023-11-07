// Fill out your copyright notice in the Description page of Project Settings.


#include "YigsoftSamplePlayerState.h"

AYigsoftSamplePlayerState::AYigsoftSamplePlayerState()
{
	abilitySystemComponent = CreateDefaultSubobject<USampleAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AssertNotNullReturn(abilitySystemComponent);

	attributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
	AssertNotNullReturn(attributeSet);
}

void AYigsoftSamplePlayerState::InitAttributes(const TObjectPtr<UDataTable>& dataTable)
{
	AssertNotNullReturn(dataTable);
	AssertNotNullReturn(attributeSet);
	attributeSet->InitFromMetaDataTable(dataTable);
}

UAbilitySystemComponent* AYigsoftSamplePlayerState::GetAbilitySystemComponent() const
{
	return abilitySystemComponent;
}
