// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatNotifyState_HitSphere.h"
#include "Kismet/GameplayStatics.h"
#include "Engine\World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Macros.h"

TArray<AActor*> UCombatNotifyState_HitSphere::GetHitActors(AActor* owner, float frameDeltaSeconds) const
{
	AssertNotNullReturnVal(owner, {});

	UWorld* world = owner->GetWorld();
	AssertNotNullReturnVal(world, {});

	const FVector	actorLocation = owner->GetActorLocation();
	TArray<AActor*> result;

	for (const FSphere& sphere : _hitSpheres)
	{
		TArray<AActor*> outActors;
		const FVector	location = owner->GetActorTransform().TransformVector(sphere.Center) + actorLocation;
		const float		radius = owner->GetActorScale3D().X * sphere.W;

		UKismetSystemLibrary::SphereOverlapActors(world, location, radius, {}, actorsToHit, {}, outActors);
		result.Append(outActors);
	}
	return result;
}

void UCombatNotifyState_HitSphere::DebugDrawEditor(const UWorld* world, float frameDeltaSeconds) const
{
	AssertNotNullReturn(world);

	for (const FSphere& sphere : _hitSpheres)
	{
		const FVector location = TransformVectorToEditorSpace(sphere.Center);
		const float	  radius = TransformScaleToEditorSpace({ sphere.W, sphere.W, sphere.W }).X;
		DrawDebugSphere(world, location, radius, 8, _debugColor, true, -1.f, 0, 3.f);
	}
}

void UCombatNotifyState_HitSphere::DebugDrawGame(AActor* owner, float frameDeltaSeconds) const
{
	AssertNotNullReturn(owner);

	const UWorld* world = owner->GetWorld();
	AssertNotNullReturn(world);

	const FVector actorLocation = owner->GetActorLocation();

	for (const FSphere& sphere : _hitSpheres)
	{
		TArray<AActor*> outActors;
		const FVector	location = owner->GetActorTransform().TransformVector(sphere.Center) + actorLocation;
		const float		radius = owner->GetActorScale3D().X * sphere.W;
		DrawDebugSphere(world, location, radius, 8, _debugColor, true, -1.f, 0, 3.f);
	}
}
