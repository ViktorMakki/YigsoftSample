// Fill out your copyright notice in the Description page of
// Project Settings.

#include "CombatNotifyState_HitWindow.h"
#include "Macros.h"
#include "CombatHitComponent.h"
#include "Engine\World.h"
#include "Components\SkeletalMeshComponent.h"

void UCombatNotifyState_HitWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	AssertNotNullReturn(MeshComp);

	UWorld* world = MeshComp->GetWorld();
	AssertNotNullReturn(world);

	AActor* owner = MeshComp->GetOwner();
	AssertNotNullReturn(owner);

	// Check if debug draw is needed
	if (_debugDraw > CombatDebugDrawOptions::None)
	{
		FlushPersistentDebugLines(world);

		// PIE is editor world too, so need to check not game world for editor window
		if (!world->IsGameWorld() &&
			(_debugDraw == CombatDebugDrawOptions::Editor || _debugDraw == CombatDebugDrawOptions::EditorAndGame))
		{
			DebugDrawEditor(world, FrameDeltaTime);
		}
		else if (world->IsGameWorld() &&
			(_debugDraw == CombatDebugDrawOptions::Game || _debugDraw == CombatDebugDrawOptions::EditorAndGame))
		{
			DebugDrawGame(owner, FrameDeltaTime);
		}
	}

	// Only send hit events in the game world
	if (world->IsGameWorld())
	{
		UCombatHitComponent* hitComponent = owner->GetComponentByClass<UCombatHitComponent>();
		AssertNotNullReturn(hitComponent);

		const TArray<AActor*> hitActors = GetHitActors(owner, FrameDeltaTime);
		hitComponent->AddHitActors(hitActors, _hitActionTag);
	}
}

void UCombatNotifyState_HitWindow::NotifyEnd(
	USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AssertNotNullReturn(MeshComp);

	UWorld* world = MeshComp->GetWorld();
	AssertNotNullReturn(world);

	if (world->IsGameWorld() && _flushHitsOnEnd)
	{
		AActor* owner = MeshComp->GetOwner();
		AssertNotNullReturn(owner);

		UCombatHitComponent* hitComponent = owner->GetComponentByClass<UCombatHitComponent>();
		AssertNotNullReturn(hitComponent);

		hitComponent->RemoveHitActors(_hitActionTag);
	}

	// Clean up debug lines if notify ended;
	if (!_drawPersistent)
	{
		FlushPersistentDebugLines(world);
	}
}

TArray<AActor*> UCombatNotifyState_HitWindow::GetHitActors(AActor* /*owner*/, float /*frameDeltaSeconds*/) const
{
	UE_LOG(LogTemp, Error, TEXT(R"(This notify should not be used directly, 
		use a derived class instead. Example: NotifyState_HitSphere)"));

	return TArray<AActor*>();
}

void UCombatNotifyState_HitWindow::DebugDrawEditor(const UWorld* /*world*/, float /*frameDeltaSeconds*/) const {}

void UCombatNotifyState_HitWindow::DebugDrawGame(AActor* /*owner*/, float /*frameDeltaSeconds*/) const {}

FVector UCombatNotifyState_HitWindow::TransformVectorToEditorSpace(const FVector& location) const
{
	CheckNotNullReturnVal(_debugMeshActorClass, location);

	AActor* actor = Cast<AActor>(_debugMeshActorClass->GetDefaultObject(true));
	CheckNotNullReturnVal(actor, location);

	USkeletalMeshComponent* mesh = actor->GetComponentByClass<USkeletalMeshComponent>();
	CheckNotNullReturnVal(mesh, location);

	const FTransform transform = mesh->GetRelativeTransform();
	return transform.InverseTransformVector(location) - transform.GetLocation();
}

FVector UCombatNotifyState_HitWindow::TransformScaleToEditorSpace(const FVector& scale) const
{
	CheckNotNullReturnVal(_debugMeshActorClass, scale);

	AActor* actor = Cast<AActor>(_debugMeshActorClass->GetDefaultObject(true));
	CheckNotNullReturnVal(actor, scale);

	USkeletalMeshComponent* mesh = actor->GetComponentByClass<USkeletalMeshComponent>();
	CheckNotNullReturnVal(mesh, scale);

	const FVector meshScale = mesh->GetRelativeScale3D();
	return { 1 / meshScale.X * scale.X, 1 / meshScale.Y * scale.Y, 1 / meshScale.Y * scale.Y };
}
