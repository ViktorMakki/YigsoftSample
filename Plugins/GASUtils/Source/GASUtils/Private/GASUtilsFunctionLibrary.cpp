// Fill out your copyright notice in the Description page of Project Settings.

#include "GASUtilsFunctionLibrary.h"

#include "Macros.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

namespace data
{
	static const float UNIT_LENGTH_CM = 100.f;
	static const float UNIT_TIME_S = 0.2f;
} // namespace data

float UGASUtilsFunctionLibrary::GetUnitLengthCm()
{
	return data::UNIT_LENGTH_CM;
}

float UGASUtilsFunctionLibrary::GetUnitTimeS()
{
	return data::UNIT_TIME_S;
}

float UGASUtilsFunctionLibrary::ConvertLengthUnitToCm(float unitValue)
{
	return unitValue * data::UNIT_LENGTH_CM;
}

float UGASUtilsFunctionLibrary::ConvertTimeUnitToS(float unitValue)
{
	return unitValue * data::UNIT_TIME_S;
}

FVector UGASUtilsFunctionLibrary::GetDirectionFromActors(const AActor* from, const AActor* to)
{
	AssertNotNullReturnVal(from, {});
	AssertNotNullReturnVal(to, {});

	return FVector(to->GetActorLocation() - from->GetActorLocation()).GetSafeNormal();
}

FVector UGASUtilsFunctionLibrary::GetDirectionFromActorsXY(const AActor* from, const AActor* to)
{
	AssertNotNullReturnVal(from, {});
	AssertNotNullReturnVal(to, {});

	FVector direction = to->GetActorLocation() - from->GetActorLocation();
	return FVector(direction.X, direction.Y, 0.0).GetSafeNormal();
}

FVector UGASUtilsFunctionLibrary::GetActorOffsetLocation(const AActor* actor, const FVector& direction, float distance)
{
	AssertNotNullReturnVal(actor, {});
	return actor->GetActorLocation() + direction * distance;
}
