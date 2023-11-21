// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GASUtilsFunctionLibrary.generated.h"

UCLASS()
class GASUTILS_API UGASUtilsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Metrics")
	static float GetUnitLengthCm();

	UFUNCTION(BlueprintPure, Category = "Metrics")
	static float GetUnitTimeS();

	UFUNCTION(BlueprintPure, Category = "Metrics")
	static float ConvertLengthUnitToCm(float unitValue);

	UFUNCTION(BlueprintPure, Category = "Metrics")
	static float ConvertTimeUnitToS(float unitValue);

	UFUNCTION(BlueprintPure, Category = "Math")
	static FVector GetDirectionFromActors(const AActor* from, const AActor* to);

	UFUNCTION(BlueprintPure, Category = "Math")
	static FVector GetDirectionFromActorsXY(const AActor* from, const AActor* to);

	UFUNCTION(BlueprintPure, Category = "Math")
	static FVector GetActorOffsetLocation(const AActor* actor, const FVector& direction, float distance);
};