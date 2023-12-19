// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FaceCameraComponent.generated.h"


UCLASS(ClassGroup = (UserInterface), meta = (BlueprintSpawnableComponent))
class YIGSOFTSAMPLE_API UFaceCameraComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFaceCameraComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
