// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"

#include "CombatNotifyState_HitWindow.generated.h"

// #TODO: This could be moved to a base static function library if needed
// elsewhere
UENUM(BlueprintType)
enum class CombatDebugDrawOptions
{
	None = 0,
	Game = 1,
	Editor = 2,
	EditorAndGame = 3
};

/**
 *
 */
UCLASS()
class GASCOMBATHELPER_API UCombatNotifyState_HitWindow : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference) override final;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference);

	// Override needed by returning actors hit by the action
	virtual TArray<AActor*> GetHitActors(AActor* owner, float frameDeltaSeconds) const;

	// Override to draw debug info about overlaps, Persistance debug lines are flushed before called
	virtual void DebugDrawEditor(const UWorld* world, float frameDeltaSeconds) const;

	// Override to draw debug info about overlaps, Persistance debug lines are flushed before called
	virtual void DebugDrawGame(AActor* owner, float frameDeltaSeconds) const;

protected:
	FVector TransformVectorToEditorSpace(const FVector& location) const;

	FVector TransformScaleToEditorSpace(const FVector& scale) const;

	// Hits will be registered with this tag,
	// Actors will not be hit by the same tag twice until the hit array is reset
	UPROPERTY(EditAnywhere, Category = "GASCombat")
	FGameplayTag _hitActionTag;

	// If set on notify end will flush the hit actors
	UPROPERTY(EditAnywhere, Category = "GASCombat")
	bool _flushHitsOnEnd = true;

	UPROPERTY(EditAnywhere, Category = "GASCombat")
	CombatDebugDrawOptions _debugDraw;

	// only used for debug purpose, inverse transforms the hit colliders to give better feedback
	// If null the actual space may differ in game for the colliders
	UPROPERTY(EditAnywhere, Category = "GASCombat")
	UClass* _debugMeshActorClass;

	// Will not clear debug lines between frames, use it for setting up.
	UPROPERTY(EditAnywhere, Category = "GASCombat")
	bool _drawPersistent;
};