// Fill out your copyright notice in the Description page of Project Settings.


#include "UIDataComponent.h"

// Sets default values for this component's properties
UUIDataComponent::UUIDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUIDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UUIDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UUIDataComponent::GetHealth() const
{
	return 30.f;
}

float UUIDataComponent::GetMaxHealth() const
{
	return 100.f;
}

