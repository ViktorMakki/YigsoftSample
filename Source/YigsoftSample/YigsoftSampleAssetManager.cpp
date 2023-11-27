// Fill out your copyright notice in the Description page of Project Settings.


#include "YigsoftSampleAssetManager.h"
#include "AbilitySystemGlobals.h"

void UYigsoftSampleAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Initializing AssetManager"));
}
